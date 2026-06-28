#ifndef OPEN_ADDRESS_HASH_DICTIONARY_HPP
#define OPEN_ADDRESS_HASH_DICTIONARY_HPP

#include <vector>
#include <functional>
#include <stdexcept>
#include <utility>
#include "Dictionary.hpp"


enum OpenAddressState {
    EMPTY,
    OCCUPIED,
    DELETED
};

template<typename Key, typename Value>
struct OpenAddressHashEntry {
    Key key;
    Value value;
    OpenAddressState state;

    OpenAddressHashEntry() : state(EMPTY) {}
};
// =======================================================


// Implementação de um dicionário utilizando
// tabela hash com endereçamento aberto e sondagem linear.
template<typename Key, typename Value, typename Hash = std::hash<Key>>
class OpenAddressHashDictionary : public Dictionary<Key, Value> {
private:
    std::vector<OpenAddressHashEntry<Key, Value>> m_table;
    
    size_t m_size;
    size_t m_capacity;
    float m_max_load_factor;
    Hash m_hash;

    // Contador de comparações e colisoes
    mutable size_t m_comparisons;
    mutable size_t m_collisions;

     // Declarações dos métodos privados
    size_t hash_code(const Key& key) const;
    float load_factor() const;
    bool is_prime(size_t number) const;
    size_t next_prime(size_t number) const;
    void rehash(size_t new_capacity);

public:
    //construtor
    OpenAddressHashDictionary(size_t capacity = 19, float max_load_factor = 0.7f);

    // Métricas exigidas pelo projeto para a análise de desempenho
    size_t getComparisons() const;
    size_t getCollisions() const;
    float getLoadFactor() const;
    void resetMetrics();

    // Declarações dos métodos herdados
    bool insert(const Key& key, const Value& value) override;
    bool update(const Key& key, const Value& value) override;
    bool remove(const Key& key) override;
    bool contains(const Key& key) const override;
    Value& get(const Key& key) override;
    const Value& get(const Key& key) const override;
    void clear() override;
    size_t size() const override;
    bool empty() const override;
    Value& operator[](const Key& key) override;
    std::vector<Key> getKeys() const override;
};

// Inclusão da implementação dos templates
#include "OpenAddressHashDictionary.tpp"

#endif