//
// Created by sunruslan on 4/18/19.
//

#ifndef FILESYSTEM_FILE_H
#define FILESYSTEM_FILE_H

#include "file_system.h"

struct File{
    int inode_index;
    char* name[MAX_FILE_NAME_LENGTH];
};

#endif //FILESYSTEM_FILE_H
