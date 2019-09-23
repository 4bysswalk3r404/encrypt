#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "lists.h"

bool inVec(char c, std::vector<char> vec)
{
    for (const auto it: vec) {
        if (c == it)
            return true;
    }
    return false;
}

int main(int argc, char** argv)
{
    std::ifstream fd(argv[1], std::ios::binary);

    char* buffer;
    int keylen = 1;

    fd.seekg(0, std::ios::end);
    int size = fd.tellg();
    fd.seekg(0, std::ios::beg);

    buffer = new char[size];
    fd.read(buffer, size);

    int subX[256] = {0};
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 256; j++) {
            if (inVec(buffer[i] ^ j, acceptable))
                subX[j] += 1;
        }
    }
    int top10[10][2] = {{0}};
    for (int i = 0; i < 10; i++) {
        int top[2] = {0};
        for (int j = 0; j < 256; j++) {
            if (subX[j] > top[1]) {
                top[1] = subX[j];
                top[0] = j;
            }
        }
        top10[i][0] = top[0];
        top10[i][1] = top[1];
        subX[top[0]] = 0;
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%c", ((top10[i][0] >> j) & 1) + '0');
        }
        std::cout << ':' << top10[i][0] << '\t' << ((float)top10[i][1] / (float)size) * 100 << std::endl;
    }

    return 1;
}
