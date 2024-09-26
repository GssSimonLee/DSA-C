#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum Color
{
    Red,
    Black
} Color;

typedef struct treenode
{
    struct treenode *left, *right, *parent;
    int data;
    Color color;
} treenode;

treenode *createnode(int data)
{
    treenode *node = (treenode *)malloc(sizeof(treenode));
    if (node != NULL)
    {
        node->data = data;
        node->parent = node->right = node->left = NULL;
        node->color = Red; // every new node should be colored red
    }
    return node;
}

treenode *rightrotate(treenode *x)
{
    treenode *y = x->left;
    treenode *t2 = y->right;

    y->right = x;
    x->parent = y;

    x->left = t2;
    if (t2 != NULL)
        t2->parent = x;
    return y;
}

treenode *leftrotate(treenode *y)
{
    treenode *x = y->right;
    treenode *t2 = x->left;

    x->left = y;
    y->parent = x;

    y->right = t2;
    if (t2 != NULL)
        t2->parent = y;
    return x;
}

treenode *insert(treenode *root, int data)
{
    treenode *curr = root, *prev = NULL;
    while (curr != NULL)
    {
        prev = curr;
        if (data == curr->data)
        {
            // conflict
        }
        else if (data < curr->data)
        {
            curr = curr->left;
        }
        else if (data > curr->data)
        {
            curr = curr->right;
        }
    }
    if (data == prev->data)
    {
        printf("insert %d fail, conflict data\n", data);
        return root;
    }
    treenode *newnode = createnode(data);
    if (data > prev->data)
    {
        prev->right = newnode;
        newnode->parent = prev;
    }
    if (data < prev->data)
    {
        prev->left = newnode;
        newnode->parent = prev;
    }
    root = fixup(root, newnode);
    return root;
}

/*
    G-P-Z as line
          G
         / \
        P   U
       /
      Z
    G-P-Z as triangle
          G
         / \
        P   U
         \
          Z
    G: Grand Parent Node
    P: Parent Node
    U: Uncle Node
    Z: New Added Node (the node that make the tree imbalanced)
case 0: Z is root -> recolor to black -> done
case 1: P is Black -> do nothing -> done
case 2: P is red and U is red -> recolor P, U to Black, G to Red -> set Z to G -> do futher rebalance
case 3: P is red and U is black and G-P-Z triangle -> rotate P make G-Z-P line -> to case 4
case 4: P is red and U is black and G-P-Z line -> rotate G toward U -> recolor P to Black, G to Red
*/
treenode *fixup(treenode *root, treenode *z)
{
    // skip case 0, 1
    while (z != root && z->parent->color == Red)
    {
        // divide to two part
        //         G         G
        //        /   and     \
        //       P             P
        // (left child)  (right child)
        treenode *uncle, *parent, *grandparent;
        parent = z->parent;
        grandparent = parent->parent;
        // left child
        if (parent == grandparent->left)
        {
            uncle = grandparent->right;
            if (uncle->color = Red)
            {
                parent->color = uncle->color = Black;
                grandparent->color = Red;
                z = grandparent;
            }
            else
            {
                if (z == parent->right)
                {
                    //   G
                    //  /
                    // P
                    //  \
                    //   Z
                    // swap Z and P
                    treenode *tmp = z;
                    z = parent;
                    parent = tmp;
                    grandparent->left = leftrotate(z);
                }
                grandparent->color = parent->color = Black;
                treenode *grandgrandparent = grandparent->parent;
                if (grandgrandparent->left == grandparent)
                {
                    grandgrandparent->left = rightrotate(grandparent);
                }
                else
                {
                    grandgrandparent->right = rightrotate(grandparent);
                }
            }
        }
        else
        { // right child
            uncle = grandparent->right;
            if (uncle->color = Red)
            {
                parent->color = uncle->color = Black;
                grandparent->color = Red;
                z = grandparent;
            }
            else
            {
                if (z == parent->left)
                {
                    //   G
                    //    \
                    //     P
                    //    /
                    //   Z
                    // swap Z and P
                    treenode *tmp = z;
                    z = parent;
                    parent = tmp;
                    grandparent->right = rightrotate(z);
                }
                grandparent->color = parent->color = Black;
                treenode *grandgrandparent = grandparent->parent;
                if (grandgrandparent->right == grandparent)
                {
                    grandgrandparent->right = leftrotate(grandparent);
                }
                else
                {
                    grandgrandparent->left = leftrotate(grandparent);
                }
            }
        }
    }
    // case 1 -> do nothing
    // case 0 -> recolor root
    root->color = Black;
}