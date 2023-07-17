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

namespace fs = ghc::filesystem;

const char* default_config = R"(
{
	"name": "roblox-cpp-game",
	"globIgnorePaths": [
		"**/package.json",
		"**/tsconfig.json"
	],
	"tree": {
		"$className": "DataModel",
		"ServerScriptService": {
			"$className": "ServerScriptService",
			"cpp": {
				"$path": "out/server"
			}
		},
		"ReplicatedStorage": {
			"$className": "ReplicatedStorage",
			"cpp_include": {
				"$path": "runtimes/"
			},
			"cpp": {
				"$path": "out/shared"
			}
		},
		"StarterPlayer": {
			"$className": "StarterPlayer",
			"StarterPlayerScripts": {
				"$className": "StarterPlayerScripts",
				"cpp": {
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

)";

const char* lua_runtime = R"(

)";

void create_file(const char* path, const char* content) {
	std::ofstream file(path);
    // Write to the file
    file << content;
    // Close the file
    file.close();
}

void CommandHandler::init() {
    // creates the rojo project file and fodlers that are needed.

	create_file("default.project.json", default_config);

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

	create_file("./runtimes/runtime.server.lua", lua_runtime);
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



void CommandHandler::build() {
    // convert all the c/cpp files to luau

    // make a for loop to loop through all the files and figure out where they should go
    for (const auto& entry : fs::recursive_directory_iterator("./")) {
        if (fs::is_directory(entry)) {
            // If it's a directory, you can perform some action or simply skip it.
            // For this example, I'll print the directory path.
			std::string outputPath = convertPath(entry.path());
            ghc::filesystem::create_directories(outputPath);
        } else if (fs::is_regular_file(entry)) {
            // Process regular files here (e.g., print the file path)
            
        }
        // You can also check for other file types using is_symlink(), is_socket(), etc.
    }

	for (const auto& entry : fs::recursive_directory_iterator("./src/")) {
        if (fs::is_directory(entry)) {
            // If it's a directory, you can perform some action or simply skip it.
            // For this example, I'll print the directory path.
            std::cout << "[+] Folder: " << entry.path() << std::endl;
        } else if (fs::is_regular_file(entry)) {
            // Process regular files here (e.g., print the file path)
            std::cout << "[+] File: " << entry.path() << std::endl;
        }
        // You can also check for other file types using is_symlink(), is_socket(), etc.
    }
}

void CommandHandler::watch() {
    // if a files contents change then update the converted luau file
}