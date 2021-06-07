#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

#include "include/pcolor.h"
#include "include/fexdet.h"
#include "include/global.h"

// extend file information title
const char *extitle[9] = { "inode", "Permissions", "Links",
                         "Size", "Blocks", "User", "Group",
                         "Date Modified", "Name" };

/*
 * Print extand 9 title fields with underline 
 */
void print_ex_ttl()
{
    printf("   ");  // 3 space front of first field
    for(int i = 0; i < 9; i++) {
        PRINT_ATTR_LIN;
        printf("%s", extitle[i]);
        PRINT_ATTR_ULIN;
        printf("  ");    // 2 space between two fields
    }
    printf("\n");   // end of title
}

/* 
 * Print permission with colors
 */
void print_permis(char permis[11])
{
    printf("  ");   // double space
    // first position show if it is a directory
    if (permis[0] == 'd')
        PRINT_FONT_CYA;
    else
        PRINT_FONT_WHI;
    putchar(permis[0]);
    for (int i = 1; i < 10; i++) {
        if (permis[i] == '-') {
            PRINT_FONT_WHI;
        }
        else {
            printf("\033[%dm", (i + 1) % 3 + 31);
        }
        putchar(permis[i]);
    }
    putchar(' ');
}

/*
 * Formatted print fexdet with given struct
 */
void printfex(struct fexdet *f)
{
    PRINT_FONT_MAG;
    printf("%8lu", f->inode);
    print_permis(f->permis);
    PRINT_FONT_RED;
    printf(" %6lu", f->links);
    if (f->isDir) {
        PRINT_FONT_GRE;
        printf(" %5c", '-');
        PRINT_FONT_CYA;
        printf(" %7c", '-');
    }
    else {
        PRINT_FONT_GRE;
        printf(" %5s", f->size);
        PRINT_FONT_CYA;
        printf(" %7lu", f->blocks);
    }
    
    PRINT_FONT_YEL;
    printf("  %-4s", f->user);
    printf("  %-5s", f->group);
    PRINT_FONT_CYA;
    printf(" %14s", f->date_modify);
    if (f->isDir)
        PRINT_FONT_CYA;
    else 
        PRINT_FONT_WHI;
    printf("  %-s", f->name);
    PRINT_FONT_WHI;
    printf("\n");
}

/* 
 * Print the file-struct as grid
 */
int print_ex_grd(DIR* dir)
{
    print_ex_ttl();

    struct dirent *p;
    struct fexdet *f = malloc(sizeof(struct fexdet));
    int flag = 0;   // to show setfex function is successful
    
    // print extend file info 
    while(!flag && (p = readdir(dir)) != NULL) {
        flag = setfex(p, f);
        printfex(f);
    }

    free(f);
    return flag;
}