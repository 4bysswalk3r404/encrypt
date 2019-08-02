#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../lib/strlib.h"

int main()
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

    unsigned char* bufferTest = (unsigned char*)malloc(sizeof(unsigned char) * bufferSize);
    unsigned char* buffer = (unsigned char*)malloc(sizeof(unsigned char) * bufferSize);
    void* BufferStart = buffer;

    while (!(feof(infile)))
    {
        *buffer = getc(infile);
        bufferMain++;
    }

    fclose(infile);
    buffer = BufferStart;

    for (unsigned int i = 0; i <= UINT_MAX; i++)
    {
        SetStr(bufferTest, buffer);
        decrypt(bufferTest, i);
    }
}
