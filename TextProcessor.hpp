#ifndef TEXTPROCESSOR_HPP
#define TEXTPROCESSOR_HPP

#include <string>
#include <vector>

class TextProcessor
{
public:

    static std::vector<std::string>
    extractWords(const std::string& filename);

private:

    static bool isSeparator(char c);

    static std::string
    normalizeWord(std::string word);
};

#endif