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
    std::string params;
    std::string cb;
};

std::string newfunction(const std::vector<Function>& functions) {
    std::ostringstream final_code;

    for (const auto& func : functions) {
        final_code << "function " << func.name << "(" + func.params + ")\n";
        final_code << "    " << func.cb << "\n";
        final_code << "end\n\n";
    }

    return final_code.str();
}
std::string newvar(const std::vector<Value>& values) {
    std::ostringstream final_code;

    for (const auto& value : values) {
        final_code << "local " << value.name << " = " << value.value << "\n";
    }  
    
    return final_code.str();
}

// use the newvar and newfunction helpers to make more stuff
std::string newclass(const char* name, const std::vector<Value>& values, const std::vector<Function>& functions) {
    std::ostringstream final_code;

    final_code << newvar(std::vector<Value> {
        {std::string(name), "{}"}
    });

    for (const auto& value : values) {
        final_code << name << "." << value.name << " = " << value.value << "\n";
    }

    for (const auto& func : functions) {
        // final_code << generate_class_function(name, func);

        final_code << newfunction(std::vector<Function> {
            {std::string(name) + ":" + func.name, func.params, std::string(func.cb)}
        });
    }

    // Convert std::ostringstream to std::string and return it.
    return final_code.str();
}
std::string newenum(const char* name) {
    // call the runtime and make an enum
    std::ostringstream final_code;

    final_code << "local runtime = require(game:GetService('ReplicatedStorage'):FindFirstChild('rblx++_include').runtime)\n\n";
    final_code << std::string("runtime.MakeEnum(") + name + ")";

    return final_code.str();
}

std::string class_code = newclass("testing", std::vector<Value> {
    {"test", "10"},
    {"test2", "2"}
}, std::vector<Function> {
    {"setTest", "val", "self.test = val"},
    {"getTest", "", "return self.test"},
});
std::string function_code = newfunction(std::vector<Function> {
    {"test", "", "print('hello world')"},
});
std::string var_code = newvar(std::vector<Value> {
    {"testing1234", "'test'"}
});

std::string f_code = class_code + function_code + var_code; // repelace this later with some function to see what should go first.

void test_classcode() {
    printf("%s", f_code.c_str());
}