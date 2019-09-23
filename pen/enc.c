#include <stdio.h>
#include <stdlib.h>

void encryption(char* filename, int xorKey)
{
    FILE* infile = fopen(filename, "rb");

    fseek(infile, 0L, SEEK_END);
    unsigned int bufferSize = ftell(infile);
    rewind(infile);

    unsigned char* buffer = (unsigned char*)malloc(sizeof(unsigned char) * bufferSize);
    void* bufferStart = buffer;

    for (int i = 0; !(feof(infile)); i++)
    {
        *buffer = getc(infile) ^ xorKey;
        buffer++;
    }
    fclose(infile);

    *buffer = '\0';
    buffer = bufferStart;

    FILE* outfile = fopen(filename, "wb");
    fwrite(buffer, bufferSize, 1, outfile);
    fclose(outfile);
}

int main(int argc, char** argv)
{
    encryption(argv[1], atoi(argv[2]));
}
