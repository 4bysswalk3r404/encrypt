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

    FILE* infile = fopen(infilename, "rb");

    fseek(infile, 0L, SEEK_END);
    unsigned int bufferSize = ftell(infile);
    rewind(infile);

    unsigned char* buffer = (unsigned char*)malloc(sizeof(unsigned char) * bufferSize);

    while (!(feof(infile)))
    {
        *buffer = getc(infile);
        buffer++;
    }

    fclose(infile);
    for (int i = 0; i < bufferSize + 1; i++)
        buffer--;

    decrypt(buffer, bufferSize, atoi(argv[2]));

    char* outfilename = (char*)malloc(sizeof(char) * 100);
    SetStr(outfilename, infilename);
    ConcatStr(outfilename, ".dec");
    for (int i = 1; access(outfilename, F_OK) != -1; i++)
    {
        SetStr(outfilename, infilename);
        ConcatStr(outfilename, ToStr(i));
        ConcatStr(outfilename, ".dec");
    }

    FILE* outfile = fopen(outfilename, "wb");
    fwrite(buffer, bufferSize, 1, outfile);
    fclose(outfile);
    free(outfilename);

    return 1;
}
