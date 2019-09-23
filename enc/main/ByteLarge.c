#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void PrintByte2(int num)
{
    for (int i = 1; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            printf("%i", (num >> (i * 8) + j) & 1);
        }
        printf(" ");
    }
}

int main(int argc, char** argv)
{
    int strsize = strlen(argv[1]);
    char* password = argv[2];

    char* buffer = (char*)malloc(sizeof(char) * strsize * 2);

    for (int i = 0; i < strsize; i++) {

    }
    printf("\n");
    return 1;
}
