//
// Created by sunruslan on 3/25/19.
//

#ifndef FILESYSTEM_COMMAND_H
#define FILESYSTEM_COMMAND_H

#include <string.h>

enum Command {
    UNKNOWN,
    MKDIR,
    MKFILE,
    RMDIR,
    RMFILE,
    READ,
    WRITE,
    LS,
    EXIT
};

enum Command  convertStringToCommand(char* cmd) {
    if (!strcmp(cmd, "mkdir")) return MKDIR;
    if (!strcmp(cmd, "mkfile")) return MKFILE;
    if (!strcmp(cmd, "rmdir")) return RMDIR;
    if (!strcmp(cmd, "rmfile")) return RMFILE;
    if (!strcmp(cmd, "read")) return READ;
    if (!strcmp(cmd, "write")) return WRITE;
    if (!strcmp(cmd, "ls")) return LS;
    if (!strcmp(cmd, "exit")) return EXIT;
    return UNKNOWN;
}

#endif //FILESYSTEM_COMMAND_H
