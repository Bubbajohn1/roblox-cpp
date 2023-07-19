#include <string>
#include <iostream>
#include <vector> // For storing multiple Value objects
#include <sstream> // for std::ostringstream

struct Value {
    std::string name;
    std::string value;
};

struct Function {
    std::string name;
    std::string cb;
};

std::string generate_function(const std::string& class_name, const Function& func) {
    std::ostringstream function_code;
    function_code << "function " << class_name << ":" << func.name << "()\n";
    function_code << "    " << func.cb << "\n";
    function_code << "end\n\n";
    return function_code.str();
}

std::string newclass(const char* name, const std::vector<Value>& values, const std::vector<Function>& functions) {
    std::ostringstream class_code;
    class_code << "local " << name << " = {}\n\n";

    for (const auto& value : values) {
        class_code << name << "." << value.name << " = " << value.value << "\n";
    }

    for (const auto& func : functions) {
        class_code << generate_function(name, func);
    }

    // Convert std::ostringstream to std::string and return it.
    return class_code.str();
}


std::vector<Value> values = {
    {"test", "10"},
    {"test2", "2"}
};

std::vector<Function> functions = {
    {"setTest", "self.test = 10"},
    {"getTest", "return self.test"},
};

std::string testing = newclass("testing", values, functions); // place this inside the parser or compiler so when you make a cpp class it converts into a custom lua class.

void test_classcode() {
    printf("%s", testing.c_str());
}