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
    struct treenode *NIL;
} rbtree;

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

rbtree *createtree()
{
    rbtree *tree = (rbtree *)malloc(sizeof(rbtree));
    treenode *nil = createnode(0);
    nil->color = Black;
    tree->root = nil;
    tree->NIL = nil;
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
    if (p != tree->NIL)
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
    if (t2 != tree->NIL)
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
    if (p != tree->NIL)
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
    if (t2 != tree->NIL)
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
        since parent is red -> grandparent must exist as black node
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
    treenode *prev = tree->root, *curr = tree->NIL;
    while (prev != tree->NIL)
    {
        curr = prev;
        if (data < prev->data)
        {
            prev = prev->left;
        }
        else
        {
            prev = prev->right;
        }
    }

    if (curr != NULL && data == curr->data)
    {
        printf("insert %d fail, conflict data\n", data);
        return;
    }
    treenode *newnode = createnode(data);
    newnode->left = newnode->right = tree->NIL;
    newnode->parent = curr;
    if (curr == tree->NIL)
    {
        tree->root = newnode;
    }
    else if (data > curr->data)
    {
        curr->right = newnode;
    }
    else
    {
        curr->left = newnode;
    }

    insertfixup(tree, newnode);
}

treenode *search(rbtree *tree, int target)
{
    if (tree->root == tree->NIL)
    {
        return NULL;
    }
    treenode *curr = tree->root;

    while (curr != tree->NIL)
    {
        if (target == curr->data)
        {
            return curr;
        }
        else if (target > curr->data)
        {
            curr = curr->right;
        }
        else
        {
            curr = curr->left;
        }
    }
    return NULL;
}

/*
    find inorder successor
*/
treenode *findsuccessor(rbtree *tree, treenode *node)
{
    treenode *curr = node;
    while (curr->left != tree->NIL)
    {
        curr = curr->left;
    }
    return curr;
}

void transplant(rbtree *tree, treenode *old, treenode *new)
{
    if (old->parent == tree->NIL)
    {
        tree->root = new;
    }
    else if (old == old->parent->left)
    { // old is its parent's left child
        old->parent->left = new;
    }
    else
    {
        old->parent->right = new;
    }
    new->parent = old->parent;
}

void deletefixup(rbtree *tree, treenode *x)
{
    /*
        double black
        z was black and x is also black
        w is the sibling of x
    */
    while (x != tree->root && x->color == Black)
    {
        /*
            p
           /
          x
        x is left child
        */
        if (x == x->parent->left)
        {
            treenode *w = x->parent->right;
            // case 0. sibling is red
            if (w->color == Red)
            {
                w->color = Black;
                x->parent->color = Red;

                leftrotate(tree, x->parent);
                w = x->parent->right;
            }
            // both sibling's children are black
            if (w->left->color == Black && w->right->color == Black)
            {
                w->color = Red;
                x = x->parent;
            }
            else
            {
                /*
                    p
                   / \
                  x   w
                     / \
                    wl  wr(w->right)
                */
                if (w->right->color == Black)
                {
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
        }
        else
        { // x is right child
            treenode *w = x->parent->left;
            // case 0. red sibling
            if (w->color == Red)
            {
                w->color = Black;
                x->parent->color = Red;

                rightrotate(tree, x->parent);
                w = x->parent->left;
            }
            // both children of sibling are black
            if (w->right->color == Black && w->left->color == Black)
            {
                w->color = Red;
                x = x->parent;
            }
            else
            {
                if (w->left->color == Black)
                {
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

/*
    delete without transplant
*/
void delete2(rbtree *tree, int target)
{
    treenode *z = search(tree, target);
    treenode *y = z;
    treenode *x;
    color y_original_color = y->color;
    if (z == tree->NIL)
    {
        printf("target %d not found in tree\n", target);
        return;
    }
    // z has two children -> find y (successor of z)
    if (z->left != tree->NIL && z->right != tree->NIL)
    {
        y = findsuccessor(tree, z->right);
        y_original_color = y->color;
    }

    // do stuff on y and x
    if (y->left != tree->NIL)
    {
        x = y->left;
    }
    else
    { // y->right != NIL;
        x = y->right;
    }

    x->parent = y->parent;
    // y is not root
    if (y->parent != tree->NIL)
    {
        if (y == y->parent->left)
        {
            y->parent->left = x;
        }
        else
        {
            y->parent->right = x;
        }
    }
    else
    {
        tree->root = x;
    }

    z->data = y->data;

    if (y_original_color == Black)
    {
        deletefixup(tree, x);
    }

    free(y);
}

/*
    delete with transplant
*/
void delete(rbtree *tree, int target)
{
    /*
        target(int): the target value user want to delete
        z (treenode*): pointer point to the node value equals to target
        y (treenode*): pointer point to the node that will be delete and free memory
        x (treenode*): pointer point to the node that will replace node2delete (could be nil)
    */
    // step 1, find z, y, x
    treenode *z = search(tree, target);
    treenode *y = z;
    treenode *x;
    color y_original_color = y->color;
    if (z == tree->NIL)
    {
        printf("target %d not found in tree\n", target);
        return;
    }

    // z has zero or one child (z->right)
    if (z->left == tree->NIL)
    {
        x = z->right;
        transplant(tree, z, z->right);
    }
    else if (z->right == tree->NIL)
    { // z has only left child
        x = z->left;
        transplant(tree, z, z->left);
    }
    else
    { // z has two children
        y = findsuccessor(tree, z->right);
        y_original_color = y->color;
        x = y->right;
        // y is z's directly child
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    // when y is red, no need to fix.
    if (y_original_color == Black)
    {
        deletefixup(tree, x);
    }

    free(z);
}

/*
    inorder traversal
*/
void inorder(rbtree *tree, treenode *node)
{
    if (node == tree->NIL)
        return;
    inorder(tree, node->left);
    printf("%d(%c) ", node->data, node->color == Red ? 'R' : 'B');
    inorder(tree, node->right);
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
    inorder(tree, tree->root);
    printf("\n");

    printf("===== delete =====\n");
    printf("delete 10\n");
    delete(tree, 10);
    printf("tree root: %d\n", tree->root->data);
    printf("inorder traversal:\n");
    inorder(tree, tree->root);
    printf("\n");

    printf("delete 26\n");
    delete(tree, 26);
    printf("tree root: %d\n", tree->root->data);
    printf("inorder traversal:\n");
    inorder(tree, tree->root);
    printf("\n");

    printf("delete 25\n");
    delete(tree, 25);
    printf("tree root: %d\n", tree->root->data);
    printf("inorder traversal:\n");
    inorder(tree, tree->root);
    printf("\n");

    printf("delete 11\n");
    delete(tree, 11);
    printf("tree root: %d\n", tree->root->data);
    printf("inorder traversal:\n");
    inorder(tree, tree->root);
    printf("\n");
    return 0;
}