//
// Created by sunruslan on 3/30/19.
//

#ifndef FILESYSTEM_BLOCK_H
#define FILESYSTEM_BLOCK_H

#include <sys/types.h>

struct SuperBlock{
    uint blocksCount;
    uint freeBlocksCount;
    uint blockSize;
    uint iNodesCount;
    uint freeINodesCount;
    uint iNodeSize;
    uint magicNumber;
};


#endif //FILESYSTEM_BLOCK_H
