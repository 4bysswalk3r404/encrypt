#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lib/strlib.h"

int main(int argc, char** argv)
{
    char* infilename = argv[1];
    int O_ARG = 0;
    for (int i = 0; i < argc; i++) {
        if (SameStr(argv[i], "-o", 2)) {
            O_ARG = 1;
            char* outfilename = (char*)argv[i + 1];
            printf("-o found, %s is outfilename\n", outfilename);
        }
    }
    if (!(O_ARG)) {
        char* outfilename = (char*)argv[1];
        printf("-o not found %s is outfilename\n", outfilename);
    }
    return 1;
}
