#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum color
{
    Red,
    Black
} color;

typedef struct treenode
{
    struct treenode *left, *right, *parent;
    int data;
    color color;
} treenode;

typedef struct rbtree
{
    struct treenode *root;
} rbtree;

#define NIL (&sentinel)

treenode sentinel = {
    .color = Black, .left = NIL, .right = NIL, .parent = NULL, .data = 0};

treenode *createnode(int data)
{
    treenode *node = (treenode *)malloc(sizeof(treenode));
    if (node != NULL)
    {
        node->data = data;
        node->parent = NULL;
        node->right = node->left = NIL;
        node->color = Red; // every new node should be colored red
    }
    return node;
}

rbtree *createtree() {
    rbtree *tree = (rbtree*)malloc(sizeof(rbtree));
    tree->root = NIL;
    return tree;
}

void rightrotate(rbtree *tree, treenode *x)
{
    // find parent, y, t2
    treenode *y = x->left;
    treenode *t2 = y->right;
    treenode *p = x->parent;

    // parent <-> y
    y->parent = p;
    if (p != NULL)
    {
        if (p->left == x)
        {
            p->left = y;
        }
        else
        {
            p->right = y;
        }
    }
    else
    {
        tree->root = y;
    }

    // y <-> x
    y->right = x;
    x->parent = y;

    // x <-> t2
    x->left = t2;
    if (t2 != NIL)
    {
        t2->parent = x;
    }
}

void leftrotate(rbtree *tree, treenode *y)
{
    // find parent, x, t2
    treenode *x = y->right;
    treenode *t2 = x->left;
    treenode *p = y->parent;

    // parent <-> x
    x->parent = p;
    if (p != NULL)
    {
        if (p->left == y)
        {
            p->left = x;
        }
        else
        {
            p->right = x;
        }
    }
    else
    {
        tree->root = x;
    }

    // x <-> y
    x->left = y;
    y->parent = x;

    // y <-> t2
    y->right = t2;
    if (t2 != NIL)
    {
        t2->parent = y;
    }
}

/*
    g-p-z as line
          g
         / \
        p   u
       /
      z
    g-p-z as triangle
          g
         / \
        p   u
         \
          z
    g: Grand Parent Node
    p: Parent Node
    u: Uncle Node
    z: New Added Node (the node that make the tree imbalanced)
case 0: z is root -> recolor to black -> done
case 1: p is Black -> do nothing -> done
case 2: p is red and u is red -> recolor p, u to Black, g to Red -> set z to g -> do futher rebalance
case 3: p is red and u is black and g-p-z triangle -> rotate p make g-z-p line -> to case 4
case 4: p is red and u is black and g-p-z line -> rotate g toward u -> recolor p to Black, g to Red
*/
void insertfixup(rbtree *tree, treenode *z)
{
    // skip case 0, 1
    while (z != tree->root && z->parent->color == Red)
    {
        /*
        since parent red -> grandparent must exist as black node
        divide to two part
                 g         g
                /   and     \
               p             p
        (left child)  (right child)
        */
        treenode *u, *p, *g;
        p = z->parent;
        g = p->parent;
        // left child
        if (p == g->left)
        {
            u = g->right;
            // case 2
            if (u->color == Red)
            {
                p->color = u->color = Black;
                g->color = Red;
                z = g;
            }
            else
            {
                // case 3
                if (z == p->right)
                {
                    /*
                       g
                      /
                     p
                      \
                       z
                     swap z and p
                     then rotate
                    */
                    treenode *tmp = z;
                    z = p;
                    p = tmp;
                    leftrotate(tree, z);
                }
                // case 4
                g->color = Red;
                p->color = Black;

                rightrotate(tree, g);
            }
        }
        else
        { // right child
            u = g->left;
            // case 2
            if (u->color == Red)
            {
                p->color = u->color = Black;
                g->color = Red;
                z = g;
            }
            else
            {
                // case 3
                if (z == p->left)
                {
                    /*
                       g
                        \
                         p
                        /
                       z
                     swap z and p
                     then rotate
                    */
                    treenode *tmp = z;
                    z = p;
                    p = tmp;
                    rightrotate(tree, z);
                }
                // case 4
                g->color = Red;
                p->color = Black;

                leftrotate(tree, g);
            }
        }
    }
    // case 1 -> do nothing
    // case 0 -> recolor root
    tree->root->color = Black;
}

void insert(rbtree *tree, int data)
{
    if (tree->root == NIL)
    {
        treenode *newnode = createnode(data);
        newnode->color = Black;
        tree->root = newnode;
        return;
    }
    treenode *prev = tree->root, *curr = NULL;
    while (prev != NIL)
    {
        curr = prev;
        if (data == prev->data)
        {
            // conflict
        }
        else if (data < prev->data)
        {
            prev = prev->left;
        }
        else if (data > prev->data)
        {
            prev = prev->right;
        }
    }
    if (data == curr->data)
    {
        printf("insert %d fail, conflict data\n", data);
        return;
    }
    treenode *newnode = createnode(data);
    if (data > curr->data)
    {
        curr->right = newnode;
        newnode->parent = curr;
    }
    if (data < curr->data)
    {
        curr->left = newnode;
        newnode->parent = curr;
    }
    insertfixup(tree, newnode);
}

treenode *search(rbtree *tree, int target)
{
    if (tree->root == NIL)
    {
        return NULL;
    }
    treenode *curr = tree->root;

    while (curr != NIL) {
        if (target == curr->data) {
            return curr;
        } else if (target > curr->data) {
            curr = curr->right;
        } else {
            curr = curr->left;
        }
    }
    return NULL;
}

/*
    find inorder successor
*/
treenode *findsuccessor(treenode *node)
{
    treenode *curr = node;
    while (curr->left != NIL)
    {
        curr = curr->left;
    }
    return curr;
}

void deletefixup(rbtree *tree, treenode *x)
{
    /*
        double black
        z was black and x is also black
        w is the sibling of x
    */
    while (x != tree->root && x->color == Black) {
        /*
            p
           /
          x
        x is left child
        */
        if (x == x->parent->left) {
            treenode *w = x->parent->right;
            // case 0. sibling is red
            if (w->color == Red) {
                w->color = Black;
                x->parent->color = Red;

                leftrotate(tree, x->parent);
                w = x->parent->right;
            }
            // both sibling's children are black
            if (w->left->color == Black && w->right->color == Black) {
                w->color = Red;
                x = x->parent;
            } else {
                /*
                    p
                   / \
                  x   w
                     / \
                    wl  wr(w->right)
                */
                if (w->right->color == Black) {
                    w->left->color = Black;
                    w->color = Red;

                    rightrotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                w->parent->color = Black;
                x->right->color = Black;

                leftrotate(tree, x->parent);
                x = tree->root;
            }
        } else { // x is right child
            treenode *w = x->parent->left;
            // case 0. red sibling
            if (w->color == Red) {
                w->color = Black;
                x->parent->color = Red;

                rightrotate(tree, x->parent);
                w = x->parent->left;
            }
            // both children of sibling are black
            if (w->right->color == Black && w->left->color == Black) {
                w->color = Red;
                x = x->parent;
            } else {
                if (w->left->color == Black) {
                    w->right->color = Black;
                    w->color = Red;

                    leftrotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = Black;
                w->left->color = Black;

                rightrotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = Black;
}

void delete(rbtree *tree, int target)
{
    if (tree->root == NIL)
    {
        printf("target: %d not found.", target);
        return;
    }
    /*
        target(int): the target value user want to delete
        z (treenode*): pointer point to the node value equals to target
        y (treenode*): pointer point to the node that will be delete and free memory
        x (treenode*): pointer point to the node that will replace node2delete (could be nil)
    */
    // step 1, find targetnode, node2delete, x
    treenode *z = NULL, *y = NULL, *x = NULL;
    z = search(tree, target);
    // targetnode has zero or one child node
    if (z->right == NIL || z->left == NIL)
    {
        y = z;
    }
    else
    { // target node has two children node
        y = findsuccessor(z->right);
    }
    color y_color = y->color;

    if (y->left != NIL)
    {
        x = y->left;
    }
    else
    {
        x = y->right;
    }

    // step 2. delete node2delete and fix pointers (bst delete)
    // parent <-> x
    x->parent = y->parent;
    if (y->parent != NIL)
    { // node2delete is not root
        if (y == y->parent->left)
        { // is left child
            y->parent->left = x;
        }
        else
        { // is right child
            y->parent->right = x;
        }
    }

    // targetnode has 2 children nodes
    if (y != z)
    {
        z->data = y->data;
        free(z);
    }
    // when y is red, no need to fix.
    if (y_color == Black)
    {
        deletefixup(tree, x);
    }
}

/*
    inorder traversal
*/
void inorder(treenode *node)
{
    if (node == NIL)
        return;
    inorder(node->left);
    printf("%d(%c) ", node->data, node->color == Red ? 'R' : 'B');
    inorder(node->right);
}

int main()
{
    rbtree *tree = createtree();
    insert(tree, 25);
    insert(tree, 28);
    insert(tree, 20);
    insert(tree, 26);
    insert(tree, 11);
    insert(tree, 2);
    insert(tree, 9);
    insert(tree, 7);
    insert(tree, 10);
    printf("tree root: %d\n", tree->root->data);
    printf("inorder traversal:\n");
    inorder(tree->root);
    printf("\n");

    printf("===== delete =====\n");
    delete(tree, 10);
    printf("tree root: %d\n", tree->root->data);
    printf("inorder traversal:\n");
    inorder(tree->root);
    printf("\n");

    delete(tree, 26);
    printf("tree root: %d\n", tree->root->data);
    printf("inorder traversal:\n");
    inorder(tree->root);
    printf("\n");

    delete(tree, 25);
    printf("tree root: %d\n", tree->root->data);
    printf("inorder traversal:\n");
    inorder(tree->root);
    printf("\n");
    return 0;
}