//
// Created by sunruslan on 3/30/19.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#include "inode.h"
#include "super_block.h"
#include "file.h"


INode get_inode(FILE* file_system, const char* path) {
    INode inode = malloc(sizeof(struct INodeStruct));
    if (!strcmp(path, "")) {
        fseek(file_system, BLOCK_SIZE, SEEK_SET);
        fread(inode, INODE_SIZE, 1, file_system);
        return inode;
    }
    char name[MAX_FILE_NAME_LENGTH];
    strcpy(name, basename(path));
    int path_len = strlen(path);
    char* dir_path = malloc(sizeof(char) * path_len);
    strncpy(dir_path, path, path_len - strlen(name) -1);
    INode dir_inode = get_inode(file_system, dir_path);
    File file = malloc(sizeof(struct FileStruct));
    for (int i = 0; i < 10; ++i) {
        fseek(file_system, dir_inode->blocks[i] * BLOCK_SIZE, SEEK_SET);
        for (int j = 0; j < BLOCK_SIZE / FILE_SIZE; ++j) {
            fread(file, FILE_SIZE, 1, file_system);
            if (!strcmp(name, file->name)) return get_inode_by_index(file_system, file->inode_index);
        }
    }
    return NULL;
}

INode get_inode_by_index(FILE* file_system, int index) {
    INode inode = malloc(sizeof(struct INodeStruct));
    fseek(file_system, BLOCK_SIZE + index * INODE_SIZE, SEEK_SET);
    fread(inode, INODE_SIZE, 1, file_system);
    return inode;
}


void write_to_inode_block(FILE* file_system, INode inode, const void* content, int size) {
    assert(size > 0 && inode->size + size < 10 * BLOCK_SIZE);
    inode->size -= size;
    int block = -1;
    for (int j = 0; j < 10; ++j) {
        block = j;
        if (inode->size < (j + 1) * BLOCK_SIZE) break;
    }
    assert(inode->blocks[block] != -1);
    int free_capacity = (block + 1) * BLOCK_SIZE - inode->size;
    if (free_capacity > size) {
        fseek(file_system, inode->blocks[block] * BLOCK_SIZE + inode->size - block * BLOCK_SIZE, SEEK_SET);
        fwrite(content, size, 1, file_system);
    } else {
        assert(block + 1 < 10 && inode->blocks[block+1] != -1);
        fseek(file_system, (inode->blocks[block] + 1) * BLOCK_SIZE - free_capacity, SEEK_SET);
        fwrite(content, free_capacity, 1, file_system);
        fseek(file_system, inode->blocks[block + 1] * BLOCK_SIZE, SEEK_SET);
        fwrite(content + free_capacity, size - free_capacity, 1, file_system);
    }
}

void write_inode(FILE* file_system, INode inode) {
    fseek(file_system, BLOCK_SIZE + inode->index * INODE_SIZE, SEEK_SET);
    fwrite(inode, INODE_SIZE, 1, file_system);
}
