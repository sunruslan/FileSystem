//
// Created by sunruslan on 3/27/19.
//

#ifndef FILESYSTEM_STRUCTURES_H
#define FILESYSTEM_STRUCTURES_H

#include <sys/types.h>
#include <bits/types/FILE.h>

#define MAX_FILE_NAME

enum Mode{
    File,
    Directory,
    Empty
};

struct INode{
    enum Mode mode;
    uint nLinks;
    uint size;
    uint blocks[10];
    uint singleIndirectBlock;
    uint doubleIndirectBlock;
    uint tripleIndirectBlock;

};

struct SuperBlock{
    uint blocksCount;
    uint freeBlocksCount;
    uint blockSize;
    uint iNodesCount;
    uint freeINodesCount;
    uint iNodeSize;
    uint magicNumber;
};

struct FileSystem{
    FILE* file;
    struct SuperBlock superBlock;
    uint nextFreeBlock;
    uint nextFreeINode;
};

struct File{
    struct INode iNode;
    char* name[MAX_FILE_NAME];
};

#endif //FILESYSTEM_STRUCTURES_H
