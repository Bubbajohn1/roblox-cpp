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

void CommandHandler::init() {
    // creates the rojo project file and fodlers that are needed.

    // create and enter the rojo project file
    std::ofstream config("default.project.json");
    // Write to the file
    config << default_config;
    // Close the file
    config.close();

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

    std::ofstream runtime("./out/runtimes/runtime.server.lua");
    // Write to the file
    runtime << lua_runtime;
    // Close the file
    runtime.close();
}

void CommandHandler::build() {
    // convert all the c/cpp files to luau

    // make a for loop to loop through all the files and figure out where they should go
}

void CommandHandler::watch() {
    // if a files contents change then update the converted luau file
}