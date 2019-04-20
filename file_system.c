//
// Created by sunruslan on 3/25/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/param.h>
#include <libgen.h>

#include "file_system.h"
#include "super_block.h"
#include "inode.h"
#include "file.h"

#define MAX_CONTENT_LENGTH 1024*1024


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
    root_inode->files_inside = 1;
    root_inode->size = FILE_SIZE;
    root_inode->index = 0;
    fwrite((const void*)&root_inode->size, sizeof(int), 1, file_system);
    fwrite((const void*)&root_inode->files_inside, sizeof(int), 1, file_system);
    fwrite((const void*)&root_inode->blocks, sizeof(int), 10, file_system);
    fwrite((const void*)&root_inode->index, sizeof(int), 1, file_system);
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

int get_free_block_index() {
    assert(superBlock != NULL && superBlock->free_blocks != NULL);
    for (int i = 0; i < superBlock->blocks_count; ++i) {
        if (superBlock->free_blocks[i] > 0) return i;
    }
    return -1;
}

int occupy_block(int index){
    assert(index >= 0 && index < superBlock->blocks_count);
    assert(superBlock->free_blocks[index] == index);
    superBlock->free_blocks[index] = -1;
    superBlock->free_blocks_count -= 1;
}

int get_free_inode_index() {
    assert(superBlock != NULL && superBlock->free_inodes != NULL);
    for (int i = 0; i < superBlock->inodes_count; ++i) {
        if (superBlock->free_inodes[i] > 0) return i;
    }
    return -1;
}

int occupy_inode(int index) {
    assert(index >= 0 && index < superBlock->inodes_count);
    assert(superBlock->free_inodes[index] == index);
    superBlock->free_inodes[index] = -1;
    superBlock->free_inodes_count -=1;
}


bool create_directory(char* path){
    char name[MAX_FILE_NAME_LENGTH];
    strcpy(name, basename(path));
    int path_len = strlen(path);
    char* dir_path = malloc(sizeof(char) * path_len);
    strncpy(dir_path, path, path_len - strlen(name) -1);
    INode dir_inode = get_inode(file_system, dir_path);
    if (dir_inode == NULL) return false;
    if (file_exist_by_inode(file_system, dir_inode, name)) return false;

    INode inode = malloc(sizeof(struct INodeStruct));
    inode->size = 2 * FILE_SIZE;
    if ((inode->blocks[0] = get_free_block_index()) == -1) return false;
    occupy_block(inode->blocks[0]);
    for (int i = 1; i < 10; ++i) {
        inode->blocks[i] = -1;
    }
    inode->files_inside = 2;
    write_inode(file_system, dir_inode);
    if ((inode->index = get_free_inode_index()) == -1) return false;
    occupy_inode(inode->index);

    File file = malloc(sizeof(struct FileStruct));

    strcpy(file->name, ".");
    file->inode_index = inode->index;
    fseek(file_system, inode->blocks[0] * BLOCK_SIZE, SEEK_SET);
    fwrite(file, FILE_SIZE, 1, file_system);
    strcpy(file->name, "..");
    file->inode_index = dir_inode->index;
    fwrite(file, FILE_SIZE, 1, file_system);

    dir_inode->files_inside += 1;
    dir_inode->size += FILE_SIZE;
    write_inode(file_system, dir_inode);
    strcpy(file->name, name);
    file->inode_index = inode->index;
    write_to_inode_block(file_system, dir_inode, file, FILE_SIZE);
    return true;
}

bool create_file(char* path){
//    char* name;
//    char* dir_path;
//    INode dir_inode = get_inode(dir_path);
//    if (dir_inode == NULL) return false;
//    if (file_exist_by_inode(dir_inode, name)) return false;
//
//    INode inode = malloc(sizeof(struct INodeStruct));
//    inode->size = sizeof(struct FileStruct);
//    inode->blocks[0] = get_free_block_index();
//    for (int i = 1; i < 10; ++i) {
//        inode->blocks[i] = -1;
//    }
//    inode->files_inside = 0;
//
//    dir_inode->files_inside += 1;
//    dir_inode->size += inode->size;
//    File file = malloc(sizeof(struct FileStruct));
//    strcpy(file->name, ".");
//    file->inode_index = inode->index;
//    write_to_inode_block(dir_inode, file);
//    return true;
}

bool remove_directory(char* path){

}

bool remove_file(char* path){

}

bool read(char* path, char* content){
//    char* name;
//    char* dir_path;
//    INode dir_inode = get_inode(dir_path);
//    if (dir_inode == NULL) return false;
//    if (!file_exist_by_inode(dir_inode, name)) return false;
//
//    INode inode = get_inode(path);
//    int cur = 0;
//    int i = 0;
//    while (cur < inode->size) {
//        if (inode->blocks[i] == -1) return false;
//        fseek(file_system, inode->blocks, SEEK_SET);
//        fread(content + cur, MIN(inode->size, BLOCK_SIZE), 1, file_system);
//        cur += MIN(inode->size, BLOCK_SIZE);
//    }
//    content[inode->size] = '\0';
//    return true;
}

bool write(char* path, const char* content){

}

int ls(char* path, char*** result){
    if (!strcmp(path, "/")) strcpy(path, "");
    INode inode = get_inode(file_system, path);
    if (inode == NULL || inode->files_inside == 0) return false;
    *result = malloc(sizeof(char*) * inode->files_inside);
    int block = 0;
    fseek(file_system, inode->blocks[block] * BLOCK_SIZE, SEEK_SET);
    File file = malloc(sizeof(struct FileStruct));
    int count = 0;
    for (int i = 0; i < inode->files_inside; ++i) {
        if ((i + 1) * FILE_SIZE > BLOCK_SIZE * (block + 1)) {
            ++block;
            fseek(file_system, inode->blocks[block] * BLOCK_SIZE, SEEK_SET);
            continue;
        }
        fread(file, FILE_SIZE, 1, file_system);
        (*result)[i] = malloc(MAX_FILE_NAME_LENGTH * sizeof(char));
        strcpy((*result)[i], file->name);
        ++count;
    }
    return count;
}

bool dispose(){
    free(superBlock->free_inodes);
    free(superBlock->free_blocks);
    free(superBlock);
    fclose(file_system);
}