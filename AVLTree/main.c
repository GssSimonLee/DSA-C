#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct treenode {
  int value;
  struct treenode *left;
  struct treenode *right;
  int height;
} treenode;

int getmax(int a, int b) {
  return a > b ? a : b;
}

int getheight(treenode *node) {
  if (node == NULL) return 0;
  return node->height;
}

treenode *createnode(int value) {
  treenode* newnode = (treenode*)malloc(sizeof(treenode));
  if (newnode != NULL) {
    newnode->value = value;
    newnode->left = newnode->right = NULL;
    newnode->height = 1; // height of leaf node
  }
  return newnode;
}

// balance factor = height of left child node - height of right child node
int getbalancefactor(treenode *node) {
  if (node == NULL) return 0;
  return getheight(node->left) - getheight(node->right);
}

/*
       x               y
      / \   right     / \
     y  T3   ===>    T1  x
    / \     rotate      / \
   T1  T2    on x      T2  T3

2 pointers change
before: x (left child) -> y, y (right child) -> T2
after: y (right child) -> x, x (left-child) -> T2
*/
treenode *rightrotate(treenode* x) {
  // find y
  treenode *y = x->left;
  // find T2
  treenode *t2 = y->right;

  // make the pointer change
  y->right = x;
  x->left = t2;

  // recalculate the hight of x and y
  // the order of recalculate height matter
  // count the lower node first
  x->height = getmax(getheight(x->left), getheight(x->right)) + 1;
  y->height = getmax(getheight(y->left), getheight(y->right)) + 1;
  return y;
}

/*
       x               y
      / \    left     / \
     y  T3   <===    T1  x
    / \     rotate      / \
   T1  T2    on y      T2  T3

2 pointers change
before: y (right child) -> x, x (left-child) -> T2
after: x (left child) -> y, y (right child) -> T2
*/
treenode *leftrotate(treenode* y) {
  // find x
  treenode *x = y->right;
  // find T2
  treenode *t2 = x->left;

  // make the pointer change
  x->left = y;
  y->right = t2;

  // recalculate the hight of x and y
  // the order of recalculate height matter
  // count the lower node first
  y->height = getmax(getheight(y->left), getheight(y->right)) + 1;
  x->height = getmax(getheight(x->left), getheight(x->right)) + 1;
  return x;
}

treenode *insert(treenode *root, int value) {
  // ==== normal bst insertion start ====
  if (root == NULL) return createnode(value);

  if (value < root->value) {
    root->left = insert(root->left, value);
  } else if(value > root->value) {
    root->right = insert(root->right, value);
  } else {
    // conflict not allowed
    return root;
  }

  // ==== normal bst insertion end ====
  root->height = 1 + getmax(getheight(root->left), getheight(root->right));

  // AVL tree property: palance facter should be {-1, 0, 1}
  // if not, the tree is imbalance, need to do coresponding rotation
  int balancefactor = getbalancefactor(root);

  // the tree is balance. do nothing
  if (balancefactor == 0 || balancefactor == 1 || balancefactor == -1) return root;

  // the tree is not balance, there are 4 cases need to be deal with
  // Left Heavy
  if (balancefactor > 1) {
    // Left-Left imbalance -> LL rotation
    if (value < root->left->value) {
      // right rotation on root
      return rightrotate(root);
    }
    // Left-Right imbalance -> LR rotation
    if (value > root->left->value) {
      // 1. left rotation on root->left
      root->left = leftrotate(root->left);
      // 2. right rotation on root
      return rightrotate(root);
    }
  }

  // Right Heavy
  if (balancefactor < -1) {
    // Right-Right imbalance -> RR rotation
    if (value > root->right->value) {
      // left rotation on root
      return leftrotate(root);
    }

    // Right-Left imbalance -> RL rotation
    if (value < root->right->value) {
      // 1. right rotation on root->right
      root->right = rightrotate(root->right);
      // 2. left rotation on root
      return leftrotate(root);
    }
  }
  printf("unexpect error!\n");
  return NULL;
}

void inordertraversal(treenode *node) {
  if (node == NULL) return;
  inordertraversal(node->left);
  printf("%d ", node->value);
  inordertraversal(node->right);
}

void levelordertraversal(treenode *root) {
  treenode **queue = (treenode**)malloc(sizeof(treenode*) * 10);
  int front = 0, rear = 0;

  queue[rear++] = root;
  while (front < rear) {
    treenode *curr = queue[front++];

    printf("%d ", curr->value);

    if (curr->left != NULL) {
      queue[rear++] = curr->left;
    }

    if (curr->right != NULL) {
      queue[rear++] = curr->right;
    }
  }
  free(queue);
}

int main(int argc, char** argv) {
  treenode *tree = NULL;
  printf("insert 13\n");
  tree = insert(tree, 13);
  printf("insert 10\n");
  tree = insert(tree, 10);
  printf("insert 8\n");
  tree = insert(tree, 8);
  printf("insert 2\n");
  tree = insert(tree, 2);
  printf("insert 20\n");
  tree = insert(tree, 20);
  printf("insert 15\n");
  tree = insert(tree, 15);
  printf("insert 32\n");
  tree = insert(tree, 32);
  printf("insert 17\n");
  tree = insert(tree, 17);
  printf("insert 19\n");
  tree = insert(tree, 19);
  printf("insert 9\n");
  tree = insert(tree, 9);

  printf("inorder traversal:\n");
  inordertraversal(tree);

  printf("\n");
  printf("level traversal:\n");
  levelordertraversal(tree);
  return 0;
}