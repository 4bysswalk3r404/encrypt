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

int getDirStructure(char* path, char** files, char** folders)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    char full_path[100];

    int filesc = 0;
    int foldersc = 0;

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(dir->d_type == DT_REG) {
                full_path[0] = '\0';
                strcat(full_path, path);
                strcat(full_path, "/");
                strcat(full_path, dir->d_name);
                strcpy(*files, full_path);
                printf("file: %s\n", *files);
                files++;
            } else if ((dir->d_type == DT_DIR) && (!(sameStr(dir->d_name, "..", 2) || sameStr(dir->d_name, "..", 1)))) {
                full_path[0] = '\0';
                strcat(full_path, path);
                strcat(full_path, "/");
                strcat(full_path, dir->d_name);
                strcpy(*folders, full_path);
                printf("folders: %s\n", *folders);
                folders++;
            }
        }
        closedir(d);
    } else {
        free(d);
        free(dir);
        free(path);
        return 0;
    }
    free(d);
    free(dir);
    free(path);
    return 1;
}

int main(int argc, char** argv)
{
    char **files = (char**)malloc(sizeof(char*) * 100);
    char **folders = (char**)malloc(sizeof(char*) * 100);

    getDirStructure(argv[1], files, folders);
    while (*files != "\0")
    {
        printf("file: %s\n", *files);
        files++;
    }
    while (*folders != "\0")
    {
        printf("file: %s\n", *folders);
        folders++;
    }
    return 1;
}
