#ifndef CHAIN_HASH_NODE_HPP
#define CHAIN_HASH_NODE_HPP

/**
 * ChainHashNode.hpp
 * Estrutura de nó para tabelas hash com encadeamento (Chaining Hash).
 * Representa uma unidade fundamental de armazenamento em uma tabela 
 * hash que resolve colisões por meio de listas encadeadas.
 * @author Ana Jamily
 */

template<typename Key, typename Value>
struct ChainHashNode
{
    Key key; //armazena a chave
    Value value; //e seu valor associado

    // Ponteiro para o próximo nó da lista encadeada (tratamento de colisão)
    ChainHashNode<Key, Value>* next; 

    //Construtor para inicialização do nó.
    ChainHashNode(
        const Key& k,
        const Value& v
    )
    :
    key(k),
    value(v),
    next(nullptr) // Inicializa sem conexões para evitar ponteiros soltos
    {
    }
};

#endif