#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUEUE_MAX_SIZE 10
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

bool insert(treenode **rootptr, int value) {
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
        return insert(&(root->left), value);
    }

    return insert(&(root->right), value);
}

treenode *insertiterative(treenode *root, int data) {
    treenode *curr = root, *prev = NULL;
    while (curr != NULL) {
        prev = curr;
        if (data == curr->value) {
            // conflict
        } else if (data > curr->value) {
            curr = curr->right;
        } else { // data < curr->value
            curr = curr->left;
        }
    }
    if (data > prev->value) {
        prev->right = createnode(data);
    } else if (data < prev->value) {
        prev->left = createnode(data);
    }
    return root;
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
    // if (root->left == NULL && root->right == NULL) {
    //     free(root);
    //     return root = NULL;
    // }

    // case 2. one child (combine no child with this condition as well)
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
    // find minimum of right subtree approaches
    treenode *min, *curr;
    curr = root->right;
    while (curr != NULL) {
        min = curr;
        curr = curr->left;
    }
    root->value = min->value;
    root->right = delete(root->right, min->value);
    return root;
}

void inordertraversal(treenode *root) {
    if (root == NULL) return;
    inordertraversal(root->left);
    printf("%d ", root->value);
    inordertraversal(root->right);
}

void levelordertraversl(treenode *root) {
    if (root == NULL) return;

    treenode **queue = (treenode**)malloc(sizeof(treenode*) * QUEUE_MAX_SIZE);
    int front = 0, rear = 0;

    // enqueue root
    queue[rear++] = root;
    
    while (front < rear) {
        treenode *current = queue[front++];

        printf("%d ", current->value);

        if (current->left != NULL) {
            // enqueue left child
            queue[rear++] = current->left;
        }

        if (current->right != NULL) {
            // enqueue right child
            queue[rear++] = current->right;
        }
    }
    
    free(queue);
}

void preordertraversaliterative(treenode *root) {
    if (root == NULL) {
        return;
    }
    int top = -1, STACK_SIZE = 10;
    treenode **stack = (treenode**)malloc(sizeof(treenode*) * STACK_SIZE);
    // push
    stack[++top] = root;
    while (top != -1) {
        treenode *curr = stack[top--];
        printf("%d ", curr->value);
        if (curr->right != NULL) {
            stack[++top] = curr->right;
        }
        if (curr->left != NULL) {
            stack[++top] = curr->left;
        }
    }
}

int main(int argc, char** argv) {
    treenode *root = NULL;
    insert(&root, 13);
    insert(&root, 8);
    insert(&root, 20);
    insert(&root, 2);
    insert(&root, 15);
    insert(&root, 32);
    insert(&root, 17);
    insert(&root, 19);
    insert(&root, 10);
    insert(&root, 9);

    printf("Tree: \n");

    printf("inorder traversal\n");
    inordertraversal(root);
    printf("\n");

    printf("level traversal\n");
    levelordertraversl(root);

    printf("\n");
    printf("iteratively preorder traversal:\n");
    preordertraversaliterative(root);

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

    printf("insert 7 iteratively\n");
    root = insertiterative(root , 7);
    printf("inorder traversal\n");
    inordertraversal(root);
    printf("\n");

    return 0;
}
