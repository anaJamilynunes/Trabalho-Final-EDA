#ifndef FREQUENCYCOUNTER_TPP
#define FREQUENCYCOUNTER_TPP

#include "FrequencyCounter.hpp"

template<class DictionaryType>
void FrequencyCounter<DictionaryType>::build(
        DictionaryType& dictionary,
        const std::vector<std::string>& words)
{
    //iremos percorrer o vetor
    for(const auto& word : words) {

    //verifica se a palavra atual já foi inserida no dicionário antes
    //busca a frequencia atual e 
    //atualiza o resgistro
    //se nao, será inserida com frequência inicial como 1
        if(dictionary.contains(word)) {
            int frequency =
                dictionary.get(word);

            dictionary.update(
                word,
                frequency + 1);
        } else {
            dictionary.insert(
                word,
                1);
        }
    }
}

#endif