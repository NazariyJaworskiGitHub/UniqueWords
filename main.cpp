#include <iostream>
#include "WordCounter.h"

int main(int argc, char *argv[])
{
    if(argc>1)
    {
        std::string file_name(argv[1]);
        // std::cout << "Processing " << file_name << std::endl;
        std::ifstream file(file_name);
        if (!file.is_open()) throw std::runtime_error("Could not open file.");
        file.close();

        WordCounter word_counter;
        std::cout << word_counter.getUniqueWords(file_name).size() << std::endl;
        // std::cout << word_counter.getUniqueWords_simple(file_name).size() << std::endl;
    }
    else {
        std::cout << "Please provide a file name" << std::endl;
        return 1;
    }
    return 0;
}


