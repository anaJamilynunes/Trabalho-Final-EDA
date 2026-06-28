#ifndef AVL_DICTIONARY_HPP
#define AVL_DICTIONARY_HPP

#include <stdexcept>
#include <vector>

#include "Dictionary.hpp"
#include "AVLNode.hpp" // Incluindo o seu novo arquivo de nó solto

// Classe concreta da AVL que herda da interface abstrata Dictionary 
// para permitir o uso de polimorfismo dinâmico na main.
template<typename Key, typename Value>
class AVLDictionary : public Dictionary<Key, Value> {
private:
    AVLNode<Key, Value>* m_root;
    size_t m_size;
    
    // Contadores de métricas para a análise do projeto
    size_t m_comparisons;
    size_t m_rotations;

    // Declarações dos métodos privados (repare que usam AVLNode agora)
    int height(AVLNode<Key, Value>* node) const;
    void updateHeight(AVLNode<Key, Value>* node);
    int balanceFactor(AVLNode<Key, Value>* node) const;
    void rotateRight(AVLNode<Key, Value>* y);
    void rotateLeft(AVLNode<Key, Value>* x);
    void balanceUp(AVLNode<Key, Value>* curr);
    AVLNode<Key, Value>* findNode(const Key& key) const;
    AVLNode<Key, Value>* minNode(AVLNode<Key, Value>* node) const;

public:
    AVLDictionary();
    ~AVLDictionary();

    // Utilitário para exportação do CSV sem expor a estrutura interna dos nós
    std::vector<Key> getKeys() const override;
    
    // Métodos extras para expor as métricas no relatório final
    size_t getComparisons() const;
    size_t getRotations() const;
    void resetMetrics();

    // Declarações dos métodos da interface Dictionary
    bool insert(const Key& key, const Value& value) override;
    bool update(const Key& key, const Value& value) override;
    bool remove(const Key& key) override;
    size_t size() const override;
    bool empty() const override;
    bool contains(const Key& key) const override;
    Value& get(const Key& key) override;
    const Value& get(const Key& key) const override;
    Value& operator[](const Key& key) override;
    void clear() override;
};

// Puxa a implementação no final
#include "AVLDictionary.tpp"

#endif
