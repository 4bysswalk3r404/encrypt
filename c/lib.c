#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

unsigned int strSize(char *ptr)
{
    int offset = 0;
    int count = 0;

    while (*(ptr + offset) != '\0')
    {
        count++;
        offset++;
    }
    return count;
}

unsigned char* encrypt(unsigned char* data, unsigned int bufferSize, unsigned int seed)
{
    srand(seed);

    for (int i = 0; i < bufferSize; i++)
    {
        *data = (*data + rand() % 256) % 256;
        data++;
    }
    for (int i = 0; i < bufferSize; i++)
        data--;
    return data;
}

unsigned char* decrypt(unsigned char* data, unsigned int bufferSize, unsigned int seed)
{
    srand(seed);

    for (int i = 0; i < bufferSize; i++)
    {
        *data = (*data - rand() % 256) % 256;
        data++;
    }
    for (int i = 0; i < bufferSize; i++)
        data--;
    return data;
}

unsigned int intLen(unsigned int num)
{
    int c = 0;
    while (num >= 1)
    {
        num /= 10;
        c++;
    }
    return c;
}

unsigned int lastNum(int num)
{
    int baseLen = intLen(num);
    int subtract  = pow(10, baseLen - 1);
    int cy = 0;
    while (baseLen == intLen(num))
    {
        num -= subtract;
        cy++;
        if (cy >= 10)
            return 0;
    }
    return cy;
}

char* toStr(int num)
{
    int numLen = intLen(num);
    int mult = ceil(pow(10, numLen - 1));
    char* string = (char*)malloc(sizeof(char) * numLen);
    int last;
    for (int i = 0; i < numLen; i++)
    {
        last = lastNum(num);
        *string = last + '0';
        string++;
        num -= mult * last;
        mult /= 10;
    }
    *string = '\0';
    for (int i = 0; i < numLen; i++)
        string--;
    return string;
}

char* concatenate(char* base, char* sub)
{
    unsigned int baseSize = strSize(base);
    unsigned int subSize  = strSize(sub);

    char* output = (char*)malloc(sizeof(char) * (baseSize + subSize));

    for (int i = 0; i < baseSize; i++)
    {
        *output = *base;
        output++;
        base++;
    }
    for (int i = 0; i < subSize; i++)
    {
        *output = *sub;
        output++;
        sub++;
    }
    *output = '\0';
    for (int i = 0; i < baseSize + subSize; i++)
        output--;
    return output;
}
