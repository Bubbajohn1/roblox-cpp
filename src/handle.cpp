#include <iostream>
#include <fstream>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm> // For std::transform
#include <sstream>   // For std::stringstream
#include "include/filesystem.hpp"
#include "include/handle.hpp"
#include "include/files.hpp"

namespace fs = ghc::filesystem;


template <typename T>
T create_file(T path, T content) {
	std::ofstream file(path);
    // Write to the file
    file << content;
    // Close the file
    file.close();
}

template <typename T>
T readfile(T path) {
	std::string content;
    std::ifstream file(path);

    while (getline (file, content)) {
        // Output the text from the file
    }

    file.close();

    return content;
}


void CommandHandler::init() {
    // creates the rojo project file and folders that are needed.

	create_file<const char*>("default.project.json", default_config);

    // create the basic dirs. these cant be changed or removed.
	mkdir("runtimes");

    mkdir("out");
    mkdir("out/client");
    mkdir("out/server");
    mkdir("out/shared");

    mkdir("src");
    mkdir("src/client");
    mkdir("src/server");
    mkdir("src/shared");

    // CREATE RUNTIME FILES

	create_file<const char*>("./runtimes/runtime.server.lua", lua_runtime);

	std::cout << "[*] project initalized succesfully" << std::endl;
}

std::string convertPath(const ghc::filesystem::path& input) {
    std::string output = input.string();

    // Convert all directory separators to forward slashes
    std::replace(output.begin(), output.end(), '\\', '/');

    // Replace ".\\src\\" with "./out/"
    size_t startPos = output.find("./src/");
    if (startPos != std::string::npos) {
        output.replace(startPos, 6, "./out/");
    }

    return output;
}

std::string formatPath(const ghc::filesystem::path& input) {
    std::string output = input.string();

    // Convert all directory separators to forward slashes
    std::replace(output.begin(), output.end(), '\\', '/');

    // Replace ".\\src\\" with "./out/"
    size_t startPos = output.find("./src/");
    if (startPos != std::string::npos) {
        output.replace(startPos, 6, "./src/");
    }

    return output;
}



void CommandHandler::build() {
    // convert all the c/cpp files to luau

    // make a for loop to loop through all the files and figure out where they should go
    for (const auto& entry : fs::recursive_directory_iterator("./")) {
        if (fs::is_directory(entry)) {
            // If it's a directory, create a folder inside out that corrispponds to it
			std::string outputPath = convertPath(entry.path());
            ghc::filesystem::create_directories(outputPath);
        } else if (fs::is_regular_file(entry)) {
            // Process regular files here
            create_file<std::string>(convertPath(entry.path()), readfile<std::string>(formatPath(entry.path())));
        }
        // You can also check for other file types using is_symlink(), is_socket(), etc.
    }

	for (const auto& entry : fs::recursive_directory_iterator("./src/")) {
        if (fs::is_directory(entry)) {
            // If it's a directory, you can perform some action or simply skip it.
            // For this example, I'll print the directory path.
            std::cout << "[+] Folder: " << convertPath(entry.path()) << std::endl;
        } else if (fs::is_regular_file(entry)) {
            // Process regular files here (e.g., print the file path)
            std::cout << "[+] File: " << convertPath(entry.path()) << std::endl;
        }
        // You can also check for other file types using is_symlink(), is_socket(), etc.
    }
}

void CommandHandler::watch() {
    // if a files contents change then update the converted luau file
}