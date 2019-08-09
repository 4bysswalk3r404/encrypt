#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../lib/strlib.h"

int main(int argc, char** argv)
{
    if (SameStr(argv[1], "help", 4)) {
        printf("-s seed of file encryption\n");
        printf("[-o] specify output file name\n");
        printf("[-c] print output to console and suppress file writing\n");
        //printf("[-n] suppress file writing\n");
        exit(1);
    }
    char* infilename = argv[1];
    if (access(infilename, F_OK) == -1) {
        printf("%s does not exist or could not be found.\n", infilename);
        return -1;
    }

    char* outfilename;
    int seed;

    int O_ARG = 0;
    int S_ARG = 0;
    int C_ARG = 0;
    for (int i = 0; i < argc; i++) {
        if (SameStr(argv[i], "-o", 2)) {
            O_ARG = 1;
            outfilename = (char*)argv[i + 1];
        } else if (SameStr(argv[i], "-s", 2)) {
            S_ARG = 1;
            seed = atoi(argv[i] + 1);
        } else if (SameStr(argv[i], "-c", 2)) {
            C_ARG = 1;
        }
    }
    if (!(O_ARG)) {
        outfilename = (char*)argv[1];
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

    *buffer = '\0';
    buffer = bufferStart;

    decrypt(buffer, bufferSize, seed);

    if (!(C_ARG)) {
        FILE* outfile = fopen(outfilename, "wb");
        fwrite(buffer, bufferSize, 1, outfile);
        fclose(outfile);
    } else {
        printf("%s\n", buffer);
    }
    free(outfilename);

    return 1;
}
