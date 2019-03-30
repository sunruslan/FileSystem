#include <stdio.h>
#include <stdlib.h>

#include "file_system.h"
#include "command.h"

#define STORAGE_SIZE 1048576
#define CONTENT_SIZE 1024
#define MAX_FILE_COUNT 255
#define MAX_NAME_LENGTH 255


int main(int argc, char** argv) {

    char* filename = "file_system_storage";
    int size = STORAGE_SIZE;

    initializeFileSystem(filename, size);
    char* command = malloc(MAX_NAME_LENGTH * sizeof(char));
    char* content = malloc(CONTENT_SIZE * sizeof(char));
    char** lsResult = malloc(MAX_FILE_COUNT * sizeof(char));;
    enum Command  cmd;
    /*
    do {
        scanf("%s", command);
        cmd = convertStringToCommand(command);
        switch (cmd){
            case MKDIR:
                scanf("%s", command);
                if(!mkdir(command)){
                    printf("%s\n", "cannot create directory");
                }
                break;
            case MKFILE:
                scanf("%s", command);
                if(!mkfile(command)){
                    printf("%s\n", "cannot create file");
                }
                break;
            case RMDIR:
                scanf("%s", command);
                if(!rmdir(command)){
                    printf("%s\n", "cannot remove directory");
                }
                break;
            case RMFILE:
                scanf("%s", command);
                if(!rmfile(command)){
                    printf("%s\n", "cannot remove file");
                }
                break;
            case READ:
                scanf("%s", command);
                if(!read(command, content)){
                    printf("%s\n", "cannot read file");
                } else {
                    printf("%s\n", content);
                }
                break;
            case WRITE:
                scanf("%s", command);
                if(!write(command, content)){
                    printf("%s\n", "cannot write to file");
                }
                break;
            case LS:
                scanf("%s", command);
                if(!ls(command, lsResult)){
                    printf("%s\n", "cannot do ls command");
                } else {
                    for (int i=0; i< MAX_FILE_COUNT && lsResult[i][0] != '\0'; ++i) {
                        printf("%s\n", lsResult[i]);
                    }
                }
                break;
            case UNKNOWN:
                printf("%s %s\n", "unknown command", argv[1]);
                break;
            default:
                break;
        }
    } while (cmd != EXIT);
*/
    clearFileSystem();

    return EXIT_SUCCESS;
}