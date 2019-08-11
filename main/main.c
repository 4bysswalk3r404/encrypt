#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

unsigned int seed;
char* key;
int keylen;

int SameStr(char* s1, char* s2, int num)
{
    for (int i = 0; i < num; i++) {
        if (*s1 != *s2)
            return 0;
        s1++; s2++;
    }
    return 1;
}

void encryption(char* filename, int S_ARG, int X_ARG)
{
    FILE* infile = fopen(filename, "rb");

    fseek(infile, 0L, SEEK_END);
    unsigned int bufferSize = ftell(infile);
    rewind(infile);

    unsigned char* buffer = (unsigned char*)malloc(sizeof(unsigned char) * bufferSize);
    void* bufferStart = buffer;

    if (S_ARG) {
        srand(seed);
        while (!(feof(infile)))
        {
            *buffer = (getc(infile) DEF_X rand() % 256) % 256;
            buffer++;
        }
    } else if (X_ARG) {
        for (int i = 0; !(feof(infile)); i++)
        {
            *buffer = getc(infile) ^ key[i % keylen];
            buffer++;
        }
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
                encryption(full_path, 1, 0);
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
        printf("-s seed of file encryption.\n");
        printf("-x supply password for xor encryption/decryption.\n");
        //printf("[-o] specify output file name.\n");
        //printf("[-c] print output to console and suppress file writing.\n");
        printf("[-r] recursively encrypts all accessable files in directory specified.\n");
        printf("[-B] number of bytes for every normal byte (limited to 10).\n");
        exit(EXIT_SUCCESS);
    }
    char* infilename = argv[1];
    if (access(infilename, F_OK) == -1) {
        printf("%s does not exist or could not be found.\n", infilename);
        exit(EXIT_FAILURE);
    }


    int R_ARG = 0;
    int X_ARG;
    int S_ARG;
    for (int i = 0; i < argc; i++) {
        if (SameStr(argv[i], "-s", 2)) {
            S_ARG = 1;
            seed = atoi(argv[i + 1]);
        } else if (SameStr(argv[i], "-x", 2)) {
            X_ARG = 1;
            key = argv[i + 1];
            keylen = strlen(key);
        } else if (SameStr(argv[i], "-r", 2)) {
            R_ARG = 1;
        }
    }
    if (S_ARG && X_ARG) {
        if (1 DEF_X 1) {
            encryption(infilename, 1, 0);
            encryption(infilename, 0, 1);
        } else {
            encryption(infilename, 0, 1);
            encryption(infilename, 1, 0);
        }
        exit(EXIT_SUCCESS);
    } else if (S_ARG) {
        encryption(infilename, 1, 0);
        exit(EXIT_SUCCESS);
    } else if (X_ARG) {
        encryption(infilename, 0, 1);
        exit(EXIT_SUCCESS);
    } else {
        printf("you must supply a seed/password with -s. killing program.\n");
        exit(EXIT_FAILURE);
    }
    if (R_ARG) {
        recursiveWalkEncrypt(infilename);
        exit(EXIT_SUCCESS);
    }
    return 0;
}
