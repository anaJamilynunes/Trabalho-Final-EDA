#ifndef RBNODE_HPP
#define RBNODE_HPP

/**
 * RBNode.hpp
 * Estrutura de nó para Árvores Rubro-Negras (Red-Black Tree).
 * Contém os metadados necessários (cor e ponteiro para pai) para realizar 
 * as operações de rotação e balanceamento estrito da árvore binária de busca.
 * @author Ana Jamily
 */

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
    
    // Ponteiros de navegação bidirecional na árvore    
    RBNode<Key, Value>* parent;
    RBNode<Key, Value>* left;
    RBNode<Key, Value>* right;
};

#endif