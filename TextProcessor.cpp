#include "TextProcessor.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>

//verifica se o caractere é uma letra
static bool isLetter(unsigned char c) {
    return
        (c >= 'A' && c <= 'Z')
        ||
        (c >= 'a' && c <= 'z')
        ||
        c >= 128;
}
//==================================================
// VERIFICA SE O CARACTERE É SEPARADOR
//==================================================

bool TextProcessor::isSeparator(char c)
{
    if(std::isspace(
            static_cast<unsigned char>(c)))
    {
        return true;
    }

    switch(c)
    {
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

//==================================================
// CONVERTE PARA MINÚSCULAS
//==================================================

std::string
TextProcessor::normalizeWord(
    std::string word)
{
    for(unsigned char& c :
        reinterpret_cast<
            std::basic_string<unsigned char>&
        >(word))
    {
        // somente ASCII
        if(c >= 'A' && c <= 'Z')
        {
            c = c - 'A' + 'a';
        }
    }

    return word;
}

//==================================================
// VERIFICA SE A PALAVRA É VÁLIDA
//==================================================

static bool isValidWord(
    const std::string& word) {
    for(unsigned char c : word) {
        if(isLetter(c)) {
            return true;
        }
    }

    return false;
}

//==================================================
// EXTRAÇÃO DAS PALAVRAS
//==================================================

std::vector<std::string>
TextProcessor::extractWords(
    const std::string& filename)
{
    std::ifstream file(filename);

    std::vector<std::string> words;

    if(!file.is_open())
    {
        return words;
    }

    std::string current;
    char c;

    while(file.get(c))
    {
        // separadores normais
        if(isSeparator(c))
        {
            if(!current.empty())
            {
                current =
                    normalizeWord(current);

                if(isValidWord(current))
                {
                    words.push_back(
                        current);
                }

                current.clear();
            }

            continue;
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

    // última palavra
    if(!current.empty())
    {
        current =
            normalizeWord(current);

        if(isValidWord(current))
        {
            words.push_back(
                current);
        }
    }

    return words;
}