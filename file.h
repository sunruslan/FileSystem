//
// Created by sunruslan on 4/18/19.
//

#ifndef FILESYSTEM_FILE_H
#define FILESYSTEM_FILE_H

#include "file_system.h"

#define MAX_FILE_NAME_LENGTH 255
#define FILE_SIZE 260


struct FileStruct{
    int inode_index;
    char name[MAX_FILE_NAME_LENGTH];
} FileStruct;

typedef struct FileStruct* File;

bool file_exist_by_inode(FILE* file_system, INode inode, const char* name);

bool file_exist_by_path(FILE* file_system, const char* path);

#endif //FILESYSTEM_FILE_H
