//
// Created by sunruslan on 4/18/19.
//

#ifndef FILESYSTEM_SUPERBLOCK_H
#define FILESYSTEM_SUPERBLOCK_H

#define MAX_BLOCKS_COUNT 1024
#define MAX_INODES_COUNT 1024
#define BLOCK_SIZE 8220

struct SuperBlockStruct{
    int blocks_count;
    int inodes_count;
    int block_size;
    int inode_size;
    int file_system_blocks;
    int* free_blocks;
    int* free_inodes;
    int free_blocks_count;
    int free_inodes_count;
} SuperBlockStruct;

typedef struct SuperBlockStruct* SuperBlock;



#endif //FILESYSTEM_SUPERBLOCK_H
