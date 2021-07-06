#include "btree.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Init a new binary tree
 */
btree *init_btree()
{
    btree *p = malloc(sizeof(btree));
    p->head = init_btree_node();
    p->head->left = p->head;
    p->num = 0;
    return p;
}

/*
 * Init a new binary tree node
 */
btree_node *init_btree_node()
{
    btree_node *p = malloc(sizeof(btree_node));
    p->left = NULL;
    p->right = NULL;
    p->dat = NULL;
    return p;
}

/*
 * Pre order traverse binary tree
 */
int pre_traverse(btree_node *t, void (*visit)(btree_node*))
{
    if (t == NULL)
        return 1;
    else {
        visit(t);   // visit t node
        pre_traverse(t->left, visit);   // visit left child
        pre_traverse(t->right, visit);  // visit right child
    }
}

/*
 * In order traverse binary tree
 */
int in_traverse(btree_node *t, void (*visit)(btree_node*))
{
    if (t == NULL)
        return 1;
    else {
        in_traverse(t->left, visit);   // visit left child
        visit(t);   // visit t node
        in_traverse(t->right, visit);  // visit right child
    }
}

/*
 * Post order traverse binary tree
 */
int post_traverse(btree_node *t, void (*visit)(btree_node*))
{
    if (t == NULL)
        return 1;
    else {
        post_traverse(t->left, visit);   // visit left child
        post_traverse(t->right, visit);  // visit right child
        visit(t);   // visit t node
    }
}

void (*_free_)() = NULL;

/*
 * Free the tree node using default free function
 */
void free_btreenode(btree_node *node)
{
    if (node == NULL)
        return;
    _free_(node->dat);
    free(node);
}

/*
 * Free all of the tree using given free function
 * Parameter:
 * _func_: The function to free the struct in data pointer
 */
void free_btree(btree *p, void (*_func_)())
{
    _free_ = _func_;
    post_traverse(p->head->right, free_btreenode);  // free start with root node
    free(p->head);  // free head node
    free(p);    // free btree pointer
}

/*
 * Free the tree node using given free function
 * Parameter:
 * _func_: The function to free the struct in data pointer
 */
void free_btreenode_f(btree_node *node, void (*_func_)())
{
    if (node == NULL)
        return;
    _func_(node->dat);
    free(node);
}