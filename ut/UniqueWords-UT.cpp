#include <iostream>
#include <cassert>
#include "../WordCounter.h"

int main(void)
{
    WordCounter word_counter;
    assert(word_counter.getUniqueWords("../../ut/input1.txt").size() == 35242);
    assert(word_counter.getUniqueWords("../../ut/input2.txt").size() == 1);
    assert(word_counter.getUniqueWords("../../ut/input3.txt").size() == 0);
    assert(word_counter.getUniqueWords("../../ut/input4.txt").size() == 4);
    return 0;
}
