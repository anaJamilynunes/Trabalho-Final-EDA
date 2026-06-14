#ifndef RBNODE_HPP
#define RBNODE_HPP

enum Color
{
    RED,
    BLACK
};

template<typename Key, typename Value>
struct RBNode
{
    Key key;
    Value value;

    Color color;

    RBNode<Key, Value>* parent;
    RBNode<Key, Value>* left;
    RBNode<Key, Value>* right;
};

#endif