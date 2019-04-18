//
// Created by sunruslan on 3/30/19.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inode.h"

#define MAX_I_NODES_COUNT 256
#define BLOCK_SIZE 1024


uint gap = 0;

void setGap(const uint _gap) {
    gap = _gap;
}

struct INode* getINode(const uint id, FILE* file){
    assert(id < MAX_I_NODES_COUNT);
    struct INode* iNode;
    fseek(file, BLOCK_SIZE + id * sizeof(struct INode), SEEK_SET);
    fread(&iNode, sizeof(struct INode), 1, file);
    fflush(file);
    return iNode;
}

void resetINode(const uint id, FILE* file){
    assert(id < MAX_I_NODES_COUNT);
    fseek(file, BLOCK_SIZE + id* sizeof(struct INode), SEEK_SET);
    void* zeros = malloc(sizeof(struct INode));
    memset(zeros, 0, sizeof(struct INode));
    fwrite(zeros, sizeof(struct INode), 1, file);
    free(zeros);
    fflush(file);
}

void addData(){

}

