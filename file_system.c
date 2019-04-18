//
// Created by sunruslan on 3/25/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "file_system.h"

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


//    fileSystem
    fileSystem->nextFreeBlock = 2 + 16;
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

struct INode* getINodeByFileName(const struct INode* iNode, const char* name){
    struct File* file = malloc(sizeof(struct File));
    for(int block = 0; block < 10; ++block){
        for (int i = 0; i < BLOCK_SIZE / sizeof(struct File); ++i){
            fseek(fileSystem->file, BLOCK_SIZE * (17 + iNode->blocks[i]), SEEK_SET);
            fread(file, sizeof(struct File), 1, fileSystem->file);
            if (!strcpy(file->name, name)) {
                return file->iNode;
            }
            fflush(fileSystem->file);
        }
    }
    return NULL;
}

struct INode* getRootINode(FILE* file){
    fseek(file, BLOCK_SIZE, SEEK_SET);
    struct INode* root = malloc(sizeof(struct INode));
    fwrite(root, sizeof(struct INode), 1, file);
    fflush(file);
    return root;

}

int mkdir(const char* path){
    assert(path[0] == '/');
    struct INode* currentINode = getRootINode(fileSystem->file);
    struct INode* previousINode;
    char sep[10] = "/";
    char *currentFileName;
    char *previousName;
    currentFileName = strtok(path, sep);
    while(currentFileName != NULL) {
        previousINode = currentINode;
        currentINode = getINodeByFileName(previousINode, currentFileName);
        previousName = currentFileName;
        currentFileName = strtok(NULL, sep);
    }
    if (currentINode == NULL && previousINode != NULL) {
        struct File* file = malloc(sizeof(File));
        struct INode* newINode = malloc(sizeof(struct INode));
        newINode->mode = Directory;
        newINode->nLinks = 1;
        newINode->size = 0;
        file->iNode = newINode;
        strcpy(file->name, previousName);
        addData(previousINode, file);
    } else {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int mkfile(const char* path){
    assert(path[0] == '/');
    struct INode* currentINode = getRootINode(fileSystem->file);
    struct INode* previousINode;
    char sep[10] = "/";
    char *currentFileName;
    char *previousName;
    currentFileName = strtok(path, sep);
    while(currentFileName != NULL) {
        previousINode = currentINode;
        currentINode = getINodeByFileName(previousINode, currentFileName);
        previousName = currentFileName;
        currentFileName = strtok(NULL, sep);
    }
    if (currentINode == NULL && previousINode != NULL) {
        struct File* file = malloc(sizeof(File));
        struct INode* newINode = malloc(sizeof(struct INode));
        newINode->mode = File;
        newINode->nLinks = 1;
        newINode->size = 0;
        file->iNode = newINode;
        strcpy(file->name, previousName);
        addData(previousINode, file);
    } else {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


void clearFileSystem(){
    fclose(fileSystem->file);
    free(fileSystem);
}