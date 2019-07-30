#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <vector>

int main(int argc, char** argv)
{
    std::ifstream infile(argv[1], std::ios::binary);
    char c;
    while (infile.get(c))
    {
        std::cout << (int)c << ' ';
    }
    infile.close();
    std::cout << std::endl;
}
