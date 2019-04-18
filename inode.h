//
// Created by sunruslan on 3/30/19.
//

#ifndef FILESYSTEM_INODE_H
#define FILESYSTEM_INODE_H

#include <sys/types.h>
#include <bits/types/FILE.h>

struct INode{
    uint size;
    uint blocks[10];
    uint single_indirect_block;
    uint double_indirect_block;
    uint triple_indirect_block;
};

void setGap(uint);

struct INode* getINode(uint, FILE*);

void setINode(uint, struct INode*, FILE*);

void freeINode(uint);

void newNode();

void addData(struct INode*, void* data);

#endif //FILESYSTEM_INODE_H
