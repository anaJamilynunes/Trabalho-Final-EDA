#ifndef FREQUENCYCOUNTER_TPP
#define FREQUENCYCOUNTER_TPP

#include "FrequencyCounter.hpp"

template<class DictionaryType>
void FrequencyCounter<DictionaryType>::build(
        DictionaryType& dictionary,
        const std::vector<std::string>& words)
{
    for(const auto& word : words)
    {
        if(dictionary.contains(word))
        {
            int frequency =
                dictionary.get(word);

            dictionary.update(
                word,
                frequency + 1);
        }
        else
        {
            dictionary.insert(
                word,
                1);
        }
    }
}

#endif