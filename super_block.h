//
// Created by sunruslan on 4/18/19.
//

#ifndef FILESYSTEM_SUPERBLOCK_H
#define FILESYSTEM_SUPERBLOCK_H

struct SuperBlock{
    uint blocks_count;
    uint inode_count;
    uint block_size;
    uint inode_size;
    uint free_block;
    uint free_inode;
};

#endif //FILESYSTEM_SUPERBLOCK_H
