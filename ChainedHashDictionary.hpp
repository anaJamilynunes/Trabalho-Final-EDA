#ifndef CHAINED_HASH_DICTIONARY_HPP
#define CHAINED_HASH_DICTIONARY_HPP

#include <cstddef>
#include <functional>
#include <stdexcept>

#include "ChainHashNode.hpp"

template<typename Key, typename Value>
class ChainedHashDictionary
{
private:

    //vetor de ponteiros para listas encadeadas
    ChainHashNode<Key, Value>** table;

    //qtd de posições da tabela hash
    size_t capacity;

    //contador: qtd de elementos armazenados
    size_t elementCount;

    //calcula o indice da chave na tabela
    size_t hash(
        const Key& key
    ) const;

public:

    //construtor: cria a hash vazia
    ChainedHashDictionary(
        size_t initialCapacity = 101
    );

    //destrutor: libera toda a memória utilizada
    ~ChainedHashDictionary();

    //insere uma nova chave e valor
    bool insert(
        const Key& key,
        const Value& value
    );

    //remove uma chave da estrutura
    bool remove(
        const Key& key
    );

    //verifica se uma chave existe
    bool contains(
        const Key& key
    ) const;

    //retorna ponteiro/endereço para o valor associado
    //sem o const
    Value& get(
        const Key& key
    );

    //com o var const
    const Value& get(
        const Key& key
    ) const;


    //atualiza o valor de uma chave existente
    bool update(
        const Key& key,
        const Value& value
    );

    //remove todos os elementos
    void clear();

    //qtd de elementos armazenados
    size_t size() const;

    //verifica se a estrutura está vazia
    bool empty() const;

    //busca e insere automaticamente
    Value& operator[](
        const Key& key
    );
};

#include "ChainedHashDictionary.tpp"

#endif