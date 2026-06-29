#include "TextProcessor.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>

/**
 * Identifica se um byte corresponde a um caractere alfabético.
 * Aceita o intervalo ASCII padrão (A-Z, a-z) e estende a validação para 
 * valores >= 128 para preservar caracteres acentuados (UTF-8 / Extended ASCII).
 */

//verifica se o caractere é uma letra válida
//incluindo acentuação
static bool isLetter(unsigned char c) {
    return
        (c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        c >= 128;
}

// VERIFICA SE O CARACTERE É SEPARADOR
//std::isspace(...): Uma função padrão do C++ que checa 
//se o caractere é um espaço em branco, uma tabulação (\t) 
//ou uma quebra de linha (\n). Se for, ela retorna true
bool TextProcessor::isSeparator(char c)
{
    if(std::isspace( static_cast<unsigned char>(c))) {
        return true;
    }

    //se nao for espaço branco
    switch(c) {
        case '.':
        case ',':
        case ';':
        case ':':
        case '!':
        case '?':
        case '(':
        case ')':
        case '[':
        case ']':
        case '{':
        case '}':
        case '"':
        case '\'':
        case '*':
        case '+':
        case '=':
        case '/':
        case '\\':
        case '_':
        case '#':
        case '$':
        case '%':
        case '&':
        case '@':
        case '^':
        case '~':
        case '`':
        case '<':
        case '>':
        case '|':
            return true;

        default:
            return false;
    }
}

// CONVERTE PARA MINÚSCULAS
/**
 * Transforma caracteres ASCII maiúsculos em minúsculos.
 * Realiza cast seguro para manipulação direta de bytes, afetando apenas a tabela ASCII base.
 */
std::string
TextProcessor::normalizeWord(
    std::string word)
{
    for(unsigned char& c :
        reinterpret_cast<
            std::basic_string<unsigned char>&
        >(word)) {
        // somente ASCII
        if(c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
    }

    return word;
}

// VERIFICA SE A PALAVRA É VÁLIDA
/**
 * Valida se o token extraído contém ao menos um caractere legível.
 * Evita que strings compostas unicamente por símbolos órfãos entrem no dicionário.
 */
static bool isValidWord(
    const std::string& word) {
    for(unsigned char c : word) {
        if(isLetter(c)) {
            return true;
        }
    }

    return false;
}

// EXTRAÇÃO DAS PALAVRAS
/**
 * Processa o arquivo texto, tokenizando e isolando palavras limpas.
 * Implementa uma máquina de estados simples via leitura de fluxo de caracteres.
 * Trata hífens de forma especial para preservar palavras compostas (ex: "guarda-chuva").
 */
std::vector<std::string>
TextProcessor::extractWords(
    const std::string& filename)
{
    std::ifstream file(filename); //tenta abrir o arquivo

    std::vector<std::string> words; 

    if(!file.is_open()) { //verifica se o arquivo existe
        return words;
    }

    std::string current; //aux para montar a palavra caractere por caractere
    char c;

    while(file.get(c)) { //lê o arquivo caractere por caractere,
        // separadores normais
        if(isSeparator(c)) {
            if(!current.empty()) { //se a contagem de carac. nao estiver vazia
                current =
                    normalizeWord(current); //entao é feita a normalização

                if(isValidWord(current)) {
                    words.push_back( //e inserida no vetor final
                        current);
                }

                current.clear(); //pode esvaziar e recomeçar
            }

            continue; //próximo caractere
        }

        // tratamento especial do hífen
        if(c == '-') {
            // hífen isolado
            if(current.empty()) {
                continue;
            }

            // preserva apenas se houver letra antes
            unsigned char previous =
                static_cast<unsigned char>(
                    current.back());

            if(isLetter(previous)) {
                current += c;
            }

            continue;
        }

        // caractere normal
        current += c;
    }

    // Interceptação de resíduos ao atingir o EOF (Fim de Arquivo) sem delimitador final
    if(!current.empty())
    {
        current =
            normalizeWord(current);

        if(isValidWord(current)) {
            words.push_back(
                current);
        }
    }

    return words;
}