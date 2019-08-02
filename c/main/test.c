#include "../lib/strlib.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char* buffer = (char*)malloc(sizeof(char) * 100);
    SetStr(buffer, argv[1]);
    printf("%s\n", buffer);
    ConcatStr(buffer, "_hello");
    printf("%s\n", buffer);
}
