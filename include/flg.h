#ifndef _FLG_H
#define _FLG_H

#include "syscall.h"

#define __BIT_CHK(flg) flg & 1  // check bit flag

#ifdef linux

/* bit  meaning
 * 
 * 
 * 
 * print:
 * 16   title
 * 
 * 9    inode
 * 8    permission
 * 7    links number
 * 6    file sizes
 * 5    blocks number
 * 4    user name
 * 3    group name
 * 2    date modify
 * 1    name
 */
typedef unsigned int flg_t;     // type of flag

#define B_IPNAM 0x100   // if print name
#define B_IPDAT 0x80    // if print date modify
#define B_IPGRP 0x40    // if print group name
#define B_IPUSR 0x20    // if print user name
#define B_IPBLK 0x10    // if print blocks number
#define B_IPSIZ 0x8     // if print group name
#define B_IPLNK 0x4     // if print links number
#define B_IPPMS 0x2     // if print permission
#define B_IPIND 0x1     // if print inode

#define B_PALL 0x1ff    // print all items

#define B_IPTTL 0x1 << 15   // if print title

#endif

struct print_item {
    unsigned char pos_num;  // effective number of position array
    unsigned char pos[ALL_EX_NUM];  // position of items to print
};
typedef struct print_item pitm_t;

#endif