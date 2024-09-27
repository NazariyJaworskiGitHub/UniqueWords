#include "WordCounter.h"

Words WordCounter::getUniqueWords_simple(const std::string& file_name) 
{
    Words words;
    std::ifstream file(file_name);
    std::string word;
    while (file >> word) words.insert(word);
    file.close();
    return words;
}

std::vector<Chunk> WordCounter::divide_file_into_chunks(const std::string &file_name, size_t num_chunks) 
{
    std::ifstream file(file_name, 
        std::ios::binary |
        std::ios::ate);
        size_t file_size = file.tellg();
    file.close();
    if(file_size < num_chunks*2) num_chunks = 1;
    std::vector<Chunk> chunks;
    size_t chunk_size = file_size / num_chunks;
    size_t start = 0;
    for (size_t i = 0; i < num_chunks; ++i) 
    {
        size_t end = (i == num_chunks - 1) ? file_size : start + chunk_size;
        chunks.push_back({start, end});
        start = end+1;
    }
    return chunks;
}

Words WordCounter::process_chunk(const std::string &file_name, Chunk chunk) 
{
    Words local_words;
    std::string word;
    std::ifstream file(file_name);
    file.seekg(chunk.first);
    if(chunk.first!=0) {
        char c;
        file.get(c);
        if(!std::isspace(c))
            file >> word; 
    }
    if((size_t)file.tellg()>=chunk.second) return {};
    do {
        if(file >> word)
            local_words.insert(word);
    }
    while ((size_t)file.tellg() <= chunk.second);
    file.close();
    return local_words;
}

Words WordCounter::merge_sets( Words &set1, Words &set2) 
{
    set1.insert(set2.begin(), set2.end());
    return set1;
}

Words WordCounter::getUniqueWords(const std::string &file_name)
{
    size_t num_threads = std::thread::hardware_concurrency();
    auto chunks = divide_file_into_chunks(file_name, num_threads);
    std::vector<std::future<Words>> futures;
    for (auto &chunk : chunks) futures.push_back(std::async(std::launch::async, process_chunk, file_name, chunk));
    std::vector<Words> hash_sets;
    for (auto &fut : futures) hash_sets.push_back(fut.get());
    while (hash_sets.size() > 1)
    {
        std::vector<std::future<Words>> merge_futures;
        for (size_t i = 0; i < hash_sets.size(); i += 2)
            if (i + 1 < hash_sets.size())
                merge_futures.push_back(std::async(std::launch::async, merge_sets, std::ref(hash_sets[i]), std::ref(hash_sets[i + 1])));
            else
                merge_futures.push_back(std::async(std::launch::async, [](Words &set){ return set; }, std::ref(hash_sets[i])));
        std::vector<Words> tmp_hash_sets;
        for (auto &merge_fut : merge_futures) tmp_hash_sets.push_back(merge_fut.get());
        hash_sets.clear();
        hash_sets = std::move(tmp_hash_sets);
    }
    return std::move(hash_sets[0]);
}