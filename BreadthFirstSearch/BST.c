#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BST.h"


static node *createnode(int data) {
    node *n = (node*)malloc(sizeof(node));
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

bst *createtree() {
    bst *t = (bst*)malloc(sizeof(bst));
    t->root = NULL;
    return t;
}

void insert(bst *t, int data) {
    node *newnode = createnode(data);
    node *curr = t->root;
    node *parent = NULL;
    while (curr != NULL) {
        parent = curr;
        if (data < curr->data) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    if (parent != NULL) {
        if (data > parent->data) {
            parent->right = newnode;
        } else {
            parent->left = newnode;
        }
    } else {
        t->root = newnode;
    }
}