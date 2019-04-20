cmake_minimum_required(VERSION 3.13)
project(FileSystem C)

set(CMAKE_C_STANDARD 99)

add_executable(FileSystem main.c file_system.c file_system.h inode.c inode.h file.h super_block.h file.c)