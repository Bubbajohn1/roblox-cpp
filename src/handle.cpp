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
#include "include/language/compile.hpp"

namespace fs = ghc::filesystem;

template <typename T, typename T2>
void create_file(T path, T2 content) {
	std::ofstream file(path);
    // Write to the file
    file << content;
    // Close the file
    file.close();
}

void test_create_file(const char* path, const char* content) {
	std::ofstream file(path);
    // Write to the file
    file << content;
    // Close the file
    file.close();
}

template <typename T>
std::string readfile(T path) {
    std::string content;
    std::ifstream file(path);

    if (!file) {
        std::cerr << "Error opening file: " << path << std::endl;
        return "";
    }

    // Use a stringstream to efficiently append each line to the content string
    std::stringstream buffer;
    buffer << file.rdbuf();
    content = buffer.str();

    file.close();

    return content;
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


void CommandHandler::init() {
    // creates the rojo project file and folders that are needed.

	test_create_file("default.project.json", R"(
    {
        "name": "roblox-rblx++-game",
        "globIgnorePaths": [
            "**/package.json",
            "**/tsconfig.json"
        ],
        "tree": {
            "$className": "DataModel",
            "ServerScriptService": {
                "$className": "ServerScriptService",
                "rblx++": {
                    "$path": "out/server"
                }
            },
            "ReplicatedStorage": {
                "$className": "ReplicatedStorage",
                "rblx++_include": {
                    "$path": "runtimes/"
                },
                "rblx++": {
                    "$path": "out/shared"
                }
            },
            "StarterPlayer": {
                "$className": "StarterPlayer",
                "StarterPlayerScripts": {
                    "$className": "StarterPlayerScripts",
                    "rblx++": {
                        "$path": "out/client"
                    }
                }
            },
            "Workspace": {
                "$className": "Workspace",
                "$properties": {
                    "FilteringEnabled": true
                }
            },
            "HttpService": {
                "$className": "HttpService",
                "$properties": {
                    "HttpEnabled": true
                }
            },
            "SoundService": {
                "$className": "SoundService",
                "$properties": {
                    "RespectFilteringEnabled": true
                }
            }
        }
    }

    )");

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

	create_file<const char*, const char*>("./runtimes/runtime.lua", lua_runtime);

	std::cout << "[*] project initalized succesfully" << std::endl;
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
            create_file<std::string, std::string>(convertPath(entry.path()), readfile<std::string>(formatPath(entry.path())));
            compile_file(formatPath(entry.path()).c_str(), readfile<std::string>(formatPath(entry.path()))); // replace ^ with this line
        }
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

void CommandHandler::test() {
    for (const auto& entry : fs::recursive_directory_iterator("./")) {
        if (fs::is_regular_file(entry)) {
            // Process regular files here
            compile_file(formatPath(entry.path()).c_str(), readfile<std::string>(formatPath(entry.path()))); // replace ^ with this line
        }
    }
}