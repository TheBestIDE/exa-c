#include "list.h"
#include <stdlib.h>

/*
 * Return a initial list
 */
dlist *init_lst()
{
    dlist *p = malloc(sizeof(dlist));
    p->head = init_lstnode();
    p->fst = p->head->nxt;
    p->num = 0;
    return p;
}

/*
 * Return a initial list node
 */
dlist_node *init_lstnode()
{
    dlist_node *p = malloc(sizeof(dlist_node));
    p->pre = NULL;
    p->dat = NULL;
    p->nxt = NULL;
    return p;
}

/*
 * Return if the node is in the given list
 */
BOOL is_in_lst(dlist *li, dlist_node *node)
{
    // list not exist
    if (li == NULL)
        return FALSE;
    for (dlist_node* n = li->fst;
         n != NULL;
         n = n->nxt)
        if (node == n)   // find it, return true
            return TRUE;
    // finally not found, return false
    return FALSE;
}

/*
 * Insert a list node before a given list node
 */
void ins_pre_lst(dlist *li, dlist_node *aft_node, dlist_node *node)
{
    // li = null ------ (ins_aft_lst function judge it)
    // or aft_node = null
    // or node = null ------ (ins_aft_lst function judge it)
    // or pre_node is not in the list
    // or node is in the list ------ (ins_aft_lst function judge it)
    // can't insert
    if (aft_node != NULL
        || is_in_lst(li, aft_node))
        ins_aft_lst(li, aft_node->pre, node);   // equals insert after previous node
}

/*
 * Insert a list node after a given list node
 */
void ins_aft_lst(dlist *li, dlist_node *pre_node, dlist_node *node)
{
    // li = null
    // or pre_node = null
    // or node = null
    // or pre_node is not in the list
    // or node is in the list
    // can't insert
    if (li == NULL
        || pre_node == NULL
        || node == NULL
        || !is_in_lst(li, pre_node)
        || is_in_lst(li, node))
        return;
    // insert part
    node->pre = pre_node;
    node->nxt = pre_node->nxt;
    if (pre_node->nxt != NULL)  // pre_node is not a last node
        pre_node->nxt->pre = node;
    pre_node->nxt = node;
    li->num++;  // list number add
}

/*
 * Take out a list node from list and return it
 */
dlist_node *out_lst(dlist *li, dlist_node *node)
{
    if (node == NULL
        || !is_in_lst(li, node))
        return NULL;
    node->pre->nxt = node->nxt;
    if (node->nxt != NULL)  // node is not last node
        node->nxt->pre = node->pre;
    li->num--;
    return node;
}

/*
 * Free the list node
 * Parameter:
 * _func_: The function to free the struct in data pointer
 */
void free_lstnode(dlist_node *node, void (*_func_)())
{
    if (node == NULL)
        return;
    _func_(node->dat);
    free(node);
}

/*
 * Free all of the list
 * Parameter:
 * _func_: The function to free the struct in data pointer
 */
void free_lst(dlist *li, void (*_func_)())
{
    for (dlist_node *node = li->fst;
         node != NULL;
         node = node->nxt)
        free_lstnode(node, _func_);
}