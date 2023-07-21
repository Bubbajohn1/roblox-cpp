#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "./token.hpp"
#include "./snippets.hpp"
#include "../utils.hpp"
#include "../filesystem.hpp"

namespace fs = ghc::filesystem;

std::string compile_file(const char* filePath, const std::string& fileContents) {
    std::string final_code;

    // ends with cpp is in the utils header.
    if (endsWithCpp(filePath)) {
        std::vector<std::string> tokens = tokenize(fileContents);

        for (const std::string& token : tokens) {
            if(token == ";") {
                std::cout << " ; found" << std::endl;
            }
            // Here, you can process the tokens as needed, e.g., concatenate them to form the final_code.
        }
    }

    return final_code;
}