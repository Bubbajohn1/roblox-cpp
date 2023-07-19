#include <stdio.h>
#include <string.h>
#include "include/handle.hpp"
#include "include/language/snippets.hpp"


int cmpStrings(char* a[], const char* b, const char* c) {
    if(strcmp(a[1], b) == 0 || strcmp(a[1], c) == 0) {
        return 0;
    } else {
        return 1;
    }
}

int main(int argc, char* argv[]) {    
    if (argc >= 2) {
        if(cmpStrings(argv, "-w", "-watch") == 0) {
            CommandHandler::watch();
        }

        if(cmpStrings(argv, "-b", "-build") == 0) {
            CommandHandler::build();
        }
        
        if(cmpStrings(argv, "--init", "--initalize") == 0) {
            CommandHandler::init();
        }

        // test_classcode();
    } else {
        printf("Usage: rblxcpp.exe -command \n --init / --initalize \n -w / -watch \n -b / -build");
    }
    return 0;
}
