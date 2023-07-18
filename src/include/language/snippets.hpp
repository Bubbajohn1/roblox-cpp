#include <string>
#include <iostream>
#include <vector> // For storing multiple Value objects
#include <sstream> // for std::ostringstream

struct Value {
    std::string name;
    std::string value;
};

struct Functions {}; // Replace 'struct functions' with 'struct Functions'

std::string newclass(const char* name, const std::vector<Value>& values, const Functions& functions) {
    std::ostringstream class_code;
    class_code << "local " << name << " = {};\n";
    class_code << "function " << name << ".new()\n";
    class_code << "    local Object = {";

    for (size_t i = 0; i < values.size(); ++i) {
        const Value& value = values[i];
        class_code << value.name << " = " << value.value;

        if (i < values.size() - 1) {
            class_code << ", ";
        }
    }

    class_code << "}\n";
    class_code << "    setmetatable(Object, " << name << ")\n";
    class_code << "    " << name << ".__index = " << name << "\n";
    class_code << "    return Object\n";
    class_code << "end";

    // Convert std::ostringstream to std::string and return it.
    return class_code.str();
}


std::vector<Value> values = {
    {"test", "10"},
    {"test2", "2"}
};

std::string testing = newclass("testing", values, {

});

void test_classcode() {
    printf("%s", testing.c_str());
}