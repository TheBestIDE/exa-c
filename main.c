#include <stdio.h>
#include <stdlib.h>

#include "include/pcolor.h"
#include "include/grid.h"
#include "include/global.h"
#include "include/syscall.h"
#include "include/flg.h"
#include "lib/list.h"

/*
 *  Path Parameter 
 */
char path[1024] = {0};  // The directory path to display
gap_t gap_num = 1;      // The number of space between two items
flg_t print_mode = 1;       // bit flag of print mode
srt_mod mode = _SRT_MOD_ASC;        // sort mode: asc or desc
pitm_t ipos;    // instruct print items

/*
 * set print item array
 */
void set_prt_item()
{
    ipos.pos_num = 0;
    for(int i = 0; i < ALL_EX_NUM; i++)
        if (print_mode >> i & 1)
            ipos.pos[ipos.pos_num++] = i;
}


int main(int argc, char* argv[])
{
    // Default running path
    path[0] = '.';
    // Default print items
    print_mode = 0xffff;

    // if platform is supported
    #if IS_SUPPORT

    // Set print item
    set_prt_item();

    // Open the Folder
    ALL_PLAT_DIR* dir = open_dir_forall(path);
    if (dir == NULL) {
        fprintf(stderr, "Diretory can't open.");
        return ERROR;
    }
    
    if (print_mode & B_IPTTL)
        print_ex_ttl();
    print_ex_grd(dir);

    close_dir_forall(dir);

    #else

    fprintf(stderr, "Not support for this platform.");

    #endif

    return 0;
}