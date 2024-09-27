#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <unordered_set>
#include <vector>
#include <string>
#include <future>
#include <fstream>

using Words = std::unordered_set<std::string>;
using Chunk = std::pair<size_t, size_t>;

class WordCounter
{
public:
    Words getUniqueWords(const std::string&);
    Words getUniqueWords_simple(const std::string&);

private:
    inline std::vector<Chunk> divide_file_into_chunks(const std::string&, size_t);
    static Words process_chunk(const std::string&, Chunk);
    static Words merge_sets(Words&, Words&);
};

#endif // WORDCOUNTER_H
