#include <stdio.h>
#include <stdlib.h>

#include "include/pcolor.h"
#include "include/grid.h"
#include "include/global.h"
#include "include/syscall.h"

/*
 *  Path Parameter 
 */
char path[1024] = {0};   // The directory path to display
unsigned char gap_num = 1;  // The number of space between two items
unsigned int print_item = 1;        // bit flag of print items

int main(int argc, char* argv[])
{
    // Default running path
    path[0] = '.';

    // if platform is supported
    #if IS_SUPPORT

    // Open the Folder
    ALL_PLAT_DIR* dir = open_dir_forall(path);
    if (dir == NULL) {
        fprintf(stderr, "Diretory can't open.");
        return ERROR;
    }
    
    print_ex_ttl();
    print_ex_grd(dir);

    close_dir_forall(dir);

    #else

    fprintf(stderr, "Not support for this platform.");

    #endif

    return 0;
}