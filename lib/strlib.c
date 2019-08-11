#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int StrSize(char* buffer)
{
    int i;
    for (i = 0; *buffer != '\0'; i++)
        buffer++;
    return i;
}

void Input(char* buffer)
{
    char c;
    void* BufferStart = buffer;
    while(c = getchar())
    {
        if ((c == '\n') || (c == '\0')) {
            *buffer = '\0';
            break;
        } else {
            *buffer = c;
            buffer++;
        }
    }
    buffer = BufferStart;
}

void ConcatStr(char* buffer, char* sub)
{
    void* BufferStart = buffer;
    while (*buffer != '\0')
        buffer++;
    while (*sub != '\0')
    {
        *buffer = *sub;
        buffer++; sub++;
    }
    *buffer = '\0';
    buffer = BufferStart;
}

void SetStr(char* from, char* to)
{
    void* FromStart = from;
    int _strlen = StrSize(to);
    for (int i = 0; i < _strlen; i++)
    {
        *from = *to;
        from++;
        to++;
    }
    *from = '\0';
    from = FromStart;
}

int SameStr(char* base, char* sub, int num)
{
    int same = 0;
    for (int i = 0; i < num; i++)
    {
        if (*base == *sub)
            same++;
        base++;
        sub++;
    }
    if (same == num)
        return 1;
    return 0;
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

char* ToStr(int num)
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
