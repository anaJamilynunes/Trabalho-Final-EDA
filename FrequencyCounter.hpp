#ifndef FREQUENCYCOUNTER_HPP
#define FREQUENCYCOUNTER_HPP

#include <vector>
#include <string>

template<class DictionaryType>
class FrequencyCounter
{
public:

    static void build(
        DictionaryType& dictionary,
        const std::vector<std::string>& words);
};

#include "FrequencyCounter.tpp"

#endif