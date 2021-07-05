#ifndef _FEXDET_H
#define _FEXDET_H

#include "syscall.h"

/*
 * File extend detail 
 */
struct fexdet {

#ifdef linux
    ino_t inode;        // file inode
    nlink_t links;      // number of file hard links
    blkcnt_t blocks;    // file blocks
    siz_t size;
    char user[256];     // file owner
    char group[256];    // group of file owner
    char permis[11];    // file permission
    char date_modify[20];   // modifid date
#endif

    time_t sec_time;
    char str_size[6];       // file sizes
    char *name;         // file name
    int isDir;          // if it is a directory
};

int setfex(ALL_PLAT_DIRENT*, struct fexdet*);
int fname_cmp(void*, void*);
int fsize_cmp(void*, void*);
int ftime_cmp(void*, void*);
void fexfree(struct fexdet*);

#endif