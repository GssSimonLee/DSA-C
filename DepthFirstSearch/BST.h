#ifndef BST_H
#define BST_H

typedef struct node {
    struct node *left, *right;
    int data;
} node;

typedef struct bst {
    struct node *root;
} bst;

bst *createtree();
void freetree(bst*);
void insert(bst*, int);

#endif