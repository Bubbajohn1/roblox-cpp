#include <iostream>
#include <fstream>
#include "include/handle.hpp"

const char* default_config = R"(
{
    "options": {
        "outDir": "./out",
        "srcDir": "./src"
    }
}
)";

void CommandHandler::init() {
    // create a config file that holds all of the build options for rblxcpp

    // create and enter the config file
    std::ofstream config("rblxcpp.config.json");
    // Write to the file
    config << default_config;
    // Close the file
    config.close();
}

void CommandHandler::build() {
    // convert all the c/cpp files to luau
}

void CommandHandler::watch() {
    // if a files contents change then update the converted luau file
}