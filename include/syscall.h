/*
 * This file is for cross-platform system call
 * Support Platform :
 * Linux
 */

#ifndef _SYSCALL_H
#define _SYSCALL_H

// linux system call
#ifdef linux

#include <unistd.h>
#include <getopt.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>

#include <sys/stat.h>
#include <sys/types.h>

#define IS_SUPPORT 1
#define ALL_EX_NUM 9    // number of all extend items

typedef DIR ALL_PLAT_DIR;       // linux directory struct
typedef struct dirent ALL_PLAT_DIRENT;   // linux direcotry entry struct

#endif


// Mac OS system call
#ifdef TARGET_OS_MAC

#define ALL_PLAT_DIR
#define IS_SUPPORT 0

#endif


// Windows OS system call
#ifdef __WINDOWS_

#define ALL_PLAT_DIR
#define IS_SUPPORT 0

#endif


// Unknow OS
#ifndef IS_SUPPORT
#define IS_SUPPORT 0
#endif


// If platform is not support
#if !IS_SUPPORT
#error "Your platform is not support for exa software."
#endif


/*---------------    All Paltform Unified Interface Call     -----------------*/

ALL_PLAT_DIR *open_dir_forall(char []);
ALL_PLAT_DIRENT *read_dir_forall(ALL_PLAT_DIR*);
int close_dir_forall(ALL_PLAT_DIR*);


#endif