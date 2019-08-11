#include <stdio.h>
#include <string.h>

void PrintBin(char byte)
{
    for (int i = 8; i >= 0; i++) {
        printf("%i", (byte >> i) & 1);
    }
}

int main(int argc, char** argv)
{
    char* password = argv[2];
    int strsize = strlen(argv[1]);
    char* buffer = argv[1];

    for (int i = 0; i < strsize; i++) {
        printf("%i ", buffer[i]);
    }
    printf("\n");

    printf("encrypting:\n");
    for (int i = 0; i < strsize; i++)
    {
        printf("%i\t:\t", buffer[i]);
        buffer[i] ^= *(password + (i % strlen(password)));
        printf("%i\n", buffer[i]);
    }

    for (int i = 0; i < strsize; i++) {
        printf("%i ", buffer[i]);
    }
    printf("\n");

    printf("\ndecrypting:\n");
    for (int i = 0; i < strsize; i++)
    {
        printf("%i\t:\t", buffer[i]);
        buffer[i] ^= *(password + (i % strlen(password)));
        printf("%i\n", buffer[i]);
    }

    for (int i = 0; i < strsize; i++) {
        printf("%i ", buffer[i]);
    }
    printf("\n");
}
