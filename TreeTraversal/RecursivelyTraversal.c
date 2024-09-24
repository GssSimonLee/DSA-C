#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct treenode
{
    struct treenode *left, *right;
    int data;
} treenode;

treenode *createnode(int data)
{
    treenode *n = (treenode *)malloc(sizeof(treenode));
    if (n != NULL)
    {
        n->left = n->right = NULL;
        n->data = data;
    }
    return n;
}

treenode *freetree(treenode *node)
{
    if (node == NULL)
        return NULL;
    if (node->left != NULL)
        return freetree(node->left);
    if (node->right != NULL)
        return freetree(node->right);
    free(node);
    return NULL;
}

treenode *insert(treenode *root, int data)
{
    if (root == NULL)
        return createnode(data);
    if (data == root->data)
    {
        printf("insert %d fail. data conflict!\n", data);
        return root;
    }
    if (data > root->data)
    {
        root->right = insert(root->right, data);
    }
    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    return root;
}

void preorder(treenode *node)
{
    if (node == NULL)
        return;
    printf("%d ", node->data);
    preorder(node->left);
    preorder(node->right);
}

void inorder(treenode *node)
{
    if (node == NULL)
        return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

void postorder(treenode *node)
{
    if (node == NULL)
        return;
    postorder(node->left);
    postorder(node->right);
    printf("%d ", node->data);
}

int main()
{
    /*
         2
        / \
       1   4
          / \
         3   5
    */

    treenode *root = createnode(2);
    root = insert(root, 1);
    root = insert(root, 4);
    root = insert(root, 3);
    root = insert(root, 5);

    printf("preorder\n");
    preorder(root);
    printf("\n");

    printf("inorder\n");
    inorder(root);
    printf("\n");

    printf("postorder\n");
    postorder(root);
    printf("\n");

    return 0;
}