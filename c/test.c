#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib.h"

int main(int argc, char** argv)
{
    char* infilename = argv[1];

    if (access(infilename, F_OK) == -1) {
        printf("%s does not exist or could not be found.\n", infilename);
        return -1;
    }

    FILE* infile = fopen(infilename, "rb");

    unsigned int bufferSize = 0;
    unsigned char* buffer;

    do {
        *buffer = getc(infile);
        buffer++;
        bufferSize++;
    } while (!(feof(infile)));
    fclose(infile);
    for (int i = 0; i < bufferSize; i++)
        buffer--;

    encrypt(buffer, bufferSize, atoi(argv[2]));

    decrypt(buffer, bufferSize, atoi(argv[2]));

    char* outfilename = "./decrypted.txt";
    for (int i = 1; access(outfilename, F_OK) != -1; i++)
    {
        outfilename = concatenate("./decrypted", toStr(i));
        outfilename = concatenate(outfilename, ".txt");
    }

    FILE* outfile = fopen(outfilename, "wb");
    fwrite(buffer, bufferSize, 1, outfile);
    fclose(outfile);

    return 1;
}
