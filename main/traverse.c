#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

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

int main(int argc, char** argv)
{
    DIR *d;
    struct dirent *dir;
    char path[100];
    strcpy(path, argv[1]);
    d = opendir(path);
    char full_path[100];

    char files[100][100];
    char folders[100][100];

    int filesc = 0;
    int foldersc = 0;
    char c;

    printf("%s\n", path);
    printf("are you sure you want to encrypt this directory? [Y/N] ");
    scanf("%c", &c);
    if (!(c == 'Y' || c == 'y'))
    {
        printf("aborted\n");
        exit(-1);
    }

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(dir->d_type == DT_REG) {
                full_path[0] = '\0';
                strcat(full_path, path);
                strcat(full_path, "/");
                strcat(full_path, dir->d_name);
                strcpy(files[filesc], full_path);
                filesc++;
            } else if ((dir->d_type == DT_DIR) && (!(sameStr(dir->d_name, "..", 2) || sameStr(dir->d_name, "..", 1)))) {
                full_path[0] = '\0';
                strcat(full_path, path);
                strcat(full_path, "/");
                strcat(full_path, dir->d_name);
                strcpy(folders[foldersc], full_path);
                foldersc++;
            }
        }
        closedir(d);
    } else {
        printf("could not open directory\n");
    }

    for (int i = 0; i < filesc; i++)
    {
        FILE* infile;

        fseek(infile, 0L, SEEK_END);
        unsigned int bufferSize = ftell(infile);
        rewind(infile);

        unsigned char* buffer = (unsigned char*)malloc(sizeof(unsigned char) * bufferSize);
        void* BufferStart = buffer;

        while (!(feof(infile)))
        {
            *buffer = getc(infile);
            buffer++;
        }
        buffer = BufferStart;

        encrypt(buffer, atoi)

        FILE* outfile;
        printf("file: %s\n", files[i]);
    }
    for (int i = 0; i < foldersc; i++)
    {
        printf("folder: %s\n", folders[i]);
    }
    return(0);
}
