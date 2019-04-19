//
// Created by sunruslan on 3/25/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/param.h>

#include "file_system.h"
#include "super_block.h"
#include "inode.h"


SuperBlock superBlock;
FILE *file_system;

void create_file_system(char* path, int size){
    assert(size > 10 * BLOCK_SIZE);
    file_system = fopen(path, "w+b");
    superBlock = malloc(sizeof(struct SuperBlockStruct));
    superBlock->blocks_count = MIN(size / BLOCK_SIZE, MAX_BLOCKS_COUNT);
    superBlock->block_size = BLOCK_SIZE;
    superBlock->inodes_count = MIN(size/BLOCK_SIZE, MAX_BLOCKS_COUNT);
    superBlock->inode_size = INODE_SIZE;
    superBlock->free_blocks_count = superBlock->blocks_count - 3;
    superBlock->free_inodes_count = superBlock->free_inodes_count - 1;
    superBlock->free_blocks = malloc(sizeof(int) * superBlock->blocks_count);
    int file_system_blocks = 1 + superBlock->inodes_count * INODE_SIZE / BLOCK_SIZE + 1;
    for (int i = 0; i < superBlock->blocks_count; ++i) {
        superBlock->free_blocks[i] = i + file_system_blocks >= superBlock->blocks_count ? -1 : i + file_system_blocks;
    }
    superBlock->free_inodes = malloc(sizeof(int) * superBlock->inodes_count);
    for (int j = 0; j < superBlock->inodes_count; ++j) {
        superBlock->free_inodes[j] = j + 1 >= superBlock->inodes_count ? -1 : j + 1;
    }
    fprintf(file_system, "%d",superBlock->blocks_count);
    fprintf(file_system, "%d",superBlock->block_size);
    fprintf(file_system, "%d",superBlock->inode_size);
    fprintf(file_system, "%d",superBlock->inodes_count);
    fprintf(file_system, "%d",superBlock->free_inodes_count);
    fprintf(file_system, "%d",superBlock->free_inodes_count);
    fwrite(superBlock->free_blocks, sizeof(int), superBlock->blocks_count, file_system);
    fwrite(superBlock->free_inodes, sizeof(int), superBlock->inodes_count, file_system);
    dispose();
}

void connect_file_system(char* path) {
    file_system = fopen(path, "r+b");
    superBlock = malloc(sizeof(struct SuperBlockStruct));
    fread()
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
    fclose(file_system);
}