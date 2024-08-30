#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct treenode {
    int value;
    struct treenode *left;
    struct treenode *right;
} treenode;

treenode *createnode(int value) {
    treenode* result = (treenode*)malloc(sizeof(treenode));

    if (result != NULL) {
        result->left = result->right = NULL;
        result->value = value;
    }
    return result;
}

treenode *findmin(treenode *root) {
    // empty
    if (root == NULL) return root;
    // no left child
    if (root->left == NULL) return root;
    return findmin(root->left);
}

bool insertnumber(treenode **rootptr, int value) {
    treenode *root = *rootptr;

    if (root == NULL) {
        // tree empty
        (*rootptr) = createnode(value);
        return true;
    }

    if (value == root->value) {
        // do nothing
        // the value already exist in the tree
        return false;
    }

    if (value < root->value) {
        return insertnumber(&(root->left), value);
    }

    return insertnumber(&(root->right), value);
}

bool findnumber(treenode *node, int value) {
    // the tree is empty
    if (node == NULL) return false;

    if (node->value == value) return true;

    if (value < node->value) {
        return findnumber(node->left, value);
    } else {
        return findnumber(node->right, value);
    }
}

treenode *delete(treenode *root, int target) {
    if (root == NULL) return root;
    // keep finding in left sub tree
    if (target < root->value) {
        root->left = delete(root->left, target);
        return root;
    }
    // keep finding in right sub tree
    if (target > root->value) {
        root->right = delete(root->right, target);
        return root;
    }

    // root->value == target
    // case 1. no child
    if (root->left == NULL && root->right == NULL) {
        free(root);
        return root = NULL;
    }

    // case 2. one child
    if (root->left == NULL) {
        treenode *temp = root;
        root = root->right;
        free(temp);
        return root;
    }

    if (root->right == NULL) {
        treenode *temp = root;
        root = root->left;
        free(temp);
        return root;
    }

    // case 3. two children
    // there two approaches: 1. find maximum of left subtree and swap 2. find minimum of right subtree and swap
    // find minmum of right subtree approaches
    treenode *min = findmin(root->right);
    root->value = min->value;
    root->right = delete(root->right, min->value);
    return root;
}

void inordertraversal(treenode *root) {
    if (root == NULL) return;
    if (root->left != NULL) inordertraversal(root->left);
    printf("%d ", root->value);
    if (root->right != NULL) inordertraversal(root->right);
}

int main(int argc, char** argv) {
    treenode *root = NULL;
    insertnumber(&root, 13);
    insertnumber(&root, 8);
    insertnumber(&root, 20);
    insertnumber(&root, 2);
    insertnumber(&root, 15);
    insertnumber(&root, 32);
    insertnumber(&root, 17);
    insertnumber(&root, 19);
    insertnumber(&root, 10);
    insertnumber(&root, 9);

    printf("Tree: \n");

    printf("inorder traversal\n");
    inordertraversal(root);

    printf("\n");

    printf("findnumber: 10, found(0/1): %d.\n", findnumber(root, 10));
    printf("findnumber: 17, found(0/1): %d.\n", findnumber(root, 17));
    printf("findnumber: 3, found(0/1): %d.\n", findnumber(root, 3));

    printf("delete number: 10\n");
    delete(root, 10);

    printf("findnumber: 10, found(0/1): %d.\n", findnumber(root, 10));
    printf("findnumber: 17, found(0/1): %d.\n", findnumber(root, 17));
    printf("inorder traversal\n");
    inordertraversal(root);

    printf("delete number: 4\n");
    delete(root, 4);

    printf("findnumber: 10, found(0/1): %d.\n", findnumber(root, 10));
    printf("findnumber: 17, found(0/1): %d.\n", findnumber(root, 17));
    printf("findnumber: 4, found(0/1): %d.\n", findnumber(root, 4));
    printf("inorder traversal\n");
    inordertraversal(root);
    printf("\n");
    return 0;
}
