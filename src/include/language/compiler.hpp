#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "./snippets.hpp"

bool isCppKeyword(const std::string& token) {
    static const std::vector<std::string> keywords = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while", "bool", "catch",
        "class", "const_cast", "delete", "dynamic_cast", "explicit",
        "false", "friend", "inline", "mutable", "namespace", "new",
        "operator", "private", "protected", "public", "reinterpret_cast",
        "static_cast", "template", "this", "throw", "true", "try",
        "typeid", "typename", "using", "virtual", "wchar_t"
    };

    return std::find(keywords.begin(), keywords.end(), token) != keywords.end();
}

bool isValidIdentifier(const std::string& token) {
    static const std::regex identifierRegex("[a-zA-Z_][a-zA-Z0-9_]*");
    return std::regex_match(token, identifierRegex);
}

bool isFunction(const std::string& code, const std::string& token) {
    std::string functionPattern = token + "\\s*\\(";
    std::regex functionRegex(functionPattern);

    return std::regex_search(code, functionRegex);
}

std::string extractFunctionParams(const std::string& code, const std::string& functionName) {
    std::string params;
    std::string functionPattern = functionName + "\\s*\\(([^)]*)\\)";
    std::regex functionRegex(functionPattern);

    std::smatch match;
    if (std::regex_search(code, match, functionRegex)) {
        if (match.size() > 1) {
            params = match.str(1);
        }
    }

    return params;
}

std::string extractVariableValue(const std::string& code, const std::string& variableName) {
    std::string value;
    std::string variablePattern = "\\b(?:int|float|double|char|bool)\\b\\s+" + variableName + "\\s*=\\s*(.*?)(;|$)";
    std::regex variableRegex(variablePattern);

    std::smatch match;
    if (std::regex_search(code, match, variableRegex)) {
        if (match.size() > 1) {
            value = match.str(1);
            // Remove leading and trailing whitespaces from the value.
            value = std::regex_replace(value, std::regex("^\\s+|\\s+$"), "");
        }
    }

    return value;
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

std::string compile_file(const char* filePath, std::string fileContents) {
    std::string final_code;

    if (endsWithCpp(filePath)) {
        std::istringstream iss(fileContents);
        std::string token;

        while (iss >> token) {
            if (isCppKeyword(token)) {
                // std::cout << token << " is a C++ keyword." << std::endl;
            } else if (isValidIdentifier(token)) {
                if (isFunction(fileContents, token)) {
                    // std::cout << token << " is a function name." << std::endl;
                    std::string params = extractFunctionParams(fileContents, token);
                    if (!params.empty()) {
                        // std::cout << "Function Parameters: " << params << std::endl;
                    }
                } else {
                    std::string value = extractVariableValue(fileContents, token);
                    if (!value.empty()) {
                        final_code += newvar(std::vector<Value>{{token, value}});
                    }
                }
            } else {
                // std::cout << token << " is not a valid identifier" << std::endl;
            }
        }
    }

    return final_code;
}
