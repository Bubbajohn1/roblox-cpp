#include "include/utils.hpp"

bool endsWithCpp(const char* str) {
    if (str == nullptr)
        return false;

    size_t len = strlen(str);
    if (len < 4)
        return false;

    const char* suffix = str + (len - 4);
    return (strcmp(suffix, ".cpp") == 0);
}