#ifndef CHAINED_HASH_DICTIONARY_HPP
#define CHAINED_HASH_DICTIONARY_HPP

#include <cstddef>
#include <functional>
#include <stdexcept>
#include "Dictionary.hpp"
#include "ChainHashNode.hpp"

template<typename Key, typename Value>
class ChainedHashDictionary :
    public Dictionary<Key, Value>
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
    ) override;

    //remove uma chave da estrutura
    bool remove(
        const Key& key
    ) override;

    //verifica se uma chave existe
    bool contains(
        const Key& key
    ) const override;

    //retorna ponteiro/endereço para o valor associado
    //sem o const
    Value& get(
        const Key& key
    ) override;

    //com o var const
    const Value& get(
        const Key& key
    ) const override;


    //atualiza o valor de uma chave existente
    bool update(
        const Key& key,
        const Value& value
    ) override;

    //remove todos os elementos
    void clear() override;

    //qtd de elementos armazenados
    size_t size() const override;

    //verifica se a estrutura está vazia
    bool empty() const override;

    //busca e insere automaticamente
    Value& operator[](
        const Key& key
    ) override;
};

#include "ChainedHashDictionary.tpp"

#endif