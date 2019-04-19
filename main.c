#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>

#include "file_system.h"
#include "inode.h"

#define MAX_COMMAND_LENGTH 10
#define MAX_PATH_LENGTH 100
#define MAX_CONTENT_LENGTH 1024


bool file_exist(char* path) {
    struct stat buffer;
    int exist = stat(path, &buffer);
    if(exist == 0)
        return true;
    else
        return false;
}

int main(int argc, char** argv) {
    INode inode;
    printf("%d", sizeof(inode->blocks));
    /*
    if (argc != 2 && argc != 3) {
        printf("usage for existent file system:\n\t./file_system path\n");
        printf("usage for nonexistent file system:\n\t./file_system path size\n");
        return EXIT_SUCCESS;
    }
    bool exist_mode = argc == 2;

    char* path = argv[1];
    uint size = atoi(argv[2]);

    if (file_exist(path) && !exist_mode || !file_exist(path) && exist_mode) {
        return EXIT_FAILURE;
    }
    if (!exist_mode){
        create_file_system(path, size);
    }
    connect_file_system(path);

    char* command = malloc(MAX_COMMAND_LENGTH * sizeof(char));
    char* command_path = malloc(MAX_PATH_LENGTH * sizeof(char));
    char* content = malloc(MAX_CONTENT_LENGTH * sizeof(char));
    char** ls_results;

    while(true) {
        scanf("%s", command);
        if (!strcmp(command, "mkdir")) {
            scanf("%s", command_path);
            if(!create_directory(command_path)) printf("cannot create directory\n");
        } else if (!strcmp(command, "mkfile")) {
            scanf("%s", command_path);
            if(!create_file(command_path)) printf("cannot create file\n");
        } else if (!strcmp(command, "rmdir")) {
            scanf("%s", command_path);
            if(!remove_directory(command_path)) printf("cannot remove directory\n");
        } else if (!strcmp(command, "rmfile")) {
            scanf("%s", command_path);
            if(!remove_file(command_path)) printf("cannot remove file\n");
        } else if (!strcmp(command, "read")) {
            scanf("%s", command_path);
            if(!read(command_path, content)){
                printf("cannot read from file\n");
                continue;
            }
            printf(content);
        } else if (!strcmp(command, "write")) {
            scanf("%s", command_path);
            scanf("%s", content);
            if(!write(command_path, content)) printf("cannot write to file\n");
        } else if (!strcmp(command, "ls")) {
            scanf("%s", command_path);
            if(!ls(command_path, ls_results)) printf("no such file or directory\n");
        } else if (!strcmp(command, "exit")) {
            dispose();
            printf("Exit.....\n");
            break;
        }
    }

    free(path);
    free(command);
    free(command_path);
    free(content);
    for (int i = 0; i < sizeof(ls_results)/ sizeof(char*); ++i) {
        if (ls_results[i] != NULL) free(ls_results[i]);
    }
    if (ls_results != NULL) free(ls_results);
     */
    return EXIT_SUCCESS;
}