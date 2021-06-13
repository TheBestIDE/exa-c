/*
 *  > File name: list.h
 *  > Action: provide a thread unsafe version for double linked list
 */

#ifndef _LIST_H
#define _LIST_H

#include <limits.h>

typedef char BOOL;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef unsigned long ndlist_t;
typedef struct doub_lik_li_node dlist_node;

// double Linked List Node
struct doub_lik_li_node {
    dlist_node *pre;    // previous pointer
    void *dat;  // data pointer
    dlist_node *nxt;    // next pointer
} ;

// double Linked List with head node
typedef struct doub_lik_li {
    ndlist_t num;    // number of list node
    dlist_node *head;   // head node
} dlist;

// define sort mode
typedef int srt_mod;
// sort asc 
#define _SRT_MOD_ASC 0
// sort desc
#define _SRT_MOD_DSC INT_MIN

dlist *init_lst();
dlist_node *init_lstnode();
dlist_node *fst(dlist*);
dlist_node *end(dlist*);
BOOL is_in_lst(dlist*, dlist_node*);
void ins_pre_lst(dlist*, dlist_node*, dlist_node*);
void ins_aft_lst(dlist*, dlist_node*, dlist_node*);
void add_lst(dlist*, void*);
dlist_node *out_lst(dlist*, dlist_node*);
dlist_node *fnd_lst(dlist*, void*);
void srt_lst(dlist*, int (*)(void*, void*), srt_mod);
void free_lstnode(dlist_node*, void (*)());
void free_lst(dlist*, void (*)());

#endif