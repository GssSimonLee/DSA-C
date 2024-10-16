# BinarySearchTree

## Deletion

```c
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
```

In practice, we do not use change value strategy to delete node that has 2 children. It may have lots of properties which changing the pointer is the better approach.