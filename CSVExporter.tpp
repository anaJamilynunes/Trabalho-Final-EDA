#ifndef CSV_EXPORTER_TPP
#define CSV_EXPORTER_TPP

#include "CSVExporter.hpp"
#include <fstream>
#include <vector>
#include <algorithm> // Para usar o std::sort

template<typename Key, typename Value>
bool CSVExporter<Key, Value>::exportVocabulary(
    Dictionary<Key, Value>& dictionary, 
    const std::string& filename,
    bool shouldSort) 
{
    // Abre o arquivo de vocabulário
    std::ofstream vocab(filename);

    if (!vocab.is_open()) {
        return false;
    }

    // Pega as chaves de dentro da estrutura usando a função que criamos
    std::vector<Key> keys = dictionary.getKeys();

    // Se for uma tabela Hash (que vem bagunçada), ordena em ordem alfabética
    if (shouldSort) {
        std::sort(keys.begin(), keys.end());
    }

    // Grava no arquivo exatamente no formato palavra,frequência
    for (const auto& key : keys) {
        vocab << key << "," << dictionary.get(key) << "\n";
    }

    vocab.close();
    return true;
}

#endif
