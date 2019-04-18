//
// Created by sunruslan on 4/18/19.
//

#include <stdbool.h>
#include <sys/stat.h>

bool file_exist(char* path) {
    struct stat buffer;
    int exist = stat(path, &buffer);
    if(exist == 0)
        return true;
    else
        return false;
}