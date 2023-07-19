#include <cstring> // For strcmp
#include <iostream>
#include <string>
#include <unordered_set>

bool isCppKeyword(const std::string& word) {
    static const std::unordered_set<std::string> keywords = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if", "int",
        "long", "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile",
        "while", "bool", "true", "false", "namespace", "using", "class", "public",
        "private", "protected", "virtual", "template"
    };

    return keywords.find(word) != keywords.end();
}

void findAndPrintKeywords(const std::string& code) {
    std::string word;
    for (char ch : code) {
        if (std::isalpha(ch) || ch == '_') {
            word.push_back(ch);
        } else {
            if (!word.empty() && isCppKeyword(word)) {
                // use snippets.hpp to generate lua code based on the cpp keywords.
                std::cout << "Found C++ keyword: " << word << std::endl;
            }
            word.clear();
        }
    }
}

bool endsWithCpp(const char* str) {
    if (str == nullptr)
        return false;

    size_t len = strlen(str);
    if (len < 4)
        return false;

    const char* suffix = str + (len - 4);
    return (strcmp(suffix, ".cpp") == 0);
}

void compile_file(const char* filePath, std::string fileContents) {
    if(endsWithCpp(filePath)) {
        std::cout << filePath << std::endl;
        std::cout << fileContents.c_str() << std::endl;
        findAndPrintKeywords(fileContents);
    }
}