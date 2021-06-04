#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#include "include/fexdet.h"
#include "include/global.h"

extern const char path[1024];

// English abbreviation of month
const char *str_Mon[12] = { "Jan", "Feb", "Mat", "Apr",
                            "May", "Jun", "Jul", "Aug",
                            "Sep", "Oct", "Nov", "Dec"};

/*
 * Get string of file size
 */
void getFileSize(struct stat* fstat, char buf[6])
{
    const char *unit[4] = { "", "Ki", "Mi", "Gi" };     // the unit of file size (none, Ki, Mi, Gi)
    int i = 0;  // a flag to show which unit to choose
    float size = fstat->st_size;
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
 * Get string of file permissions
 */
int getFilePermis(struct stat* fstat, char buf[])
{
    // init buffer
    for (int i = 0; i < 10; i++)
        buf[i] = '-';
    // first position is a flag to show if file is a directory
    buf[0] = S_ISDIR(fstat->st_mode) ? 'd' : '.';
    // 1 4 7 position is a flag to show if file owner, group, other have read permission
    for (int i = 1; i < 10; i += 3)
        if (fstat->st_mode >> (i - 1) & 1)
            buf[i] = 'r';
    // 2 5 8 position is a flag to show if file owner, group, other have write permission
    for (int i = 2; i < 10; i += 3)
        if (fstat->st_mode >> (i - 1) & 1)
            buf[i] = 'w';
    // 3 6 9 position is a flag to show if file owner, group, other have read permission
    for (int i = 3; i < 10; i += 3)
        if (fstat->st_mode >> (i - 1) & 1)
            buf[i] = 'x';
    // end of string: '\0'
    buf[10] = 0;
}

/*
 * convert uid to user name
 */
void uidToName(uid_t uid, char buf[])
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
void gidToName(gid_t gid, char buf[])
{
    struct group* grp;
    if ((grp = getgrgid(gid)) == NULL)
        sprintf(buf, "%u", gid);
    else
        sprintf(buf, "%s", grp->gr_name);
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

/*
 * Set fexdet struct with given dirent to designated buffer
 */
int setfex(struct dirent* fd, struct fexdet* buf)
{
    char *fan = malloc(1024); // file absolute name
    strcpy(fan, path);        // copy the file absolute path
    strcat(fan, "/");
    strcat(fan, fd->d_name);    // add the file name to absolute path

    struct stat *fstat = malloc(sizeof(struct stat));
    int flag;   // the flag to show stat function is successful
    if ((flag = stat(fan, fstat)) == -1) {
        printf("%s: %s.\n", fan, strerror(errno));
        return ERROR;
    }

    buf->inode = fd->d_ino;
    getFilePermis(fstat, buf->permis);
    buf->links = fstat->st_nlink;
    buf->size[0] = '\0';
    // directory not display size
    buf->isDir = S_ISDIR(fstat->st_mode);
    getFileSize(fstat, buf->size);
    buf->blocks = fstat->st_blocks;
    uidToName(fstat->st_uid, buf->user);
    gidToName(fstat->st_gid, buf->group);
    strtime(fstat->st_mtim.tv_sec, buf->date_modify);
    buf->name = fd->d_name;

    free(fstat);
    free(fan);    // free heap memory
}