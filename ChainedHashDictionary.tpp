#include <functional>
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <vector>
#include "ChainHashNode.hpp"

//irá transforma uma chave em uma posição válida da tabela.
template<typename Key, typename Value>
size_t ChainedHashDictionary<Key, Value>::hash(
    const Key& key
) const
{
    //cria um objeto responsável por gerar códigos hash.
    std::hash<Key> hasher;

    //e retorna um índice válido
    return hasher(key) % capacity;
}


template<typename Key, typename Value>
ChainedHashDictionary<Key, Value>::ChainedHashDictionary(
    size_t initialCapacity
)
{
    capacity = initialCapacity; //guarda a capacidade 

    //o vetor é alocado, criando um vetor de ponteiros
    table =
        new ChainHashNode<Key, Value>*[capacity];

    //e entao é feita a inicialização das posições .: fazer apontar
    for(size_t i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }

    //tabela recém criada e vazia, posições apontam para null 
    elementCount = 0;

    comparisons = 0;
    collisions = 0;
}

template<typename Key, typename Value>
ChainedHashDictionary<Key, Value>::~ChainedHashDictionary()
{
    //removemos todos os nós existentes nas listas
    clear();

    //e também o vetor principal
    delete[] table;
}

template<typename Key, typename Value>
size_t ChainedHashDictionary<Key, Value>::size() const
{
    //contador atualizado 
    return elementCount;
}

template<typename Key, typename Value>
bool ChainedHashDictionary<Key, Value>::empty() const
{
    //true: se estiver vazia
    return elementCount == 0;
}

//verifica se existe
template<typename Key, typename Value>
bool ChainedHashDictionary<Key, Value>::contains(
    const Key& key
) const
{
    //obtendo posição da tabela
    size_t index = hash(key);

    //current aponta para o primeiro nó da lista
    ChainHashNode<Key, Value>* current =
        table[index];

    //enquanto existir nó ele irá buscar
    while(current != nullptr) {
        comparisons++;

        if(current->key == key) {
            return true;
        }

        //próximo nó
        current = current->next;
    }

    return false;
}

//retorna o valor associado a chave
//será igual ao contains
template<typename Key, typename Value>
Value&
ChainedHashDictionary<Key, Value>::get(
    const Key& key
)
{
    size_t index = hash(key); //guarda o inicio

    ChainHashNode<Key, Value>* current = //aux
        table[index];

    while(current != nullptr) {
        comparisons++;

        if(current->key == key) {
            //se for encontrada retorna a referencia
            return current->value;
        }
        //percorre a lista
        current = current->next;
    }
    //caso nao encontre lança exceção
    throw std::out_of_range(
        "Key not found"
    );
}

//get const
template<typename Key, typename Value>
const Value&
ChainedHashDictionary<Key, Value>::get(
    const Key& key
) const
{
    size_t index = hash(key);

    ChainHashNode<Key, Value>* current =
        table[index];

    while(current != nullptr) {
        comparisons++;

        if(current->key == key) {
            return current->value;
        }

        current = current->next;
    }

    //se nao existir é lançada uma exceção
    throw std::out_of_range(
        "Key not found"
    );
}

template<typename Key, typename Value>
bool ChainedHashDictionary<Key, Value>::insert(
    const Key& key,
    const Value& value
)
{
    //se a chave já existir ela 
    //não poderá ser inserida novamente
    if(contains(key)) {
        return false;
    }

    size_t index = hash(key); //posição inicial

    if(table[index] != nullptr) {
        collisions++;
    }

    //criando o novo nó
    ChainHashNode<Key, Value>* newNode =
        new ChainHashNode<Key, Value>(
            key,
            value
        );

    newNode->next = table[index]; //liga o novo nó ao antigo primeiro nó

    table[index] = newNode; //atualiza o inicio

    elementCount++; //e o contador

    return true;
}

template<typename Key, typename Value>
bool ChainedHashDictionary<Key, Value>::update(
    const Key& key,
    const Value& value
)
{
    size_t index = hash(key); //guarda o inicio

    //current aponta para o primeiro nó da lista
    ChainHashNode<Key, Value>* current =
        table[index];

    while(current != nullptr) {
        comparisons++;

        if(current->key == key) {
            //e entao o novo valor será guardado
            current->value = value;
            return true;
        }

        //próximo
        current = current->next;
    }

    return false;
}

template<typename Key, typename Value>
bool ChainedHashDictionary<Key, Value>::remove(
    const Key& key
)
{
    size_t index = hash(key); //guarda o inicio

    //current aponta para o primeiro nó da lista
    ChainHashNode<Key, Value>* current =
        table[index];

    //ptr auxiliar para rastrear o nó anterior ao current
    //por isso inicia null
    ChainHashNode<Key, Value>* previous =
        nullptr;

    while(current != nullptr) {
        comparisons++;

        if(current->key == key) {
            //se null, significa que o nó a ser removido é o primeiro da lista
            //entao a cabeça deve ser atualizada
            if(previous == nullptr) {
                table[index] =
                    current->next;
            } else {
                //se nao ajustamos para saltar
                previous->next =
                    current->next;
            }

            //o nó é liberado 
            delete current;

            //e o contador atualizado
            elementCount--;

            return true;
        }

        previous = current; //move o ptr previous para o nó atual antes de avançar
        current = current->next; //move para o próximo nó da lista
    }

    return false;
}

template<typename Key, typename Value>
void ChainedHashDictionary<Key, Value>::clear()
{
    //para percorrer todas as posições da hash
    for(size_t i = 0; i < capacity; i++) {
        ChainHashNode<Key, Value>* current =
            table[i];

        //e todas as listas removendo cada nó
        while(current != nullptr) {
            //guarda o nó atual para dar continuidade
            ChainHashNode<Key, Value>* temp =
                current;

            //avançar e 
            current = current->next;
            //liberar o nó salvo no temporário
            delete temp;
        }

        //p/evitar lixo o ptr da tabela deve ser nill
        table[i] = nullptr;
    }

    //manter contador atualizado
    elementCount = 0;
}

//diferente do get, se a chave nao existir ela 
//será implementada automaticamente
template<typename Key, typename Value>
Value&
ChainedHashDictionary<Key, Value>::operator[](
    const Key& key
)
{
    size_t index = hash(key);

    ChainHashNode<Key, Value>* current =
        table[index];

    while(current != nullptr) {
        comparisons++;

        if(current->key == key) {
            return current->value;
        }

        current = current->next;
}

    //chama o insert, caso a chave nao for encontrada
    insert(key, Value());

    //retorna o valor associado 
    return get(key);
}

//metricas
//retorna o contador global de comparações de chaves
template<typename K, typename V>
long long
ChainedHashDictionary<K,V>::getComparisons() const {
    return comparisons;
}

//retorna o número total de colisões registradas
template<typename K, typename V>
long long
ChainedHashDictionary<K,V>::getCollisions() const {
    return collisions;
}

//indica quantos elementos existem por posição da tabela
template<typename Key, typename Value>
double
ChainedHashDictionary<Key,Value>::
getLoadFactor() const
{
    //razão entre o número total de elementos e a capacidade da tabela
    return
        static_cast<double>(elementCount)/capacity;
}

//para encontrar qual é a maior lista encadeada ou maior número de colisões em uma única posição
template<typename Key, typename Value>
size_t
ChainedHashDictionary<Key,Value>::
getLargestChain() const
{
    //aux p/ armazenar o atual maior tam de lista 
    size_t max = 0;

    //percorre todas as posições da hash
    for(size_t i=0;i<capacity;i++) {
        //e guardamos quantos nós existem na lista encadeada
        size_t current = 0;

        ChainHashNode<Key,Value>* ptr =
            table[i];

        //laço para fazer a contagem
        while(ptr != nullptr) {
            current++;
            ptr = ptr->next;
        }

        //e se a lista no i for maior atualiza
        if(current > max) {
            max = current;
        }
    }

    return max;
}

//ordenação - as chaves ficam espalhadas
template<typename Key, typename Value>
std::vector<Key>
ChainedHashDictionary<Key,Value>::
getKeys() const
{
    std::vector<Key> keys; //criar um vetor para acumular todas as chaves encontradas na tabela

    //todas as posições do vetor e todas as listas sao varridas
    //a chave de cada nó (current->key) e jogando-a para dentro do vetor usando o keys.push_back
    for(size_t i=0; i<capacity; i++) { 
        ChainHashNode<Key,Value>* current =
            table[i];

        while(current != nullptr) {
            keys.push_back(
                current->key
            );

            current =
                current->next;
        }
    }

    //por fim, o veotr é organizado em 
    //ordem alfabética crescente
    std::sort(
        keys.begin(),
        keys.end()
    );

    return keys;
}