#ifndef TEXTPROCESSOR_HPP
#define TEXTPROCESSOR_HPP

#include <string>
#include <vector>

/**
 * TextProcessor.hpp
 * Mecanismo de parsing, filtragem e tratamento de arquivos de texto.
 * Responsável pelo ciclo de vida inicial dos dados: abertura do arquivo, 
 * tokenização baseada em delimitadores e limpeza de caracteres especiais.
 * @author Ana Jamily
 */

class TextProcessor
{
public:
    /**
     * Abre um arquivo texto e extrai todas as palavras válidas isoladas.
     * filename Caminho relativo ou absoluto do arquivo de origem.
     * std::vector<std::string> Lista de palavras devidamente normalizadas.
     * std::runtime_error Se o arquivo não puder ser aberto ou lido.
     */
    static std::vector<std::string>
    extractWords(const std::string& filename);

private:

    // Identifica caracteres de pontuação, quebras de linha e espaços para segmentação
    static bool isSeparator(char c);

    // Remove acentuações, pontuações embutidas e converte a string para caixa baixa
    static std::string
    normalizeWord(std::string word);
};

#endif