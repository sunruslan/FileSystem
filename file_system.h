//
// Created by sunruslan on 3/25/19.
//

#ifndef FILESYSTEM_FILE_SYSTEM_H
#define FILESYSTEM_FILE_SYSTEM_H

#include <string.h>
#include <stdbool.h>

#include "inode.h"


void create_file_system(char* path, int size);

void connect_file_system(char* path);

bool create_directory(char* path);

bool create_file(char* path);

bool remove_directory(char* path);

bool remove_file(char* path);

bool read(char* path, char* content);

bool write(char* path, const char* content);

bool ls(char* path, char** result);

bool dispose();


#endif //FILESYSTEM_FILE_SYSTEM_H
