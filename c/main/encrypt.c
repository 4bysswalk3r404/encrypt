#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../lib/strlib.h"

int main(int argc, char** argv)
{
    char* infilename = argv[1];
    if (access(infilename, F_OK) == -1) {
        printf("%s does not exist or could not be found.\n", infilename);
        return -1;
    }

    int O_ARG = 0;
    int S_ARG = 0;
    for (int i = 0; i < argc; i++) {
        if (SameStr(argv[i], "-o", 2)) {
            O_ARG = 1;
            char* outfilename = (char*)argv[i + 1];
        } else if (SameStr(argv[i], "-s", 2)) {
            S_ARG = 1;
            int seed = atoi(argv[i] + 1);
        }
    }
    if (!(O_ARG)) {
        char* outfilename = (char*)argv[1];
    }
    if (!(S_ARG)) {
        printf("you must supply a seed/password with -p. killing program.\n");
        exit(EXIT_FAILURE);
    }

    FILE* infile = fopen(infilename, "rb");

    fseek(infile, 0L, SEEK_END);
    unsigned int bufferSize = ftell(infile);
    rewind(infile);

    unsigned char* buffer = (unsigned char*)malloc(sizeof(unsigned char) * bufferSize);
    void* bufferStart = buffer;

    while (!(feof(infile)))
    {
        *buffer = getc(infile);
        buffer++;
    }

    fclose(infile);
    buffer = bufferSize;

    encrypt(buffer, bufferSize, atoi(seed);

    FILE* outfile = fopen(outfilename, "wb");
    fwrite(buffer, bufferSize, 1, outfile);
    fclose(outfile);

    free(outfilename);

    return 1;
}
