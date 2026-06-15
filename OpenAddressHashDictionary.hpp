#ifndef OPEN_ADDRESS_HASH_DICTIONARY_HPP
#define OPEN_ADDRESS_HASH_DICTIONARY_HPP

#include <vector>
#include <functional>
#include <stdexcept>
#include <utility>

#include "Dictionary.hpp"

// Implementação de um dicionário utilizando
// tabela hash com endereçamento aberto e sondagem linear.
// O redimensionamento da tabela ocorre automaticamente
// quando o fator de carga máximo é atingido.
template<typename Key, typename Value, typename Hash = std::hash<Key>>
class OpenAddressHashDictionary : public Dictionary<Key, Value> {
private:

    // Estados possíveis de uma posição da tabela hash
    enum State {
        EMPTY,
        OCCUPIED,
        DELETED
    };

    // Estrutura que representa uma entrada da tabela hash
    struct Entry {
        Key key;
        Value value;
        State state;

        Entry()
            : state(EMPTY) {}
    };

    // Vetor que armazena a tabela hash
    std::vector<Entry> m_table;

    // Quantidade atual de elementos armazenados
    size_t m_size;
    // Capacidade total da tabela
    size_t m_capacity;

    // Fator de carga máximo permitido
    float m_max_load_factor;

    // Função hash utilizada
    Hash m_hash;

private:

// Calcula a posição inicial de uma chave na tabela
    size_t hash_code(const Key& key) const {
    return m_hash(key) % m_capacity;
}

// Calcula o fator de carga atual da tabela
    float load_factor() const {
    return static_cast<float>(m_size) / m_capacity;
}
    
// Verifica se um número é primo
    bool is_prime(size_t number) const {

    if(number < 2) {
        return false;
    }

    for(size_t i = 2; i * i <= number; i++) {

        if(number % i == 0) {
            return false;
        }
    }

    return true;
}

// Retorna o próximo número primo maior ou igual ao valor informado
    size_t next_prime(size_t number) const {

    while(!is_prime(number)) {
        number++;
    }

    return number;
}

// Recria a tabela com maior capacidade e reinsere os elementos
    void rehash(size_t new_capacity) {

    std::vector<Entry> old_table = m_table;

    m_capacity = next_prime(new_capacity);
    m_table.clear();
    m_table.resize(m_capacity);

    m_size = 0;

    for(const auto& entry : old_table) {

        if(entry.state == OCCUPIED) {

            insert(
                entry.key,
                entry.value
            );
        }
    }
}

public:

// Construtor da tabela hash
    OpenAddressHashDictionary(
    size_t capacity = 19,
    float max_load_factor = 0.7f
) {
    m_capacity = next_prime(capacity);
    m_size = 0;
    m_max_load_factor = max_load_factor;

    m_table.resize(m_capacity);
}

// Insere um novo elemento na tabela utilizando sondagem linear
    bool insert(
    const Key& key,
    const Value& value
) override {

    if(static_cast<float>(m_size + 1) / m_capacity
    >= m_max_load_factor
) {
    rehash(
    next_prime(m_capacity * 2)
);
}

    size_t index = hash_code(key);

    for(size_t i = 0; i < m_capacity; i++) {

        size_t pos = (index + i) % m_capacity;

        if(
            m_table[pos].state == OCCUPIED &&
            m_table[pos].key == key
        ) {
            return false;
        }

        if(
            m_table[pos].state == EMPTY ||
            m_table[pos].state == DELETED
        ) {
            m_table[pos].key = key;
            m_table[pos].value = value;
            m_table[pos].state = OCCUPIED;

            m_size++;

            return true;
        }
    }

    return false;
}

// Atualiza o valor associado a uma chave existente.
// Retorna false caso a chave não seja encontrada.
bool update(
    const Key& key,
    const Value& value
) override {

    size_t index = hash_code(key);

    for(size_t i = 0; i < m_capacity; i++) {

        size_t pos = (index + i) % m_capacity;

        if(m_table[pos].state == EMPTY) {
            return false;
        }

        if(
            m_table[pos].state == OCCUPIED &&
            m_table[pos].key == key
        ) {
            m_table[pos].value = value;
            return true;
        }
    }

    return false;
}

// Remove uma chave da tabela marcando a posição como DELETED
    bool remove(
    const Key& key
) override {

    size_t index = hash_code(key);

    for(size_t i = 0; i < m_capacity; i++) {

        size_t pos = (index + i) % m_capacity;

        if(m_table[pos].state == EMPTY) {
            return false;
        }

        if(
            m_table[pos].state == OCCUPIED &&
            m_table[pos].key == key
        ) {
            m_table[pos].state = DELETED;

            m_size--;

            return true;
        }
    }

    return false;
}

// Verifica se uma chave existe na tabela
    bool contains(
    const Key& key
) const override {

    size_t index = hash_code(key);

    for(size_t i = 0; i < m_capacity; i++) {

        size_t pos = (index + i) % m_capacity;

        if(m_table[pos].state == EMPTY) {
            return false;
        }

        if(
            m_table[pos].state == OCCUPIED &&
            m_table[pos].key == key
        ) {
            return true;
        }
    }

    return false;
}

// Retorna uma referência para o valor associado à chave
    Value& get(
    const Key& key
) override {

    size_t index = hash_code(key);

    for(size_t i = 0; i < m_capacity; i++) {

        size_t pos = (index + i) % m_capacity;

        if(m_table[pos].state == EMPTY) {
            break;
        }

        if(
            m_table[pos].state == OCCUPIED &&
            m_table[pos].key == key
        ) {
            return m_table[pos].value;
        }
    }

    throw std::out_of_range("Key not found");
}

// Retorna uma referência constante para o valor associado à chave
    const Value& get(
    const Key& key
) const override {

    size_t index = hash_code(key);

    for(size_t i = 0; i < m_capacity; i++) {

        size_t pos = (index + i) % m_capacity;

        if(m_table[pos].state == EMPTY) {
            break;
        }

        if(
            m_table[pos].state == OCCUPIED &&
            m_table[pos].key == key
        ) {
            return m_table[pos].value;
        }
    }

    throw std::out_of_range("Key not found");
}

// Remove todos os elementos da tabela
    void clear() override {
    m_table.clear();
    m_table.resize(m_capacity);

    m_size = 0;
}

// Retorna a quantidade de elementos armazenados
    size_t size() const override {
    return m_size;
}

// Verifica se a tabela está vazia
    bool empty() const override {
    return m_size == 0;
}

// Retorna o valor associado à chave.
// Caso a chave não exista, ela é criada com valor padrão.
    Value& operator[](
    const Key& key
) override {

    size_t index = hash_code(key);

    for(size_t i = 0; i < m_capacity; i++) {

        size_t pos = (index + i) % m_capacity;

        if(m_table[pos].state == EMPTY) {
            break;
        }

        if(
            m_table[pos].state == OCCUPIED &&
            m_table[pos].key == key
        ) {
            return m_table[pos].value;
        }
    }

    insert(key, Value());

    return get(key);
}

};

#endif
