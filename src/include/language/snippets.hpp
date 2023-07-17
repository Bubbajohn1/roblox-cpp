#include <string>

const char* newclass(const char* name) {
    std::string class_code = std::string("local ") + name + " = {}" + R"(
        
    )";
    // Convert std::string to const char* (c_str) and return it.
    return class_code.c_str();
}