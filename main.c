#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>


#define MAX_COMMAND_LENGTH 10
#define MAX_PATH_LENGTH 100


void connect_file_system(char* path) {

}

bool file_exist(char* path) {
    struct stat buffer;
    int exist = stat(path,&buffer);
    if(exist == 0)
        return true;
    else
        return false;
}

void create_file_system(char* path, int size){

}


int main(int argc, char** argv) {
    if (argc != 2 && argc != 3) {
        printf("usage for existent file system:\n\t./file_system path\n");
        printf("usage for nonexistent file system:\n\t./file_system path size\n");
        return EXIT_SUCCESS;
    }
    bool exist_mode = argc == 2;

    char* path = argv[1];
    int size = atoi(argv[2]);

    if (file_exist(path) && !exist_mode || !file_exist(path) && exist_mode) {
        return EXIT_FAILURE;
    }
    if (!exist_mode){
        create_file_system(path, size);
    }
    connect_file_system(path);

    char* command = malloc(MAX_COMMAND_LENGTH * sizeof(char));
    char* command_path = malloc(MAX_PATH_LENGTH * sizeof(char));

    while(true) {
        scanf("%s", command);
        if (!strcmp(command, "mkdir")) {
            scanf("%s", command_path);
            if(!mkdir(command_path)) printf("cannot create directory\n");
        } else if (!strcmp(command, "mkfile")) {
            scanf("%s", command_path);
            if(!mkdir(command_path)) printf("cannot create file\n");
        } else if (!strcmp(command, "rmdir")) {
            scanf("%s", command_path);
            if(!mkdir(command_path)) printf("cannot remove directory\n");
        } else if (!strcmp(command, "rmfile")) {
            scanf("%s", command_path);
            if(!mkdir(command_path)) printf("cannot remove file\n");
        } else if (!strcmp(command, "read")) {
            scanf("%s", command_path);
            if(!mkdir(command_path)) printf("cannot read from file\n");
        } else if (!strcmp(command, "write")) {
            scanf("%s", command_path);
            if(!mkdir(command_path)) printf("cannot write to file\n");
        } else if (!strcmp(command, "ls")) {
            scanf("%s", command_path);
            if(!mkdir(command_path)) printf("no such file or directory\n");
        } else if (!strcmp(command, "exit")) {
            printf("Exit.....\n");
            break;
        }
    }
    return EXIT_SUCCESS;
}