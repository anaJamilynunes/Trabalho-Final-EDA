#ifndef RBTREE_DICTIONARY_HPP
#define RBTREE_DICTIONARY_HPP

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "RBNode.hpp"
#include "Dictionary.hpp"

template<typename Key, typename Value>
class RBTreeDictionary :
    public Dictionary<Key, Value>
{
private:

    RBNode<Key,Value>* root;
    RBNode<Key,Value>* NIL;

    size_t nodeCount; //contador

    void leftRotate(
        RBNode<Key,Value>* x
    );

    void rightRotate(
        RBNode<Key,Value>* y
    );

    void insertFixup(
        RBNode<Key,Value>* z
    );

    void deleteFixup(
        RBNode<Key,Value>* x
    );

    RBNode<Key,Value>* searchNode(
        const Key& key
    ) const;

    RBNode<Key,Value>* minimum(
        RBNode<Key,Value>* node
    ) const;

    void printInOrder(RBNode<Key, Value>* node);
    
public:

    //construtor: inicializa a raiz com o nil
    RBTreeDictionary() ;

    //destrutor: irá chamar a clear()
    ~RBTreeDictionary();

    bool insert(
        const Key& key,
        const Value& value
    ) override;

    bool remove(
        const Key& key
    ) override;

    //bool: verifica a existencia de uma chave
    bool contains(
        const Key& key
    ) const override;

    //busca o valor de uma chave
    //se nao existir lança uma exceção
    Value& get(
    const Key& key
    ) override;

    const Value& get(
        const Key& key
    ) const override;

    //bool: atualiza uma chave
    bool update(
        const Key& key,
        const Value& value
    ) override;

    //percorre a arvore usando pilha para liberar a memória alocada
    void clear() override;

    //retorna a qtd de elementos
    size_t size() const override;

    //verifica se a arvore está vazia
    bool empty() const override;

    //permite a inserção dinâmica
    Value& operator[](
        const Key& key
    ) override;

    //percorre em order crescente e imprime as chaves, cores e nós
    void printInOrder();


};

#include "RBTreeDictionary.tpp"
#endif