#ifndef FREQUENCYCOUNTER_HPP
#define FREQUENCYCOUNTER_HPP

#include <vector>
#include <string>

template<class DictionaryType>
class FrequencyCounter
{
public:
//referencia para o dicionario onde as frequencias
//serao guardadas e o vetor contendo todas as palavras que queremos contar
    static void build(
        DictionaryType& dictionary,
        const std::vector<std::string>& words);
};

#include "FrequencyCounter.tpp"

#endif