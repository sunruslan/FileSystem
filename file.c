//
// Created by sunruslan on 4/20/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <libgen.h>

#include "file.h"
#include "super_block.h"


bool file_exist_by_inode(FILE* file_system, INode inode, const char* name){
    File file = malloc(sizeof(struct FileStruct));
    for (int i = 0; i < 10; ++i) {
        fseek(file_system, inode->blocks[i], SEEK_SET);
        for (int j = 0; j < BLOCK_SIZE / FILE_SIZE; ++j) {
            fread(file, FILE_SIZE, 1, file_system);
            if (!strcmp(name, file->name)) return true;
        }
    }
    return false;
}

bool file_exist_by_path(FILE* file_system, const char* path) {
    char name[MAX_FILE_NAME_LENGTH];
    strcpy(name, basename(path));
    int path_len = strlen(path);
    char* dir_path = malloc(sizeof(char) * path_len);
    strncpy(dir_path, path, path_len - strlen(name) -1);
    return file_exist_by_inode(file_system, get_inode(file_system, dir_path), name);
}
