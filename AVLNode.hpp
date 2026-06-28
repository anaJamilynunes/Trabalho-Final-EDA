#ifndef AVL_NODE_HPP
#define AVL_NODE_HPP

// a inclusão do ponteiro 'parent'. 
// É ele que me permite "subir" na árvore para verificar e aplicar rotações 
template<typename Key, typename Value>
struct AVLNode {
    Key key;
    Value value;
    
    AVLNode<Key, Value>* left;
    AVLNode<Key, Value>* right;
    AVLNode<Key, Value>* parent; 
    
    // Altura do nó (usada para calcular o Fator de Balanceamento na árvore).
    int height;

    // Construtor: novas folhas sempre nascem sem filhos, sem pai e com altura 1.
    AVLNode(const Key& k, const Value& v)
    : key(k), value(v), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
};

#endif
