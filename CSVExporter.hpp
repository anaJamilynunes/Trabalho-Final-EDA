#ifndef CSV_EXPORTER_HPP
#define CSV_EXPORTER_HPP

#include <string>
#include "Dictionary.hpp"

template<typename Key, typename Value>
class CSVExporter {
public:
    // Método estático para exportar o vocabulário sem precisar instanciar a classe
    static bool exportVocabulary(
        Dictionary<Key, Value>& dictionary, 
        const std::string& filename,
        bool shouldSort = false
    );
};

#include "CSVExporter.tpp"

#endif
