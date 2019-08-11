#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

unsigned int seed;

int SameStr(char* s1, char* s2, int num)
{
    for (int i = 0; i < num; i++) {
        if (*s1 != *s2)
            return 0;
        s1++; s2++;
    }
    return 1;
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

void recursiveWalkEncrypt(char* path)
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
            } else if ((dir->d_type == DT_DIR) && (!(SameStr(dir->d_name, "..", 2) || SameStr(dir->d_name, "..", 1)))) {
                full_path[0] = '\0';
                strcat(full_path, path);
                strcat(full_path, "/");
                strcat(full_path, dir->d_name);
                recursiveWalkEncrypt(full_path);
            }
        }
        closedir(d);
    }
}

int main(int argc, char** argv)
{
    if (SameStr(argv[1], "help", 4)) {
        printf("-s seed of file encryption\n");
        printf("[-o] specify output file name\n");
        printf("[-c] print output to console and suppress file writing\n");
        printf("[-r] recursively encrypts all accessable files in directory specified\n");
        exit(EXIT_SUCCESS);
    }
    char* infilename = argv[1];
    if (access(infilename, F_OK) == -1) {
        printf("%s does not exist or could not be found.\n", infilename);
        exit(EXIT_FAILURE);
    }

    char* outfilename;

    int O_ARG = 0;
    int S_ARG = 0;
    int C_ARG = 0;
    int R_ARG = 0;
    for (int i = 0; i < argc; i++) {
        if (SameStr(argv[i], "-o", 2)) {
            O_ARG = 1;
            outfilename = (char*)argv[i + 1];
        } else if (SameStr(argv[i], "-s", 2)) {
            S_ARG = 1;
            seed = atoi(argv[i + 1]);
        } else if (SameStr(argv[i], "-c", 2)) {
            C_ARG = 1;
        } else if (SameStr(argv[i], "-r", 2)) {
            R_ARG = 1;
        }
    }
    if (!(O_ARG)) {
        outfilename = (char*)argv[1];
    }
    if (!(S_ARG)) {
        printf("you must supply a seed/password with -s. killing program.\n");
        exit(EXIT_FAILURE);
    }
    if (R_ARG) {
        recursiveWalkEncrypt(infilename);
        return 1;
    }

    FILE* infile = fopen(infilename, "rb");

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

    if (!(C_ARG)) {
        FILE* outfile = fopen(outfilename, "wb");
        fwrite(buffer, bufferSize, 1, outfile);
        fclose(outfile);
    } else {
        printf("%s\n", buffer);
    }

    return 1;
}
