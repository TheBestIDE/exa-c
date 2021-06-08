#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

#include "include/pcolor.h"
#include "include/fexdet.h"
#include "include/global.h"

#define PRINT_GAP(num) printf("%*s", num, "")   // print gap between two items
#define ALL_EX_NUM 9    // number of all extend items

extern unsigned char gap_num;


/* -----------------    Print title function    ------------------------*/

// The type of function pointer to print extend title
typedef void(*exttl_prt_func)(const char []);

/*
 * Print inode title with 3 space behind
 */
void print_inode_ttl(const char t[])
{
    PRINT_GAP(3);
    PRINT_ATTR_LIN;
    printf("%s", t);
    PRINT_ATTR_ULIN;
}

/*
 * Print size title with 1 space behind
 */
void print_siz_ttl(const char t[])
{
    PRINT_GAP(1);
    PRINT_ATTR_LIN;
    printf("%s", t);
    PRINT_ATTR_ULIN;
}

/*
 * Print other title with no special format
 */
void print_oth_ttl(const char t[])
{
    PRINT_ATTR_LIN;
    printf("%s", t);
    PRINT_ATTR_ULIN;
}

// extend file information title
const char *extitle[ALL_EX_NUM] = { 
    "inode", "Permissions", "Links",
    "Size", "Blocks", "User", "Group",
    "Date Modified", "Name" 
};

// The function pointer to print extend title
const exttl_prt_func exttl_prt[ALL_EX_NUM] = {
    print_inode_ttl, print_oth_ttl, print_oth_ttl,
    print_siz_ttl, print_oth_ttl, print_oth_ttl, print_oth_ttl,
    print_oth_ttl, print_oth_ttl
};

/*
 * Print extand 9 title fields with underline 
 */
void print_ex_ttl()
{
    for(int i = 0; i < ALL_EX_NUM; i++) {
        exttl_prt[i](extitle[i]);
        PRINT_GAP(gap_num);
    }
    printf("\n");   // end of title
}


/*---------------------    Print item message function     -----------------------*/


// The type of function pointer to print extend file message
typedef void(*mes_prt_func)(struct fexdet *);

/*
 * Print inode with colors
 */
void print_inode(struct fexdet *f)
{
    PRINT_FONT_MAG;
    printf("%8lu", f->inode);
}

/* 
 * Print permission with colors
 */
void print_permis(struct fexdet *f)
{
    // first position show if it is a directory
    if (f->permis[0] == 'd')
        PRINT_FONT_CYA;
    else
        PRINT_FONT_WHI;
    putchar(f->permis[0]);
    for (int i = 1; i < 10; i++) {
        if (f->permis[i] == '-') {
            PRINT_FONT_WHI;
        }
        else {
            printf("\033[%dm", (i + 1) % 3 + 31);
        }
        putchar(f->permis[i]);
    }
    putchar(' ');
}

/*
 * Print hard links with colors
 */
void print_links(struct fexdet *f)
{
    PRINT_FONT_RED;
    printf("%5lu", f->links);
}

/*
 * Print size if it's not a directory 
 */
void print_size(struct fexdet *f)
{
    if (f->isDir) {
        PRINT_FONT_GRE;
        printf("%5c", '-');
    }
    else {
        PRINT_FONT_GRE;
        printf("%5s", f->size);
    }
}

/*
 * Print blocks if it's not a directory 
 */
void print_blocks(struct fexdet *f)
{
    if (f->isDir) {
        PRINT_FONT_CYA;
        printf("%6c", '-');
    }
    else {
        PRINT_FONT_CYA;
        printf("%6lu", f->blocks);
    }
}

/*
 * Print file owner user name
 */
void print_user(struct fexdet *f)
{
    PRINT_FONT_YEL;
    printf("%-4s", f->user);
}

/*
 * Print file owner group name
 */
void print_group(struct fexdet *f)
{
    PRINT_FONT_YEL;
    printf("%-5s", f->group);
}

/*
 * Print the last modified date of file
 */
void print_date_modify(struct fexdet *f)
{
    PRINT_FONT_CYA;
    printf("%13s", f->date_modify);
}

/*
 * Print file name with colors
 */
void print_name(struct fexdet *f)
{
    if (f->isDir)
        PRINT_FONT_CYA;
    else 
        PRINT_FONT_WHI;
    printf("%-s", f->name);
}

// The function pointer to print extend message
const mes_prt_func exmes_prt[ALL_EX_NUM] = {
    print_inode, print_permis, print_links,
    print_size, print_blocks, print_user, print_group,
    print_date_modify, print_name
};

/*
 * Formatted print fexdet with given struct
 */
void printfex(struct fexdet *f)
{
    for (int i = 0; i < ALL_EX_NUM; i++) {
        exmes_prt[i](f);
        PRINT_GAP(gap_num);
    }
    // end of file detail
    PRINT_FONT_WHI;
    printf("\n");
}


/*-----------------------     Public Function     ------------------------*/


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