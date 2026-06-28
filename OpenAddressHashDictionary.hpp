#ifndef OPEN_ADDRESS_HASH_DICTIONARY_HPP
#define OPEN_ADDRESS_HASH_DICTIONARY_HPP

#include <vector>
#include <functional>
#include <stdexcept>
#include <utility>
#include "Dictionary.hpp"

// =======================================================
// OPÇÃO NUCLEAR: Colocamos os estados e o Struct diretamente aqui!
// Assim o C++ é OBRIGADO a ler isso antes da Tabela Hash.
// =======================================================
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

// Agora a classe da Tabela Hash logo em seguida:
template<typename Key, typename Value, typename Hash = std::hash<Key>>
class OpenAddressHashDictionary : public Dictionary<Key, Value> {
private:
    std::vector<OpenAddressHashEntry<Key, Value>> m_table;
    
    size_t m_size;
    size_t m_capacity;
    float m_max_load_factor;
    Hash m_hash;

    mutable size_t m_comparisons;
    mutable size_t m_collisions;

    size_t hash_code(const Key& key) const;
    float load_factor() const;
    bool is_prime(size_t number) const;
    size_t next_prime(size_t number) const;
    void rehash(size_t new_capacity);

public:
    OpenAddressHashDictionary(size_t capacity = 19, float max_load_factor = 0.7f);

    size_t getComparisons() const;
    size_t getCollisions() const;
    float getLoadFactor() const;
    void resetMetrics();

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

#include "OpenAddressHashDictionary.tpp"

#endif