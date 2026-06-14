#include <cstddef>
#include "RBNode.hpp"
#include <stack>
#include <iostream>


template<typename Key, typename Value>
RBTreeDictionary<Key, Value>::RBTreeDictionary()
{
    //criando nó nil na tree vazia
    //definindo a cor inicial (preto) e seus ponteiros
    NIL = new RBNode<Key, Value>();

    NIL->color = BLACK;

    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;

    root = NIL; //a raiz recebera o nil

    nodeCount = 0; //quant de elementos armazenados 
}

template<typename Key, typename Value>
RBTreeDictionary<Key, Value>::~RBTreeDictionary()
{
    //criando o destrutor
    clear();

    delete NIL;
}

template<typename Key, typename Value>
RBNode<Key, Value>*
RBTreeDictionary<Key, Value>::searchNode(
    const Key& key
) const
{
    //implementação da busca
    RBNode<Key, Value>* current = root; //recebe a raiz

    while(current != NIL) {
        if(key == current->key) {
            return current;
        }

        if(key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NIL;
}

template<typename Key, typename Value>
bool RBTreeDictionary<Key, Value>::contains(
    const Key& key
) const
{
    //se retornar um nó diferente de nil a chave existe
    //retorno booleano
    return searchNode(key) != NIL;
}

template<typename Key, typename Value>
void RBTreeDictionary<Key, Value>::leftRotate(
    RBNode<Key, Value>* x
)
{   //rotação left
    RBNode<Key, Value>* y = x->right;

    x->right = y->left;

    if(y->left != NIL) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if(x->parent == NIL) {
        root = y;
    } else if(x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;

    x->parent = y;
}

template<typename Key, typename Value>
void RBTreeDictionary<Key, Value>::rightRotate(
    RBNode<Key, Value>* y
)
{ //rotação right
    RBNode<Key, Value>* x = y->left;

    y->left = x->right;

    if(x->right != NIL) {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if(y->parent == NIL) {
        root = x;
    } else if(y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }

    x->right = y;

    y->parent = x;
}

template<typename Key, typename Value>
bool RBTreeDictionary<Key, Value>::insert(
    const Key& key,
    const Value& value
)
{
    //inserção (chave, valor)
    //criando o nó
    RBNode<Key, Value>* z =
        new RBNode<Key, Value>();

    //inicialização
    z->key = key;
    z->value = value;

    RBNode<Key, Value>* x = root;
    RBNode<Key, Value>* y = NIL;

    //garantir que o dic nao duplique valores
    //verificar se isso acontece:
    while(x != NIL) {
        y = x;

        if(key < x->key) {
            x = x->left;
        } else if(key > x->key) {
            x = x->right;
        } else {
            delete z;
            return false;
        }
    }

    z->parent = y;

    if(y == NIL) {
        root = z;
    } else if(key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    //inicialização dos filhos
    z->left = NIL;
    z->right = NIL;

    //cor do novo nó
    z->color = RED;

    //balancemanto
    insertFixup(z);

    //contador para atualizar o tamanho 
    nodeCount++;

    return true;
}

template<typename Key, typename Value>
void RBTreeDictionary<Key, Value>::insertFixup(
    RBNode<Key, Value>* z
)
{
    while(z->parent->color == RED) { //enquanto o pai de z for red
        if(z->parent == z->parent->parent->left) { //z é filho esq?
            RBNode<Key, Value>* y = //y será o tio de z
                z->parent->parent->right;

            if(y->color == RED) { //caso 01: tio red?
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent;
            } else { //caso "zig-zag"
                if(z == z->parent->right) { //caso 03: se z for filho dir
                    z = z->parent;
                    leftRotate(z);
                }

                //caso 02: z é filho esq
                z->parent->color = BLACK;

                z->parent->parent->color = RED;

                rightRotate(
                    z->parent->parent
                );
            }
        } else {
            //caso de simetria: z é filho dir?
            RBNode<Key, Value>* y = z->parent->parent->left; // o tio agora é o esq

                if (y->color == RED) { // caso 1: tio é vermelho
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else { //caso 2 e 3: tio é preto
                    if (z == z->parent->left) { //se "zig-zag" z é filho esq
                        z = z->parent;
                        rightRotate(z);
                    }
                    //caso 3: "linha" z é filho dir
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
        }
    }

    //recolore a raiz
    root->color = BLACK;
}

template<typename Key, typename Value>
RBNode<Key, Value>*
RBTreeDictionary<Key, Value>::minimum(
    RBNode<Key, Value>* node
) const
{  //para encontrar e definir o sucessor no balancemanto após a remoção
    //menor elemento mais a esq da arv dir
    while(node->left != NIL) {
        node = node->left;
    }
    return node;
}

template<typename Key, typename Value>
bool RBTreeDictionary<Key, Value>::remove(
    const Key& key
)
{
    //para remover a chave do dicionario
    //primeiro devmos localizar o nó
    //se nao existir é retornado false
    //remove apenas uma chave
    RBNode<Key, Value>* z =
        searchNode(key);

    if(z == NIL)
        return false;

    RBNode<Key, Value>* y;
    RBNode<Key, Value>* x;

    if(z->left == NIL || z->right == NIL)
        y = z;
    else
        y = minimum(z->right);

    if(y->left != NIL)
        x = y->left;
    else
        x = y->right;

    x->parent = y->parent;

    if(y->parent == NIL)
        root = x;
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    if(y != z) {
        z->key = y->key;
        z->value = y->value;
    }

    Color removedColor = y->color;

    delete y;

    if(removedColor == BLACK) {
        deleteFixup(x);
    }

    nodeCount--;
    return true;
}

template<typename Key, typename Value>
void RBTreeDictionary<Key, Value>::deleteFixup(
    RBNode<Key, Value>* x
)
{
    while(x != root && x->color == BLACK) {
        if(x == x->parent->left) { //x é filho esq
            RBNode<Key, Value>* w =
                x->parent->right;

            if(w->color == RED) { //caso 1: w = irmao do nó
                w->color = BLACK;
                x->parent->color = RED;

                leftRotate(
                    x->parent
                );

                w = x->parent->right;
            }

            if(w->left->color == BLACK && w->right->color == BLACK) { 
                //caso 2: w e seus dois filhos sao black
                w->color = RED;

                x = x->parent;
            } else { //filhos de w tem cores !=
                if(w->right->color == BLACK) { //caso 3: esq = red e dir = black
                    w->left->color =
                        BLACK;

                    w->color = RED;

                    rightRotate(w);

                    w = x->parent->right;
                }
                
                //caso 4: filho dir é red
                w->color =
                    x->parent->color;

                x->parent->color =
                    BLACK;

                w->right->color =
                    BLACK;

                leftRotate(
                    x->parent
                );

                x = root;
            }
        } else {
            // caso simétrico
            RBNode<Key, Value>* w = x->parent->left; //o irmão é o esquerdo

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }

    x->color = BLACK;
}

//remove todos os elementos
//arvore ficara vazia
template<typename Key, typename Value>
void RBTreeDictionary<Key, Value>::clear()
{
    if(root == NIL) {
        return;
    }

    std::stack<RBNode<Key, Value>*> st; //cria a pilha

    st.push(root); //emplilha

    while(!st.empty()) {
        RBNode<Key, Value>* current = //aux segura o topo
            st.top(); 

        st.pop(); //desempilha/remove o nó do topo

        if(current->left != NIL) {
            st.push(current->left);
        }

        if(current->right != NIL) {
            st.push(current->right);
        }

        //libera quem foi retirado da pilha
        delete current;
    }

    root = NIL;
    nodeCount = 0;
}

//get nao const
template<typename Key, typename Value>
Value& RBTreeDictionary<Key, Value>::get(
    const Key& key
)
{
    RBNode<Key,Value>* node =
        searchNode(key);

    if(node == NIL) {
        throw std::out_of_range(
            "Key not found"
        );
    }

    return node->value;
}

//get const
template<typename Key, typename Value>
const Value&
RBTreeDictionary<Key, Value>::get(
    const Key& key
) const
{
    RBNode<Key,Value>* node =
        searchNode(key);

    if(node == NIL)
    {
        throw std::out_of_range(
            "Key not found"
        );
    }

    return node->value;
}

template<typename Key, typename Value>
bool RBTreeDictionary<Key, Value>::update(
    const Key& key,
    const Value& value
)
{
    //e assim poderemos atualizar um valor existente
    //fazer a buscar na chave desejada e verificar
    //se não é nula
    //e passar o novo valor para value
    RBNode<Key, Value>* node =
        searchNode(key);

    if(node == NIL) {
        return false;
    }

    node->value = value;
    return true;
}

template<typename Key, typename Value>
size_t RBTreeDictionary<Key, Value>::size() const
{
    //retornamos o contador que já está sendo atualizado
    //dentro da inserção e da remoção
    return nodeCount;
}

//funções teste para imprimir
template<typename Key, typename Value>
void RBTreeDictionary<Key, Value>::printInOrder()
{
    printInOrder(root);
    std::cout << "\n";
}

template<typename Key, typename Value>
void RBTreeDictionary<Key, Value>::printInOrder(
    RBNode<Key, Value>* node
)
{
    if(node == NIL) {
        return;
    }

    printInOrder(node->left);

    std::cout
    << "("
    << node->key
    << ", "
    << node->value
    << ", "
    << (node->color == RED ? "R" : "B")
    << ") ";
    printInOrder(node->right);
}

//verifica  se a arvore está vazia
template<typename Key, typename Value>
bool RBTreeDictionary<Key, Value>::empty() const
{
    return nodeCount == 0;
}

//inserção automatica caso a busca nao exista
template<typename Key, typename Value>
Value&
RBTreeDictionary<Key, Value>::operator[](
    const Key& key
)
{
    RBNode<Key,Value>* node =
        searchNode(key);

    if(node == NIL) {
        insert(key, Value());
        node = searchNode(key);
    }

    return node->value;
}


