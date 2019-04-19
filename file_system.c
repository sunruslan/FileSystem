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
#include "file.h"


SuperBlock superBlock;
FILE *file_system;

void create_file_system(char* path, int size){
    assert(size > 10 * BLOCK_SIZE);
    file_system = fopen(path, "w+b");
    superBlock = malloc(sizeof(struct SuperBlockStruct));
    superBlock->blocks_count = MIN(size / BLOCK_SIZE, MAX_BLOCKS_COUNT);
    superBlock->block_size = BLOCK_SIZE;
    superBlock->inodes_count = MIN(size/BLOCK_SIZE, MAX_INODES_COUNT);
    superBlock->inode_size = INODE_SIZE;
    superBlock->free_blocks_count = superBlock->blocks_count - 3;
    superBlock->free_inodes_count = superBlock->inodes_count - 1;
    superBlock->free_blocks = malloc(sizeof(int) * superBlock->blocks_count);
    int file_system_blocks = 1 + superBlock->inodes_count * INODE_SIZE / BLOCK_SIZE + 1;
    superBlock->file_system_blocks = file_system_blocks;
    for (int i = 0; i < superBlock->blocks_count; ++i) {
        superBlock->free_blocks[i] = i < file_system_blocks + 1 ? -1 : i;
    }
    superBlock->free_inodes = malloc(sizeof(int) * superBlock->inodes_count);
    for (int j = 0; j < superBlock->inodes_count; ++j) {
        superBlock->free_inodes[j] = j  < 1 ? -1 : j;
    }
    fwrite((const void*)&superBlock->blocks_count, sizeof(int), 1, file_system);
    fwrite((const void*)&superBlock->block_size, sizeof(int), 1, file_system);
    fwrite((const void*)&superBlock->inodes_count, sizeof(int), 1, file_system);
    fwrite((const void*)&superBlock->inode_size, sizeof(int), 1, file_system);
    fwrite((const void*)&superBlock->file_system_blocks, sizeof(int), 1, file_system);
    fwrite((const void*)&superBlock->free_blocks_count, sizeof(int), 1, file_system);
    fwrite((const void*)&superBlock->free_inodes_count, sizeof(int), 1, file_system);
    fwrite(superBlock->free_blocks, sizeof(int), superBlock->blocks_count, file_system);
    fwrite(superBlock->free_inodes, sizeof(int), superBlock->inodes_count, file_system);
    fseek(file_system, BLOCK_SIZE, SEEK_SET);
    File root = malloc(sizeof(struct FileStruct));
    root->inode_index = 1;
    strcpy(root->name, ".");
    INode root_inode = malloc(sizeof(struct INodeStruct));
    for (int i = 0; i < 10; ++i) {
        root_inode->blocks[i] = -1;
    }
    root_inode->blocks[0] = 3;
    root_inode->single_indirect_block = -1;
    root_inode->double_indirect_block = -1;
    root_inode->triple_indirect_block = -1;
    root_inode->files_inside = 0;
    root_inode->size = sizeof(struct INodeStruct);
    fwrite((const void*)&root_inode->size, sizeof(int), 1, file_system);
    fwrite((const void*)&root_inode->files_inside, sizeof(int), 1, file_system);
    fwrite((const void*)&root_inode->single_indirect_block, sizeof(int), 1, file_system);
    fwrite((const void*)&root_inode->double_indirect_block, sizeof(int), 1, file_system);
    fwrite((const void*)&root_inode->triple_indirect_block, sizeof(int), 1, file_system);
    fwrite((const void*)&root_inode->blocks, sizeof(int), 10, file_system);
    fseek(file_system, BLOCK_SIZE * file_system_blocks, SEEK_SET);
    fwrite((const void*)&root->inode_index, sizeof(int), 1, file_system);
    fwrite(root->name, sizeof(char), MAX_FILE_NAME_LENGTH, file_system);
    dispose();
}

void connect_file_system(char* path) {
    file_system = fopen(path, "r+b");
    superBlock = malloc(sizeof(struct SuperBlockStruct));
    fread(&superBlock->blocks_count, sizeof(int), 1, file_system);
    fread(&superBlock->block_size, sizeof(int), 1, file_system);
    fread(&superBlock->inodes_count, sizeof(int), 1, file_system);
    fread(&superBlock->inode_size, sizeof(int), 1, file_system);
    fread(&superBlock->file_system_blocks, sizeof(int), 1, file_system);
    fread(&superBlock->free_blocks_count, sizeof(int), 1, file_system);
    fread(&superBlock->free_inodes_count, sizeof(int), 1, file_system);
    superBlock->free_blocks = malloc(sizeof(int) * superBlock->blocks_count);
    superBlock->free_inodes = malloc(sizeof(int) * superBlock->inodes_count);
    fread(superBlock->free_blocks, sizeof(int), superBlock->blocks_count, file_system);
    fread(superBlock->free_inodes, sizeof(int), superBlock->inodes_count, file_system);
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
    free(superBlock->free_inodes);
    free(superBlock->free_blocks);
    free(superBlock);
    fclose(file_system);
}