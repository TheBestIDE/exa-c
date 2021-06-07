#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

#include "include/pcolor.h"
#include "include/grid.h"
#include "include/global.h"

/*
 *  Path Parameter 
 */
char path[1024] = {0};   // The directory path to display

int main(int argc, char* argv[])
{
    // Default running path
    path[0] = '.';
    // Open the Folder
    DIR* dir = opendir(path);
    if (dir == NULL) {
        fprintf(stderr, "Open diretory");
        return ERROR;
    }

    print_ex_grd(dir);

    free(dir);

    return 0;
}