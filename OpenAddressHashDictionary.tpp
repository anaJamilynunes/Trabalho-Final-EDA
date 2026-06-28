#ifndef OPEN_ADDRESS_HASH_DICTIONARY_TPP
#define OPEN_ADDRESS_HASH_DICTIONARY_TPP

#include "OpenAddressHashDictionary.hpp"

template<typename Key, typename Value, typename Hash>
size_t OpenAddressHashDictionary<Key, Value, Hash>::hash_code(const Key& key) const {
    return m_hash(key) % m_capacity;
}

template<typename Key, typename Value, typename Hash>
float OpenAddressHashDictionary<Key, Value, Hash>::load_factor() const {
    return static_cast<float>(m_size) / m_capacity;
}

// Funções auxiliares matemáticas para garantir que o tamanho da tabela 
// (m_capacity) seja sempre um número primo. Isso ajuda a espalhar melhor 
// as chaves e reduzir drasticamente o número de colisões.
template<typename Key, typename Value, typename Hash>
bool OpenAddressHashDictionary<Key, Value, Hash>::is_prime(size_t number) const {
    if(number < 2) return false;
    for(size_t i = 2; i * i <= number; i++) {
        if(number % i == 0) return false;
    }
    return true;
}

template<typename Key, typename Value, typename Hash>
size_t OpenAddressHashDictionary<Key, Value, Hash>::next_prime(size_t number) const {
    while(!is_prime(number)) {
        number++;
    }
    return number;
}

// O Rehash é a minha válvula de escape. Se a tabela atingir o fator de carga 
// máximo (ex: 70% cheia), eu dobro a capacidade (buscando o próximo primo) 
// e reinsro todas as chaves válidas. Isso garante que a busca continue.
template<typename Key, typename Value, typename Hash>
void OpenAddressHashDictionary<Key, Value, Hash>::rehash(size_t new_capacity) {
    std::vector<OpenAddressHashEntry<Key, Value>> old_table = m_table;

    m_capacity = next_prime(new_capacity);
    m_table.clear();
    m_table.resize(m_capacity);
    m_size = 0;

    for(const auto& entry : old_table) {
        if(entry.state == OCCUPIED) {
            insert(entry.key, entry.value);
        }
    }
}

template<typename Key, typename Value, typename Hash>
OpenAddressHashDictionary<Key, Value, Hash>::OpenAddressHashDictionary(size_t capacity, float max_load_factor) {
    m_capacity = next_prime(capacity);
    m_size = 0;
    m_max_load_factor = max_load_factor;
    m_table.resize(m_capacity);
    m_comparisons = 0; 
    m_collisions = 0;
}

template<typename Key, typename Value, typename Hash>
size_t OpenAddressHashDictionary<Key, Value, Hash>::getComparisons() const {
    return m_comparisons;
}

template<typename Key, typename Value, typename Hash>
size_t OpenAddressHashDictionary<Key, Value, Hash>::getCollisions() const { 
    return m_collisions; 
}

template<typename Key, typename Value, typename Hash>
float OpenAddressHashDictionary<Key, Value, Hash>::getLoadFactor() const { 
    return load_factor(); 
}

template<typename Key, typename Value, typename Hash>
void OpenAddressHashDictionary<Key, Value, Hash>::resetMetrics() {
    m_comparisons = 0;
    m_collisions = 0;
}

// Inserção com Sondagem Linear: se o índice inicial deu colisão,
// eu avanço (i++) verificando os vizinhos até achar um espaço VAZIO ou DELETADO.
template<typename Key, typename Value, typename Hash>
bool OpenAddressHashDictionary<Key, Value, Hash>::insert(const Key& key, const Value& value) {
    // Verifico se preciso fazer o Rehash antes de tentar inserir
    if(static_cast<float>(m_size + 1) / m_capacity >= m_max_load_factor) {
        rehash(next_prime(m_capacity * 2));
    }

    size_t index = hash_code(key);
    size_t first_deleted = m_capacity; // Guarda a posição do primeiro 'buraco' que eu achar

    for(size_t i = 0; i < m_capacity; i++) {
        size_t pos = (index + i) % m_capacity; // Cálculo circular da sondagem linear

        // Se andou no i (i > 0) e bateu em algo que não está vazio, significa que houve colisão!
        if (i > 0 && m_table[pos].state != EMPTY) {
            m_collisions++;
        }

        if(m_table[pos].state == OCCUPIED) {
            m_comparisons++; // Incremento a métrica do trabalho antes de comparar
            if(m_table[pos].key == key) {
                return false; // A palavra já existe, aborto a inserção
            }
        } 
        else if(m_table[pos].state == DELETED && first_deleted == m_capacity) {
            // Achei um espaço marcado como deletado. Guardo ele, mas continuo 
            // procurando pra ter certeza que a palavra já não está mais pra frente.
            first_deleted = pos;
        } 
        else if(m_table[pos].state == EMPTY) {
            // Achei um espaço totalmente vazio. Uso o primeiro 'buraco' deletado 
            // que encontrei antes (se houver), se não, uso esse espaço vazio mesmo.
            size_t insert_pos = (first_deleted != m_capacity) ? first_deleted : pos;
            m_table[insert_pos].key = key;
            m_table[insert_pos].value = value;
            m_table[insert_pos].state = OCCUPIED;
            m_size++;
            return true;
        }
    }

    // Fallback: Se a tabela estava lotada de buracos (DELETED) mas não tinha EMPTY
    if (first_deleted != m_capacity) {
        m_table[first_deleted].key = key;
        m_table[first_deleted].value = value;
        m_table[first_deleted].state = OCCUPIED;
        m_size++;
        return true;
    }

    return false;
}

template<typename Key, typename Value, typename Hash>
bool OpenAddressHashDictionary<Key, Value, Hash>::update(const Key& key, const Value& value) {
    size_t index = hash_code(key);

    for(size_t i = 0; i < m_capacity; i++) {
        size_t pos = (index + i) % m_capacity;

        if (i > 0 && m_table[pos].state != EMPTY) {
            m_collisions++;
        }

        if(m_table[pos].state == EMPTY) {
            return false;
        }

        if(m_table[pos].state == OCCUPIED) {
            m_comparisons++; 
            if(m_table[pos].key == key) {
                m_table[pos].value = value;
                return true;
            }
        }
    }
    return false;
}

// Eu não limpo a variável de verdade, 
// apenas mudo o estado dela para DELETED. Isso evita que a sondagem 
// linear quebre ao tentar buscar elementos que foram empurrados pra frente por colisões.
template<typename Key, typename Value, typename Hash>
bool OpenAddressHashDictionary<Key, Value, Hash>::remove(const Key& key) {
    size_t index = hash_code(key);

    for(size_t i = 0; i < m_capacity; i++) {
        size_t pos = (index + i) % m_capacity;

        if (i > 0 && m_table[pos].state != EMPTY) {
            m_collisions++;
        }

        if(m_table[pos].state == EMPTY) {
            return false; // Bati num espaço vazio, a palavra com certeza não está aqui
        }

        if(m_table[pos].state == OCCUPIED) {
            m_comparisons++; 
            if(m_table[pos].key == key) {
                m_table[pos].state = DELETED; // Marcação mágica!
                m_size--;
                return true;
            }
        }
    }
    return false;
}

template<typename Key, typename Value, typename Hash>
bool OpenAddressHashDictionary<Key, Value, Hash>::contains(const Key& key) const {
    size_t index = hash_code(key);

    for(size_t i = 0; i < m_capacity; i++) {
        size_t pos = (index + i) % m_capacity;

        if (i > 0 && m_table[pos].state != EMPTY) {
            m_collisions++;
        }

        if(m_table[pos].state == EMPTY) {
            return false;
        }

        if(m_table[pos].state == OCCUPIED) {
            m_comparisons++; 
            if(m_table[pos].key == key) {
                return true;
            }
        }
    }
    return false;
}

template<typename Key, typename Value, typename Hash>
Value& OpenAddressHashDictionary<Key, Value, Hash>::get(const Key& key) {
    size_t index = hash_code(key);

    for(size_t i = 0; i < m_capacity; i++) {
        size_t pos = (index + i) % m_capacity;

        if (i > 0 && m_table[pos].state != EMPTY) {
            m_collisions++;
        }

        if(m_table[pos].state == EMPTY) {
            break;
        }

        if(m_table[pos].state == OCCUPIED) {
            m_comparisons++; 
            if(m_table[pos].key == key) {
                return m_table[pos].value;
            }
        }
    }
    throw std::out_of_range("Key not found");
}

template<typename Key, typename Value, typename Hash>
const Value& OpenAddressHashDictionary<Key, Value, Hash>::get(const Key& key) const {
    size_t index = hash_code(key);

    for(size_t i = 0; i < m_capacity; i++) {
        size_t pos = (index + i) % m_capacity;

        if (i > 0 && m_table[pos].state != EMPTY) {
            m_collisions++;
        }

        if(m_table[pos].state == EMPTY) {
            break;
        }

        if(m_table[pos].state == OCCUPIED) {
            m_comparisons++; 
            if(m_table[pos].key == key) {
                return m_table[pos].value;
            }
        }
    }
    throw std::out_of_range("Key not found");
}

template<typename Key, typename Value, typename Hash>
void OpenAddressHashDictionary<Key, Value, Hash>::clear() {
    m_table.clear();
    m_table.resize(m_capacity); // Recrio o vetor vazio, mas mantendo a capacidade inicial
    m_size = 0;
}

template<typename Key, typename Value, typename Hash>
size_t OpenAddressHashDictionary<Key, Value, Hash>::size() const {
    return m_size;
}

template<typename Key, typename Value, typename Hash>
bool OpenAddressHashDictionary<Key, Value, Hash>::empty() const {
    return m_size == 0;
}

template<typename Key, typename Value, typename Hash>
Value& OpenAddressHashDictionary<Key, Value, Hash>::operator[](const Key& key) {
    size_t index = hash_code(key);

    for(size_t i = 0; i < m_capacity; i++) {
        size_t pos = (index + i) % m_capacity;

        if (i > 0 && m_table[pos].state != EMPTY) {
            m_collisions++;
        }

        if(m_table[pos].state == EMPTY) {
            break;
        }

        if(m_table[pos].state == OCCUPIED) {
            m_comparisons++; 
            if(m_table[pos].key == key) {
                return m_table[pos].value;
            }
        }
    }

    insert(key, Value());
    return get(key);
}

// Coleta iterativa de todas as chaves válidas (OCCUPIED) da tabela.
// Como Tabelas Hash não garantem ordem, a ordenação alfabética final 
// é feita lá na main usando o std::sort.
template<typename Key, typename Value, typename Hash>
std::vector<Key> OpenAddressHashDictionary<Key, Value, Hash>::getKeys() const {
    std::vector<Key> keys;
    for(size_t i = 0; i < m_capacity; i++) {
        if(m_table[i].state == OCCUPIED) {
            keys.push_back(m_table[i].key);
        }
    }
    return keys;
}

#endif