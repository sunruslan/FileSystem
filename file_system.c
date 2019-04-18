//
// Created by sunruslan on 3/25/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "file_system.h"
#include "super_block.h"

struct FileSystem{
    FILE* file;
    struct SuperBlock superBlock;
    uint* freeBlocks;
    uint* freeINodes;
    uint nextFreeBlock;
    uint nextFreeINode;
} file_system;


void create_file_system(char* path, int size){

}

void connect_file_system(char* path){
    file_system.file = fopen(path, "w+b");
}

bool create_directory(char* path){

}

bool create_file(char* path){

}

bool remove_directory(char* path){

}

bool remove_file(char* path){

}

bool read(char* path, char* content){

}

bool write(char* path, const char* content){

}

bool ls(char* path, char** result){

}

bool dispose(){
    fclose(file_system.file);
}