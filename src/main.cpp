#include <stdio.h>
#include <string.h>

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
            printf("WATCH");
        }

        if(cmpStrings(argv, "-b", "-build") == 0) {
            printf("BUILD");
        }
        
        if(cmpStrings(argv, "--init", "--initalize") == 0) {
            printf("INIT");
        }
    } else {
        printf("Usage: rblxcpp.exe \n --init / --initalize \n -w / -watch \n -b / -build");
    }
    return 0;
}
