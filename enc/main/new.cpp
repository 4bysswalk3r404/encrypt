#include <iostream>
#include <fstream>
#include <random>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int SameStr(char* s1, const char* s2, int num)
{
    for (int i = 0; i < num; i++) {
        if (*s1 != *s2)
            return 0;
        s1++; s2++;
    }
    return 1;
}

int MyEncrypt(const char* filename, int seed)
{
    FILE* infile = fopen(filename, "rb");

    fseek(infile, 0L, SEEK_END);
    unsigned int bufferSize = ftell(infile);
    rewind(infile);

    unsigned char* buffer = (unsigned char*)malloc(sizeof(char) * bufferSize);
    unsigned char* bufferStart = buffer;

    std::mt19937 rng(seed);
    std::uniform_int_distribution<std::mt19937::result_type> random256(0, 256);

    while (!(feof(infile)))
    {
        *buffer = getc(infile) ^ random256(rng);
        buffer++;
    }
    fclose(infile);

    FILE* outfile = fopen(filename, "wb");
    fwrite(bufferStart, bufferSize, 1, outfile);
    fclose(outfile);

    return 1;
}

void recursiveWalkEncrypt(const char* base_path, int seed)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(base_path);
    std::string full_path;

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(dir->d_type == DT_REG) {
                full_path = base_path;
                full_path += '/';
                full_path += dir->d_name;
                MyEncrypt(full_path.c_str(), seed);
                printf("file: %s\n", full_path.c_str());
            } else if ((dir->d_type == DT_DIR) && (!(SameStr(dir->d_name, ".", 2) || SameStr(dir->d_name, "..", 1)))) {
                full_path = base_path;
                full_path += '/';
                full_path += dir->d_name;
                printf("dir: %s\n", full_path.c_str());
                recursiveWalkEncrypt(full_path.c_str(), seed);
            }
        }
        closedir(d);
    }
}

int main(int argc, char** argv)
{
    if (argc < 3) {
        std::cout << "must include file to encrypt and encryption seed\n";
        return -1;
    }
    int usefile = 0;
    int usedir  = 0;
    for (int i = 0; i < argc; i++) {
        if (SameStr(argv[i], "-f", 2)) {
            usefile = 1;
            break;
        }
        if (SameStr(argv[i], "-d", 2)) {
            usedir = 1;
            break;
        }
    }
    if (!usefile && !usedir) {
        std::cout << "must specify directory or folder with -d and -f respectively\n";
        return -1;
    }
    std::string filename = argv[1];
    if (usefile) {
        MyEncrypt(filename.c_str(), atoi(argv[2]));
        return 1;
    }
    if (usedir) {
        recursiveWalkEncrypt(filename.c_str(), atoi(argv[2]));
        return 1;
    }
    return 1;
}
