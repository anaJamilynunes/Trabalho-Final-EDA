#ifndef AVL_DICTIONARY_TPP
#define AVL_DICTIONARY_TPP

#include "AVLDictionary.hpp" 

template<typename Key, typename Value>
int AVLDictionary<Key, Value>::height(AVLNode<Key, Value>* node) const {
    return node == nullptr ? 0 : node->height;
}

template<typename Key, typename Value>
void AVLDictionary<Key, Value>::updateHeight(AVLNode<Key, Value>* node) {
    if (node != nullptr) {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

template<typename Key, typename Value>
int AVLDictionary<Key, Value>::balanceFactor(AVLNode<Key, Value>* node) const {
    return node == nullptr ? 0 : height(node->left) - height(node->right);
}

// Nas rotações, eu faço a troca mecânica dos ponteiros.
// O detalhe crucial aqui é manter os ponteiros 'parent' atualizados, 
// pois minha implementação interativa depende totalmente deles para subir na árvore.
template<typename Key, typename Value>
void AVLDictionary<Key, Value>::rotateRight(AVLNode<Key, Value>* y) {
    AVLNode<Key, Value>* x = y->left;
    AVLNode<Key, Value>* T2 = x->right;

    x->right = y;
    y->left = T2;

    if (T2 != nullptr) T2->parent = y;

    x->parent = y->parent;
    if (y->parent == nullptr) m_root = x;
    else if (y == y->parent->right) y->parent->right = x;
    else y->parent->left = x;

    y->parent = x;

    updateHeight(y);
    updateHeight(x);
}

template<typename Key, typename Value>
void AVLDictionary<Key, Value>::rotateLeft(AVLNode<Key, Value>* x) {
    AVLNode<Key, Value>* y = x->right;
    AVLNode<Key, Value>* T2 = y->left;

    y->left = x;
    x->right = T2;

    if (T2 != nullptr) T2->parent = x;

    y->parent = x->parent;
    if (x->parent == nullptr) m_root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    x->parent = y;

    updateHeight(x);
    updateHeight(y);
}

// balanceamento bottom-Up totalmente iterativo
// Em vez de recursão, eu uso um loop while que vai subindo pelos ponteiros 'parent'.
template<typename Key, typename Value>
void AVLDictionary<Key, Value>::balanceUp(AVLNode<Key, Value>* curr) {
    while (curr != nullptr) {
        updateHeight(curr);
        int balance = balanceFactor(curr);
        AVLNode<Key, Value>* next = curr->parent;

        if (balance > 1) {
            if (balanceFactor(curr->left) >= 0) {
                m_rotations++; // Atualizo a métrica exigida no trabalho
                rotateRight(curr);
            } else {
                m_rotations += 2; 
                rotateLeft(curr->left);
                rotateRight(curr);
            }
        } else if (balance < -1) {
            if (balanceFactor(curr->right) <= 0) {
                m_rotations++; 
                rotateLeft(curr);
            } else {
                m_rotations += 2; 
                rotateRight(curr->right);
                rotateLeft(curr);
            }
        }
        curr = next;
    }
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLDictionary<Key, Value>::findNode(const Key& key) const {
    AVLNode<Key, Value>* curr = m_root;
    while (curr != nullptr) {
        if (key == curr->key) return curr;
        if (key < curr->key) curr = curr->left;
        else curr = curr->right;
    }
    return nullptr;
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLDictionary<Key, Value>::minNode(AVLNode<Key, Value>* node) const {
    if (node == nullptr) return nullptr;
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template<typename Key, typename Value>
AVLDictionary<Key, Value>::AVLDictionary() : m_root(nullptr), m_size(0), m_comparisons(0), m_rotations(0) {}

template<typename Key, typename Value>
AVLDictionary<Key, Value>::~AVLDictionary() {
    clear();
}

template<typename Key, typename Value>
size_t AVLDictionary<Key, Value>::getComparisons() const { return m_comparisons; }

template<typename Key, typename Value>
size_t AVLDictionary<Key, Value>::getRotations() const { return m_rotations; }

template<typename Key, typename Value>
void AVLDictionary<Key, Value>::resetMetrics() { m_comparisons = 0; m_rotations = 0; }

template<typename Key, typename Value>
bool AVLDictionary<Key, Value>::insert(const Key& key, const Value& value) {
    if (m_root == nullptr) {
        m_root = new AVLNode<Key, Value>(key, value);
        m_size++;
        return true;
    }

    AVLNode<Key, Value>* curr = m_root;
    AVLNode<Key, Value>* parent = nullptr;

    // Busca iterativa pela posição correta de inserção
    while (curr != nullptr) {
        parent = curr;
        m_comparisons++; // Contabilizo a métrica sempre antes de comparar
        if (key < curr->key) {
            curr = curr->left;
        } else if (key > curr->key) {
            m_comparisons++; 
            curr = curr->right;
        } else {
            return false; 
        }
    }

    AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(key, value);
    newNode->parent = parent;
    
    if (key < parent->key) parent->left = newNode;
    else parent->right = newNode;
    
    m_size++;

    // Disparo a verificação de balanceamento subindo a partir do pai do novo nó
    balanceUp(parent);
    return true;
}

template<typename Key, typename Value>
bool AVLDictionary<Key, Value>::update(const Key& key, const Value& value) {
    AVLNode<Key, Value>* node = findNode(key);
    if (node == nullptr) return false;
    node->value = value;
    return true;
}

template<typename Key, typename Value>
bool AVLDictionary<Key, Value>::remove(const Key& key) {
    AVLNode<Key, Value>* node = findNode(key);
    if (node == nullptr) return false;

    // Guarda o ponto de partida de onde eu vou ter que subir consertando a árvore
    AVLNode<Key, Value>* balanceStart = nullptr;

    if (node->left != nullptr && node->right != nullptr) {
        AVLNode<Key, Value>* successor = minNode(node->right);
        node->key = successor->key;
        node->value = successor->value;
        node = successor; 
    }

    AVLNode<Key, Value>* child = (node->left != nullptr) ? node->left : node->right;
    
    if (child != nullptr) {
        child->parent = node->parent;
    }

    if (node->parent == nullptr) {
        m_root = child;
        balanceStart = nullptr;
    } else if (node == node->parent->left) {
        node->parent->left = child;
        balanceStart = node->parent;
    } else {
        node->parent->right = child;
        balanceStart = node->parent;
    }

    delete node;
    m_size--;

    // Chamo o meu método iterativo para rebalancear a árvore após a remoção
    balanceUp(balanceStart);
    return true;
}

template<typename Key, typename Value>
size_t AVLDictionary<Key, Value>::size() const { return m_size; }

template<typename Key, typename Value>
bool AVLDictionary<Key, Value>::empty() const { return m_size == 0; }

template<typename Key, typename Value>
bool AVLDictionary<Key, Value>::contains(const Key& key) const {
    return findNode(key) != nullptr;
}

template<typename Key, typename Value>
Value& AVLDictionary<Key, Value>::get(const Key& key) {
    AVLNode<Key, Value>* node = findNode(key);
    if (node == nullptr) throw std::out_of_range("Key not found");
    return node->value;
}

template<typename Key, typename Value>
const Value& AVLDictionary<Key, Value>::get(const Key& key) const {
    AVLNode<Key, Value>* node = findNode(key);
    if (node == nullptr) throw std::out_of_range("Key not found");
    return node->value;
}

template<typename Key, typename Value>
Value& AVLDictionary<Key, Value>::operator[](const Key& key) {
    AVLNode<Key, Value>* node = findNode(key);
    if (node != nullptr) return node->value;
    
    insert(key, Value());
    return findNode(key)->value;
}

// Limpeza da árvore estritamente iterativa
// Utilizo um std::vector atuando como uma Pilha (Stack) manual.
template<typename Key, typename Value>
void AVLDictionary<Key, Value>::clear() {
    if (m_root == nullptr) return;
    
    std::vector<AVLNode<Key, Value>*> stack;
    stack.push_back(m_root);
    
    while (!stack.empty()) {
        AVLNode<Key, Value>* curr = stack.back();
        stack.pop_back();
        
        if (curr->left) stack.push_back(curr->left);
        if (curr->right) stack.push_back(curr->right);
        
        delete curr;
    }
    
    m_root = nullptr;
    m_size = 0;
}

// Percurso Em-Ordem também de forma puramente iterativa com Pilha.
// Isso garante que as chaves da minha árvore já saiam em ordem alfabética para o CSV.
template<typename Key, typename Value>
std::vector<Key> AVLDictionary<Key, Value>::getKeys() const {
    std::vector<Key> keys;
    if (m_root == nullptr) return keys;

    std::vector<AVLNode<Key, Value>*> stack;
    AVLNode<Key, Value>* curr = m_root;

    while (curr != nullptr || !stack.empty()) {
        while (curr != nullptr) {
            stack.push_back(curr);
            curr = curr->left;
        }
        curr = stack.back();
        stack.pop_back();
        
        keys.push_back(curr->key);
        
        curr = curr->right;
    }
    return keys;
}

#endif
