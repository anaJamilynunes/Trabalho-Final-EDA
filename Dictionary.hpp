#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <cstddef>

template<typename Key, typename Value>
class Dictionary {
public:

    virtual bool insert(
        const Key& key,
        const Value& value
    ) = 0;

    virtual bool update(
        const Key& key,
        const Value& value
    ) = 0;

    virtual bool remove(
        const Key& key
    ) = 0;

    virtual bool contains(
        const Key& key
    ) const = 0;

    virtual Value& get(
        const Key& key
    ) = 0;

    virtual const Value& get(
        const Key& key
    ) const = 0;

    virtual void clear() = 0;

    virtual size_t size() const = 0;

    virtual bool empty() const = 0;

    virtual Value& operator[](
        const Key& key
    ) = 0;

    virtual ~Dictionary() {}

    virtual std::vector<Key> getKeys() const = 0;
};

#endif