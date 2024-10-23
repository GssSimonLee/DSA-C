#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BST.h"

bool breadthfirstsearch(bst *t, int target) {
    if (t->root == NULL) {
        return false;
    }

    node *queue[20];
    int front = 0;
    int rear = 0;

    queue[rear++] = t->root;

    while (front < rear) {
        node *curr = queue[front++];
        if (curr->data == target) return true;

        if (curr->left != NULL) {
            queue[rear++] = curr->left;
        }

        if (curr->right != NULL) {
            queue[rear++] = curr->right;
        }
    }
    return false;
}

int main() {
    bst *t = createtree();
    insert(t, 20);
    insert(t, 4);
    insert(t, 18);
    insert(t, 24);
    insert(t, 13);
    insert(t, 8);

    bool e = breadthfirstsearch(t, 18);
    if (e) {
        printf("18 exist");
    } else {
        printf("18 not exist");
    }
    return 0;
}