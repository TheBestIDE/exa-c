#ifndef _FEXDET_H
#define _FEXDET_H

#include "syscall.h"

/*
 * File extend detail 
 */
struct fexdet {

#ifdef linux
    ino_t inode;        // file inode
    char permis[11];    // file permission
    nlink_t links;      // number of file hard links
    unsigned long blocks;   // file blocks
    char user[256];     // file owner
    char group[256];    // group of file owner
    char date_modify[20];   // modifid date
#endif

    char size[6];       // file sizes
    char *name;         // file name
    int isDir;          // if it is a directory
};

int setfex(ALL_PLAT_DIRENT*, struct fexdet*);

#endif