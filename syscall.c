#include "include/syscall.h"

/*
 * For all platform open directory
 * Return pointer of directory
 */
ALL_PLAT_DIR *open_dir_forall(char path[])
{

// linux system call function
#ifdef linux
    return opendir(path);
#endif

}

/*
 * For all platform read directory
 * Return pointer of directory entry
 */
ALL_PLAT_DIRENT *read_dir_forall(ALL_PLAT_DIR* dir)
{

#ifdef linux
    return readdir(dir);
#endif
}

/*
 * For all platform close directory.
 * Return 0 if successful, -1 if not.
 */
int close_dir_forall(ALL_PLAT_DIR* dir)
{

// linux system call function
#ifdef linux
    return closedir(dir);
#endif

}
