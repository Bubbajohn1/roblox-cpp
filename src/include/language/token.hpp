#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <vector>

std::vector<std::string> tokenize(const std::string& input) {
    // Regular expression pattern to match C++ tokens
    std::regex token_regex("[a-zA-Z_][a-zA-Z_0-9]*|\\S");

    // Token vector to store individual tokens
    std::vector<std::string> tokens;

    // Using std::sregex_iterator to iterate over matched tokens in the input string
    for (std::sregex_iterator it(input.begin(), input.end(), token_regex); it != std::sregex_iterator(); ++it) {
        tokens.push_back(it->str());
    }

    return tokens;
}