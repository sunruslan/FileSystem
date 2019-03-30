//
// Created by sunruslan on 3/25/19.
//

#ifndef FILESYSTEM_FILE_SYSTEM_H
#define FILESYSTEM_FILE_SYSTEM_H

#include <string.h>
#include <stdbool.h>


void initializeFileSystem(const char* filename, uint size);

void clearFileSystem();

int ls(const char* path, char** result);

int mkdir(const char* path);

int mkfile(const char* path);

int rmdir(const char* path);

int rmfile(const char* path);

int read(const char* path, char* content);

int write(const char* path, char* content);


#endif //FILESYSTEM_FILE_SYSTEM_H
