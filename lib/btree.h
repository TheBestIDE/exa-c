/*
 *  > File name: btree.h
 *  > Action: provide a thread unsafe version for binary tree
 */

#ifndef _B_TREE_H
#define _B_TREE_H

typedef struct binarytree btree;
typedef struct binarytree_node btree_node;
typedef unsigned long btn_t;

struct binarytree_node {
    btree_node *left;   // left child node
    void *dat;      // data pointer
    btree_node *right;  // right child node
};

struct binarytree {
    btree_node *head;
    btn_t num;  // number of binary tree node
};


btree *init_btree();
btree_node *init_btree_node();

int pre_traverse(btree_node *, void (*)(btree_node*));
int in_traverse(btree_node *, void (*)(btree_node*));
int post_traverse(btree_node *, void (*)(btree_node*));

void free_btree(btree *, void (*)());
void free_btreenode_f(btree_node *, void (*)());

#endif