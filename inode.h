//
// Created by sunruslan on 3/30/19.
//

#ifndef FILESYSTEM_INODE_H
#define FILESYSTEM_INODE_H

#include <sys/types.h>
#include <bits/types/FILE.h>

#define INODE_SIZE 52


struct INodeStruct{
    int size;
    int files_inside;
    int blocks[10];
    int index;
} INodeStruct;

typedef struct INodeStruct* INode;

INode get_inode(FILE* file_system, const char* path);

void write_to_inode_block(FILE* file_system, INode inode, const void* content, int size);

INode get_inode_by_index(FILE* file_system, int index);

void write_inode(FILE* file_system, INode inode);

#endif //FILESYSTEM_INODE_H
