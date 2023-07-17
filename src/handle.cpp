#include <iostream>
#include <fstream>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
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

    // create the basic dirs. these can be changed or removed.
    mkdir("out");
    mkdir("out/runtimes");
    mkdir("src");

    std::string runtimeText;
    std::ifstream runtimefile_lua1("../lua_runtimes/runtime.lua");

    // CREATE RUNTIME FILES

    std::ofstream runtime("./out/runtimes/runtime.lua");
    // Write to the file
    while (getline (runtimefile_lua1, runtimeText)) {
    // Output the text from the file
        runtime << runtimeText;
    }
    // Close the file
    runtime.close();
}

void CommandHandler::build() {
    // convert all the c/cpp files to luau
}

void CommandHandler::watch() {
    // if a files contents change then update the converted luau file
}