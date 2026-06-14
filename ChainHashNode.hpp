#ifndef CHAIN_HASH_NODE_HPP
#define CHAIN_HASH_NODE_HPP

template<typename Key, typename Value>
struct ChainHashNode
{
    Key key; //armazena a chave
    Value value; //e seu valor associado

    ChainHashNode<Key, Value>* next; //ligação com próximo nó

    ChainHashNode(
        const Key& k,
        const Value& v
    )
    :
    key(k),
    value(v),
    next(nullptr)
    {
    }
};

#endif