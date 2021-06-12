/*
 *  > File name: list.h
 *  > Action: provide a thread unsafe version for double linked list
 */

#ifndef _LIST_H
#define _LIST_H

typedef char BOOL;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef unsigned long ndlist_t;

// double Linked List with head node
typedef struct doub_lik_li {
    ndlist_t num;    // number of list node
    dlist_node *fst; // first data node
    dlist_node *head;    // head node
} dlist;

// double Linked List Node
typedef struct doub_lik_li_node {
    dlist_node *pre;  // previous pointer
    void *dat;  // data pointer
    dlist_node *nxt; // next pointer
} dlist_node;

dlist *init_lst();
dlist_node *init_lstnode();
BOOL is_in_lst(dlist*, dlist_node*);
void ins_pre_lst(dlist*, dlist_node*, dlist_node*);
void ins_aft_lst(dlist*, dlist_node*, dlist_node*);
dlist_node *out_lst(dlist*, dlist_node*);
void free_lstnode(dlist_node*, void (*)());
void free_lst(dlist*, void (*)());

#endif