#ifndef FREQUENCYCOUNTER_HPP
#define FREQUENCYCOUNTER_HPP

#include <vector>
#include <string>

/**
 * FrequencyCounter.hpp
 * Módulo utilitário para contagem e estatística de frequência de termos.
 * Abstrai o processo de iteração e contagem, permitindo o uso de 
 * qualquer estrutura de dicionário que implemente a interface de inserção/busca.
 * @author Ana Jamily
 */

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