//
// Created by sunruslan on 3/30/19.
//

#ifndef FILESYSTEM_INODE_H
#define FILESYSTEM_INODE_H

#include <sys/types.h>
#include <bits/types/FILE.h>

#define INODE_SIZE 56

struct INodeStruct{
    int size;
    int blocks[10];
    int single_indirect_block;
    int double_indirect_block;
    int triple_indirect_block;
} INodeStruct;

typedef struct INodeStruct* INode;

void setGap(int);

struct INode* getINode(int, FILE*);

void setINode(int, struct INode*, FILE*);

void freeINode(int);

void newNode();

void addData(struct INode*, void* data);

#endif //FILESYSTEM_INODE_H
