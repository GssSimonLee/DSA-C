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
    // find parent, y, t2
    treenode *y = x->left;
    treenode *t2 = y->right;
    treenode *p = x->parent;

    // parent <-> y
    y->parent = p;
    if (p != NULL) {
        if (p->left == x) {
            p->left = y;
        } else {
            p->right = y;
        }
    }

    // y <-> x
    y->right = x;
    x->parent = y;

    // x <-> t2
    x->left = t2;
    if (t2 != NULL) {
        t2->parent = x;
    }
    
    return y;
}

treenode *leftrotate(treenode *y)
{
    // find parent, x, t2
    treenode *x = y->right;
    treenode *t2 = x->left;
    treenode *p = y->parent;

    // parent <-> x
    x->parent = p;
    if (p != NULL) {
        if (p->left == y) {
            p->left = x;
        } else {
            p->right = x;
        }
    }

    // x <-> y
    x->left = y;
    y->parent = x;

    // y <-> t2
    y->right = t2;
    if (t2 != NULL) {
        t2->parent = y;
    }

    return x;
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
treenode *insertfixup(treenode *root, treenode *z)
{
    // skip case 0, 1
    while (z != root && z->parent->color == Red)
    {
        /*
         divide to two part
                 G         G
                /   and     \
               P             P
         (left child)  (right child)
        */
        treenode *uncle, *parent, *grandparent;
        parent = z->parent;
        grandparent = parent->parent;
        // left child
        if (parent == grandparent->left)
        {
            uncle = grandparent->right;
            if (uncle != NULL && uncle->color == Red)
            {
                parent->color = uncle->color = Black;
                grandparent->color = Red;
                z = grandparent;
            }
            else
            {
                if (z == parent->right)
                {
                    /*
                       G
                      /
                     P
                      \
                       Z
                     swap Z and P
                    */
                    treenode *tmp = z;
                    z = parent;
                    parent = tmp;
                    grandparent->left = leftrotate(z);
                }
                grandparent->color = Red;
                parent->color = Black;
                treenode *grandgrandparent = grandparent->parent;
                if (grandgrandparent != NULL)
                {
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
        }
        else
        { // right child
            uncle = grandparent->left;
            if (uncle != NULL && uncle->color == Red)
            {
                parent->color = uncle->color = Black;
                grandparent->color = Red;
                z = grandparent;
            }
            else
            {
                if (z == parent->left)
                {
                    /*
                       G
                        \
                         P
                        /
                       Z
                     swap Z and P
                    */
                    treenode *tmp = z;
                    z = parent;
                    parent = tmp;
                    grandparent->right = rightrotate(z);
                }
                grandparent->color = Red;
                parent->color = Black;
                treenode *grandgrandparent = grandparent->parent;
                if (grandgrandparent != NULL)
                {
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
    }
    // case 1 -> do nothing
    // case 0 -> recolor root
    root->color = Black;
    return root;
}

treenode *insert(treenode *root, int data)
{
    if (root == NULL)
    {
        treenode *newnode = createnode(data);
        newnode->color = Black;
        return newnode;
    }
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
    root = insertfixup(root, newnode);
    return root;
}

treenode *search(treenode *root, int target) {
    if (root == NULL) {
        return NULL;
    }

    if (root->data == target) return root;
    if (target > root->data) return search(root->right, target);
    // target < root->data
    return search(root->left, target);
}

treenode *findsuccessor(treenode *node) {
    treenode *curr = node;
    whilde (curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

treenode *deletefixup(treenode *root, treenode *Z) {
    return root;
}

treenode *delete(treenode *root, int target) {
    if (root == NULL) {
        printf("target: %d not found.", target);
        return NULL;
    }
    /*
        target(int): the target value user want to delete
        targetnode(treenode*): pointer point to the node value equals to target
        node2delete(treenode*): pointer point to the node that will be delete and free memory
        x(treenode*): pointer point to the node that will replace node2delete (could be nil)
    */
    // step 1, find targetnode, node2delete, x
    treenode *targetnode = NULL, *node2delete = NULL, *x = NULL;
    targetnode = search(root, target);
    // targetnode has zero or one child node
    if (targetnode->right == NULL || targetnode->left == NULL) {
        node2delete = targetnode;
    } else { // target node has two children node
        node2delete = findsuccessor(targetnode->right);
    }
    Color node2deletecolor = node2delete->color;

    if (node2delete->left != NULL) {
        x = node2delete->left;
    } else {
        x = node2delete->right;
    }

    // step 2. delete node2delete and fix pointers (bst delete)
    // parent <-> x
    if (node2delete->parent != NULL) { // node2delete is not root
        if (x != NULL) {
            x->parent = node2delete->parent;
        }
        if (node2delete == node2delete->parent->left) { // is left child
            node2delete->parent->left = x;
        } else { // is right child
            node2delete->parent->right = x;
        }
    }

    // targetnode has 2 children nodes
    if (node2delete != targetnode) {
        targetnode->data = node2delete->data;
        free(node2delete);
    }

    if (node2deletecolor == Black) {
        deletefixup(root, x);
    }

    /*
    target == root->data
    0, 1, 2 child(children)
    there are 2 approaches in BST deletion
    step 1
        1. find inorder successor(minimum) of right subtree
        2. find inorder precessor(maximum) of left subtree
    step 2
        replace current node's value with successor/precessor's value
    step 3
        do futher deletion recursively
    */
}

void inorder(treenode *node)
{
    if (node == NULL)
        return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

int main()
{
    treenode *tree = NULL;
    tree = insert(tree, 25);
    tree = insert(tree, 28);
    tree = insert(tree, 20);
    tree = insert(tree, 26);
    tree = insert(tree, 11);
    tree = insert(tree, 2);
    tree = insert(tree, 9);
    tree = insert(tree, 7);
    tree = insert(tree, 10);
    tree = insert(tree, -10);
    tree = insert(tree, -30);
    tree = insert(tree, -15);
    printf("inorder traversal:\n");
    inorder(tree);
    printf("\n");
    return 0;
}