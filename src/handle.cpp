#include <iostream>
#include <fstream>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
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
				"$path": "out/runtimes"
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
    mkdir("out");
    mkdir("out/runtimes");
    mkdir("out/client");
    mkdir("out/server");
    mkdir("out/shared");

    mkdir("src");
    mkdir("src/client");
    mkdir("src/server");
    mkdir("src/shared");

    // CREATE RUNTIME FILES

	create_file("./out/runtimes/runtime.server.lua", lua_runtime);
}

std::string replaceSubstring(const std::string& original, const std::string& oldSubstr, const std::string& newSubstr) {
    std::string result = original;
    size_t pos = result.find(oldSubstr);
    if (pos != std::string::npos) {
        result.replace(pos, oldSubstr.length(), newSubstr);
    }
    return result;
}


void traverseDirectory(const fs::path& srcPath, const fs::path& outPath) {
    for (const auto& entry : fs::directory_iterator(srcPath)) {
        const fs::path& entryPath = entry.path();
        const fs::path relativePath = fs::relative(entryPath, srcPath);

        if (fs::is_directory(entry)) {
            // Recursively create the directory in the output path
            fs::create_directory(outPath / relativePath);

            // Continue traversing the subdirectory
            traverseDirectory(entryPath, outPath);
        } else if (fs::is_regular_file(entry)) {
            // Copy the file to the output path
            fs::copy(entryPath, outPath / relativePath);
        }
        // You can also check for other file types using is_symlink(), is_socket(), etc.
    }
}

void CommandHandler::build() {
    // convert all the c/cpp files to luau

    // make a for loop to loop through all the files and figure out where they should go
	traverseDirectory("./src/", "./out/");
}

void CommandHandler::watch() {
    // if a files contents change then update the converted luau file
}