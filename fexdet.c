#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "include/fexdet.h"
#include "include/global.h"
#include "include/syscall.h"

extern const char path[1024];

// English abbreviation of month
const char *str_Mon[12] = { "Jan", "Feb", "Mat", "Apr",
                            "May", "Jun", "Jul", "Aug",
                            "Sep", "Oct", "Nov", "Dec"};

#ifdef linux

/*
 * Get string of file permissions
 */
int getf_permis(mode_t mode, char buf[])
{
    // init buffer
    for (int i = 0; i < 10; i++)
        buf[i] = '-';
    // first position is a flag to show if file is a directory
    buf[0] = S_ISDIR(mode) ? 'd' : '.';
    /* 3 bits for user  */
    if ( mode & S_IRUSR ) buf[1] = 'r';
    if ( mode & S_IWUSR ) buf[2] = 'w';
    if ( mode & S_IXUSR ) buf[3] = 'x';
    /* 3 bits for group */
    if ( mode & S_IRGRP ) buf[4] = 'r';
    if ( mode & S_IWGRP ) buf[5] = 'w';
    if ( mode & S_IXGRP ) buf[6] = 'x';
    /* 3 bits for other */
    if ( mode & S_IROTH ) buf[7] = 'r';
    if ( mode & S_IWOTH ) buf[8] = 'w';
    if ( mode & S_IXOTH ) buf[9] = 'x';
    // end of string: '\0'
    buf[10] = 0;
}

/*
 * convert uid to user name
 */
void uid_to_name(uid_t uid, char buf[])
{
    struct passwd* user;
    if ((user = getpwuid(uid)) == NULL)
        sprintf(buf, "%u", uid);    // Can't find a user with the same uid
    else
        sprintf(buf, "%s", user->pw_name);
}

/*
 * convert gid to group name
 */
void gid_to_name(gid_t gid, char buf[])
{
    struct group* grp;
    if ((grp = getgrgid(gid)) == NULL)
        sprintf(buf, "%u", gid);
    else
        sprintf(buf, "%s", grp->gr_name);
}

#endif

/*
 * Get string of file size
 */
void getf_size(siz_t siz, char buf[6])
{
    const char *unit[5] = { "", "Ki", "Mi", "Gi", "Ti" };     // the unit of file size (none, Ki, Mi, Gi, Ti)
    int i = 0;  // a flag to show which unit to choose
    double size = siz;
    while (size > 999) {
        size /= 1024;
        i++;
    }
    if (size < 10)
        sprintf(buf, "%3.1f", size);
    else
        sprintf(buf, "%3.0f", size);
    strcat(buf, unit[i]);
}

/*
 * convert time_t to string format like dd Mon 
 */
void strtime(const time_t t, char buf[])
{
    // get current system time
    time_t now;
    time(&now);
    struct tm *now_time = localtime(&now);
    int now_year = now_time->tm_year;
    struct tm *mdf_time = localtime(&t);    // modifid time
    if (mdf_time->tm_year == now_year) // file modifid in current year
        sprintf(buf, "%2d %3s %2d:%02d", mdf_time->tm_mday, str_Mon[mdf_time->tm_mon],
                                        mdf_time->tm_hour, mdf_time->tm_min);
    else
        sprintf(buf, "%2d %3s %5d", mdf_time->tm_mday, str_Mon[mdf_time->tm_mon],
                                        mdf_time->tm_year + 1900);
}


/*-------------------                     ---------------------*/
/*-------------------   Public function   ---------------------*/
/*-------------------                     ---------------------*/

#ifdef linux

/*
 * Set fexdet struct with given dirent to designated buffer
 */
int setfex(ALL_PLAT_DIRENT* fd, struct fexdet* buf)
{
    char *fan = malloc(1024);   // file absolute name
    strcpy(fan, path);          // copy the file absolute path
    strcat(fan, "/");
    strcat(fan, fd->d_name);    // add the file name to absolute path

    struct stat *fstat = malloc(sizeof(struct stat));
    int flag;   // the flag to show stat function is successful
    if ((flag = stat(fan, fstat)) == -1) {
        printf("%s: %s.\n", fan, strerror(errno));
        return ERROR;
    }

    buf->inode = fd->d_ino;                 // get inode
    getf_permis(fstat->st_mode, buf->permis);   // get permisstion
    buf->links = fstat->st_nlink;           // get links
    buf->isDir = S_ISDIR(fstat->st_mode);   // directory not display size
    // get size
    buf->size = fstat->st_size;
    buf->str_size[0] = '\0';
    getf_size(buf->size, buf->str_size);
    
    buf->blocks = fstat->st_blocks;         // get blocks
    uid_to_name(fstat->st_uid, buf->user);  // get user name
    gid_to_name(fstat->st_gid, buf->group); // get user group name
    // get latest modified time
    buf->sec_time = fstat->st_mtim.tv_sec;
    strtime(buf->sec_time, buf->date_modify);    
    buf->name = fd->d_name;                 // get name

    free(fstat);
    free(fan);    // free heap memory
}

/*
 * Compare file name function
 */
int fname_cmp(void *f1, void *f2)
{
    return strcmp(((struct fexdet*)f1)->name, ((struct fexdet*)f2)->name);
}

/*
 * Compare file size
 */
int fsize_cmp(void *f1, void *f2)
{
    off_t s_dif = ((struct fexdet*)f1)->size - ((struct fexdet*)f2)->size;
    // sign(s_dif)
    return (s_dif != 0) | s_dif >> (sizeof(s_dif) * 8 - 1);
}

/*
 * Compare file modified date
 */
int ftime_cmp(void *f1, void *f2)
{
    time_t t_dif = ((struct fexdet*)f1)->sec_time - ((struct fexdet*)f2)->sec_time;
    // sign(s_dif)
    return (t_dif != 0) | t_dif >> (sizeof(t_dif) * 8 - 1);
}

/*
 * Free fexdet struct in heap
 */
void fexfree(struct fexdet *f)
{
    free(f);
}

#endif