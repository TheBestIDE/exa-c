#include "list.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/*
 * Return a initial list
 */
dlist *init_lst()
{
    dlist *p = malloc(sizeof(dlist));
    p->head = init_lstnode();
    p->head->pre = p->head;
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
 * Return the first data node of given list
 */
dlist_node *fst(dlist *li)
{
    return li != NULL ? li->head->nxt : NULL;
}

dlist_node *end(dlist *li)
{
    if (li == NULL
        || li->head->nxt == NULL)
        return NULL;
    dlist_node *p;
    for (p = li->head->nxt;
         p->nxt != NULL;
         p = p->nxt);
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
    for (dlist_node* n = fst(li);
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
    // test if number is overflow
    if (li->num + 1 < li->num) {
        li->num++;  // list number add
    }
    else {
        fprintf(stderr, "list number over flow.\n");
        return;
    }

    // insert part
    node->pre = pre_node;
    node->nxt = pre_node->nxt;
    if (pre_node->nxt != NULL)  // pre_node is not a last node
        pre_node->nxt->pre = node;
    pre_node->nxt = node;
}

void add_lst(dlist *li, void *data)
{
    if (li == NULL)
        return;
    dlist_node *new_node = init_lstnode();
    new_node->dat = data;
    dlist_node *node;
    for (node = li->head;
         node->nxt != NULL;
         node = node->nxt);
    node->nxt = new_node;
    new_node->pre = node;
}

/*
 * Take out a list node from list and return it
 */
dlist_node *out_lst(dlist *li, dlist_node *node)
{
    if (node == NULL
        || !is_in_lst(li, node))
        return NULL;
    // test if number is underflow
    if (li->num - 1 > li->num) {
        li->num--;
    } else {
        fprintf(stderr, "list number under flow.\n");
        return NULL;
    }

    node->pre->nxt = node->nxt;
    if (node->nxt != NULL)  // node is not last node
        node->nxt->pre = node->pre;
    return node;
}

/*
 * Find a node with given data from list
 */
dlist_node *fnd_lst(dlist *li, void *data)
{
    if (li == NULL)
        return NULL;
    for (dlist_node *node = fst(li);
         node != NULL;
         node = node->nxt)
        if (node->dat == data)
            return node;
    return NULL;
}

/*
 * Merge the left and right 
 */
dlist_node *_merge(dlist_node *lh, dlist_node *rh, int (*_cmp_)(void*, void*), srt_mod mode)
{
    dlist_node *tempHead = init_lstnode();  // temporary head node
    dlist_node *p = tempHead;
    while (lh && rh) {
        // if mode is asc, compare result xor 0, no change.
        // if mode is desc, compare result xor 0x8000 0000, 
        // change negative number to positive number,
        // change positive number and 0 to negative number,
        // so that reverse result.
        if ((_cmp_(lh->dat, rh->dat) ^ mode) <= 0) {
            p->nxt = lh;
            lh->pre = p;
            lh = lh->nxt;
        } else {
            p->nxt = rh;
            rh->pre = p;
            rh = rh->nxt;
        }
        p = p->nxt;
    }
    
    if (lh == NULL && rh != NULL) {
        p->nxt = rh;
        rh->pre = p;
    } else if (rh == NULL && lh != NULL) {
        p->nxt = lh;
        lh->pre = p;
    } else {    // lh is null and rh is null
        p->nxt = NULL;
    }

    p = tempHead->nxt;
    tempHead->nxt = NULL;
    free(tempHead);
    return p;
}

/*
 * Use merge sort to sort list
 */
dlist_node *_merge_srt_lst(dlist_node *head, int (*_cmp_)(void*, void*), srt_mod mode)
{
    // recursive termination condition
    if (head == NULL || head->nxt == NULL)
        return head;
    dlist_node *p = head;
    dlist_node *q = head;
    while (q != NULL
        && q->nxt != NULL) {
        p = p->nxt;
        q = q->nxt->nxt;
    }
    // cut list
    p->pre->nxt = NULL;
    p->pre = NULL;
    
    dlist_node *lhalf = _merge_srt_lst(head, _cmp_, mode);
    dlist_node *rhalf = _merge_srt_lst(p, _cmp_, mode);
    return _merge(lhalf, rhalf, _cmp_, mode);
}

/*
 * Sort list item using given compare function
 * Parameter: 
 * _cpm_: The function to compare two data 
 */
void srt_lst(dlist *li, int (*_cmp_)(void*, void*), srt_mod mode)
{
    dlist_node *p = fst(li);
    if (p == NULL
        || p->nxt == NULL)
        return;
    li->head->nxt = _merge_srt_lst(p, _cmp_, mode);
    li->head->nxt->pre = li->head;
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
    for (dlist_node *node = fst(li);
         node != NULL;
         node = node->nxt)
        free_lstnode(node, _func_);
}