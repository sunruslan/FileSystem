//
// Created by sunruslan on 3/25/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "file_system.h"
#include "structures.h"

#define MAGIC_NUMBER 0xEF53
#define BLOCK_SIZE 1024
#define MIN_BLOCKS_COUNT 2
#define I_NODES_COUNT 1024


struct FileSystem* fileSystem;

struct INode* initializeRootINode();
void initializeSuperBlock(uint);


void initializeFileSystem(const char* filename, uint size){
    assert(size > BLOCK_SIZE * MIN_BLOCKS_COUNT + I_NODES_COUNT*sizeof(struct INode));

    fileSystem = malloc(sizeof(struct FileSystem));
    fileSystem->file = fopen(filename, "w+b");
    fseek(fileSystem->file, 0, SEEK_SET);

    initializeSuperBlock(size);

    fileSystem->nextFreeBlock = 0;
    fileSystem->nextFreeINode = 0;
    fwrite(&fileSystem->superBlock, sizeof(struct SuperBlock), 1, fileSystem->file);
    size_t zerosSize = BLOCK_SIZE - sizeof(struct SuperBlock);
    void* zeros = malloc(zerosSize);
    memset(zeros, 0, zerosSize);
    fwrite(zeros, zerosSize, 1, fileSystem->file);

    struct INode * rootINode = initializeRootINode();
    fwrite(rootINode, sizeof(rootINode), 1, fileSystem->file);
    zerosSize = BLOCK_SIZE - sizeof(rootINode);
    fwrite(zeros, zerosSize, 1, fileSystem->file);

    zeros = realloc(zeros, BLOCK_SIZE);
    memset(zeros, 0, BLOCK_SIZE);

    fwrite(zeros, sizeof(struct INode), fileSystem->superBlock.freeINodesCount, fileSystem->file);
    fwrite(zeros, BLOCK_SIZE, fileSystem->superBlock.freeBlocksCount, fileSystem->file);

    free(zeros);
    fflush(fileSystem->file);
}


void initializeSuperBlock(uint size){
    fileSystem->superBlock.blocksCount = (size- sizeof(struct INode)*I_NODES_COUNT) / BLOCK_SIZE;
    fileSystem->superBlock.freeBlocksCount = fileSystem->superBlock.blocksCount - 1;
    fileSystem->superBlock.blockSize = BLOCK_SIZE;

    fileSystem->superBlock.iNodesCount = I_NODES_COUNT;
    fileSystem->superBlock.freeINodesCount = I_NODES_COUNT - 1;
    fileSystem->superBlock.iNodeSize = sizeof(struct INode);

    fileSystem->superBlock.magicNumber = MAGIC_NUMBER;
}

struct INode* initializeRootINode(){
    struct INode* rootINode = malloc(sizeof(struct INode));
    rootINode->mode = Directory;
    rootINode->nLinks = 1;
    rootINode->size = 2;
    memset(rootINode->blocks, 1, sizeof(uint)*10);
    rootINode->blocks[0] = 2;
    return rootINode;
}

void clearFileSystem(){
    fclose(fileSystem->file);
    free(fileSystem);
}