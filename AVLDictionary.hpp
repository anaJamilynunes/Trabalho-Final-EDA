#ifndef AVL_DICTIONARY_HPP
#define AVL_DICTIONARY_HPP

#include <stdexcept>

#include "Dictionary.hpp"

template<typename Key, typename Value>
class AVLDictionary : public Dictionary<Key, Value> {
private:

// Estrutura que representa um nó da árvore AVL.
// Cada nó armazena uma chave, um valor,
// ponteiros para os filhos, ponteiro para o pai
// e a altura utilizada no balanceamento.
    struct Node {
        Key key;
        Value value;

        Node* left;
        Node* right;
        Node* parent;


// Altura do nó na árvore.
// Utilizada para calcular o balanceamento AVL.
        int height;

        Node(
            const Key& k,
            const Value& v
        )
        :
            key(k),
            value(v),
            left(nullptr),
            right(nullptr),
            parent(nullptr),
            height(1)
        {}
    };

    Node* m_root;
    size_t m_size;

    bool m_inserted;

// Retorna a altura de um nó.
// Nós nulos possuem altura 0.
    int height(Node* node) const {

    if(node == nullptr) {
        return 0;
    }

    return node->height;
}

// Atualiza a altura de um nó com base
// nas alturas de seus filhos.
void updateHeight(Node* node) {

    if(node == nullptr) {
        return;
    }

    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    node->height =
        1 +
        (leftHeight > rightHeight
        ? leftHeight
        : rightHeight);
}

// Calcula o fator de balanceamento.
// AVL = altura esquerda - altura direita.
int balanceFactor(Node* node) const {

    if(node == nullptr) {
        return 0;
    }

    return
        height(node->left)
        -
        height(node->right);
}

// Rotação simples para a direita.
// Utilizada nos casos LL.
Node* rotateRight(Node* y) {

    Node* x = y->left;

    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    if(T2 != nullptr) {
        T2->parent = y;
    }

    x->parent = y->parent;
    y->parent = x;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Rotação simples para a esquerda.
// Utilizada nos casos RR.
Node* rotateLeft(Node* x) {

    Node* y = x->right;

    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    if(T2 != nullptr) {
        T2->parent = x;
    }

    y->parent = x->parent;
    x->parent = y;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Insere uma chave na AVL.
// Realiza o rebalanceamento quando necessário.
Node* insert(
    Node* node,
    const Key& key,
    const Value& value
) {

    if(node == nullptr) {

        m_inserted = true;

        m_size++;

        return new Node(
            key,
            value
        );
    }

    if(key < node->key) {

        Node* newLeft =
            insert(
                node->left,
                key,
                value
            );

        node->left = newLeft;

        if(newLeft != nullptr) {
            newLeft->parent = node;
        }
    }
    else if(key > node->key) {

        Node* newRight =
            insert(
                node->right,
                key,
                value
            );

        node->right = newRight;

        if(newRight != nullptr) {
            newRight->parent = node;
        }
    }
    else {

        m_inserted = false;

        return node;
    }

    updateHeight(node);

    int balance =
        balanceFactor(node);

    if(
        balance > 1 &&
        key < node->left->key
    ) {
        return rotateRight(node);
    }

    if(
        balance < -1 &&
        key > node->right->key
    ) {
        return rotateLeft(node);
    }

    if(
        balance > 1 &&
        key > node->left->key
    ) {

        node->left =
            rotateLeft(node->left);

        return rotateRight(node);
    }

    if(
        balance < -1 &&
        key < node->right->key
    ) {

        node->right =
            rotateRight(node->right);

        return rotateLeft(node);
    }

    return node;
}


// Busca um nó pela chave.
Node* findNode(
    Node* node,
    const Key& key
) const {

    if(node == nullptr) {
        return nullptr;
    }

    if(key == node->key) {
        return node;
    }

    if(key < node->key) {
        return findNode(
            node->left,
            key
        );
    }

    return findNode(
        node->right,
        key
    );
}

// Retorna o menor nó de uma subárvore.
// Utilizado para encontrar o sucessor em ordem.
Node* minNode(
    Node* node
) const {

    if(node == nullptr) {
        return nullptr;
    }

    while(node->left != nullptr) {
        node = node->left;
    }

    return node;
}

// Remove um nó da AVL.
// Após a remoção, a árvore é rebalanceada.
Node* removeNode(
    Node* node,
    const Key& key
) {

    if(node == nullptr) {

        return nullptr;
    }

    if(key < node->key) {

        node->left =
            removeNode(
                node->left,
                key
            );
    }
    else if(key > node->key) {

        node->right =
            removeNode(
                node->right,
                key
            );
    }
   else {

    if(
        node->left == nullptr &&
        node->right == nullptr
    ) {

        delete node;

        m_size--;

        return nullptr;
    }

    if(node->left == nullptr) {

    Node* temp = node->right;

    if(temp != nullptr) {
        temp->parent = node->parent;
    }

    delete node;

    m_size--;

    return temp;
}

    if(node->right == nullptr) {

    Node* temp = node->left;

    if(temp != nullptr) {
        temp->parent = node->parent;
    }

    delete node;

    m_size--;

    return temp;
}

    Node* successor =
    minNode(
        node->right
    );

node->key =
    successor->key;

node->value =
    successor->value;

node->right =
    removeNode(
        node->right,
        successor->key
    );
}

    if(node == nullptr) {
    return node;
}

updateHeight(node);

int balance =
    balanceFactor(node);

if(
    balance > 1 &&
    balanceFactor(node->left) >= 0
) {
    return rotateRight(node);
}

if(
    balance > 1 &&
    balanceFactor(node->left) < 0
) {

    node->left =
        rotateLeft(node->left);

    return rotateRight(node);
}

if(
    balance < -1 &&
    balanceFactor(node->right) <= 0
) {
    return rotateLeft(node);
}

if(
    balance < -1 &&
    balanceFactor(node->right) > 0
) {

    node->right =
        rotateRight(node->right);

    return rotateLeft(node);
}

return node;

}

// Insere uma chave com valor padrão.
// Utilizado pelo operador [].
Node* insertDefault(
    Node* node,
    const Key& key
) {

    if(node == nullptr) {

        m_inserted = true;

        m_size++;

        return new Node(
            key,
            Value()
        );
    }

    if(key < node->key) {

        Node* newLeft =
            insertDefault(
                node->left,
                key
            );

        node->left = newLeft;

        if(newLeft != nullptr) {
            newLeft->parent = node;
        }
    }
    else if(key > node->key) {

        Node* newRight =
            insertDefault(
                node->right,
                key
            );

        node->right = newRight;

        if(newRight != nullptr) {
            newRight->parent = node;
        }
    }
    else {
        return node;
    }

    updateHeight(node);

    int balance =
        balanceFactor(node);

    if(
        balance > 1 &&
        key < node->left->key
    ) {
        return rotateRight(node);
    }

    if(
        balance < -1 &&
        key > node->right->key
    ) {
        return rotateLeft(node);
    }

    if(
        balance > 1 &&
        key > node->left->key
    ) {
        node->left =
            rotateLeft(node->left);

        return rotateRight(node);
    }

    if(
        balance < -1 &&
        key < node->right->key
    ) {
        node->right =
            rotateRight(node->right);

        return rotateLeft(node);
    }

    return node;
}

// Libera recursivamente todos os nós da árvore.
void destroy(Node* node) {

    if(node == nullptr) {
        return;
    }

    destroy(node->left);

    destroy(node->right);

    delete node;
}




public:

// Construtor da AVL.
   AVLDictionary() {
    m_root = nullptr;
    m_size = 0;
    m_inserted = false;
}

// Adiciona um novo par chave-valor.
// Retorna false caso a chave já exista.
    bool insert(
    const Key& key,
    const Value& value
) override {

    m_inserted = false;

    m_root =
        insert(
            m_root,
            key,
            value
        );

    return m_inserted;
}

// Atualiza o valor associado a uma chave existente.
// Retorna false caso a chave não seja encontrada.
bool update(
    const Key& key,
    const Value& value
) override {

    Node* node =
        findNode(
            m_root,
            key
        );

    if(node == nullptr) {
        return false;
    }

    node->value = value;

    return true;
}

// Remove uma chave da árvore.
// Retorna false caso a chave não exista.
bool remove(
    const Key& key
) override {

    if(
        !contains(key)
    ) {
        return false;
    }

    m_root =
        removeNode(
            m_root,
            key
        );

    return true;
}

// Retorna a quantidade de elementos armazenados.
size_t size() const override {
    return m_size;
}

// Verifica se a árvore está vazia.
bool empty() const override {
    return m_size == 0;
}

// Verifica se uma chave existe na árvore.
bool contains(
    const Key& key
) const override {

    return
        findNode(
            m_root,
            key
        ) != nullptr;
}

// Retorna o valor associado à chave.
// Lança exceção caso a chave não exista.
Value& get(
    const Key& key
) override {

    Node* node =
        findNode(
            m_root,
            key
        );

    if(node == nullptr) {
        throw std::out_of_range(
            "Key not found"
        );
    }

    return node->value;
}

// Versão constante de acesso ao valor.
const Value& get(
    const Key& key
) const override {

    Node* node =
        findNode(
            m_root,
            key
        );

    if(node == nullptr) {
        throw std::out_of_range(
            "Key not found"
        );
    }

    return node->value;
}

// Retorna o valor associado à chave.
// Caso a chave não exista, cria um valor padrão.
Value& operator[](
    const Key& key
) override {

    Node* node =
        findNode(
            m_root,
            key
        );

    if(node != nullptr) {
        return node->value;
    }

    m_inserted = false;

    m_root =
        insertDefault(
            m_root,
            key
        );

    return get(key);
}

// Remove todos os elementos da árvore.
void clear() override {

    destroy(m_root);

    m_root = nullptr;

    m_size = 0;
}

// Destrutor da AVL.
~AVLDictionary() {

    clear();
}


};

#endif