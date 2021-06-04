#ifndef FEXDET_H
#define FEXDET_H

#include <sys/types.h>
#include <dirent.h>

/*
 * File extend detail 
 */
struct fexdet {
    ino_t inode;    // file inode
    char permis[11];    // file permission
    nlink_t links;      // number of file hard links
    char size[6];       // file sizes
    unsigned long blocks;   // file blocks
    char user[256];     // file owner
    char group[256];    // group of file owner
    char date_modify[20];   // modifid date
    char *name;     // file name
    int isDir;      // 
};

int setfex(struct dirent*, struct fexdet*);

#endif