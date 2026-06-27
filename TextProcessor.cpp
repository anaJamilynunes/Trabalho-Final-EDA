#include "TextProcessor.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>

bool TextProcessor::isSeparator(char c)
{
if(std::isspace(
            static_cast<unsigned char>(c)))
        return true;

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
            return true;

        default:
            return false;
    }
}

//normalização
std::string
TextProcessor::normalizeWord(
        std::string word)
{
    for(char& c : word)
    {
        c = std::tolower(
                static_cast<unsigned char>(c));
    }

    return word;
}

//extração do texto
std::vector<std::string>
TextProcessor::extractWords(
        const std::string& filename)
{
    std::ifstream file(filename);

    std::vector<std::string> words;

    if(!file.is_open())
        return words;

    std::string current;
    char c;

    while(file.get(c))
    {
        if(isSeparator(c))
        {
            if(!current.empty())
            {
                words.push_back(
                    normalizeWord(current));

                current.clear();
            }
        }
        else
        {
            current += c;
        }
    }

    if(!current.empty())
    {
        words.push_back(
            normalizeWord(current));
    }

    return words;
}