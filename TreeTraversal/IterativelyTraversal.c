#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define STACK_SIZE 10

typedef struct treenode {
  struct treenode *left, *right;
  int data;
} treenode;

treenode *createnode(int data) {
  treenode *node = (treenode*)malloc(sizeof(treenode));
  if (node != NULL) {
    node->data = data;
    node->left = node->right = NULL;
  }
  return node;
}

treenode *insert(treenode *node, int data) {
  if (node == NULL) return createnode(data);
  if (data == node->data) printf("insert fail, conflict\n");
  if (data > node->data) node->right = insert(node->right, data);
  if (data < node->data) node->left = insert(node->left, data);
  return node;
}

typedef struct stack {
  struct treenode *data[STACK_SIZE];
  int top;
} stack;

stack *createstack() {
  stack *s = (stack*)malloc(sizeof(stack));
  if (s != NULL) {
    s->top = -1;
  }
  return s;
}

bool isFull(stack *s) {
  return s->top == STACK_SIZE - 1;
}

bool isEmpty(stack *s) {
  return s->top == -1;
}

void push(stack *s, treenode *node) {
  if (isFull(s)) {
    printf("push %d fail, stack is full\n", node->data);
    return;
  }
  s->data[++s->top] = node;
}

treenode *pop(stack *s) {
  if (isEmpty(s)) {
    printf("pop fail, stack is empty\n");
    return NULL;
  }
  return s->data[s->top--];
}

treenode *peek(stack *s) {
  if (isEmpty(s)) {
    printf("peek fail, stack is empty\n");
    return NULL;
  }
  return s->data[s->top];
}

void preorder(treenode *node) {
  stack *s = createstack();
  push(s, node);

  while (!isEmpty(s)) {
    treenode *curr = pop(s);
    printf("%d ", curr->data);
    if (curr->right != NULL) push(s, curr->right);
    if (curr->left != NULL) push(s, curr->left);
  }
}

void inorder(treenode *node) {
  stack *s = createstack();
  treenode *curr = node;
  while (curr != NULL || !isEmpty(s)) {
    if (curr != NULL) {
      push(s, curr);
      curr = curr->left;
    } else {
      treenode *p = pop(s);
      printf("%d ", p->data);
      curr = p->right;
    }
  }
}

// two stack
void postorder1(treenode *node) {
  stack *processstack = createstack();
  stack *resultstack = createstack();
  push(processstack, node);

  while (!isEmpty(processstack)) {
    treenode *p = pop(processstack);
    push(resultstack, p);
    if (p->left != NULL) push(processstack, p->left);
    if (p->right != NULL) push(processstack, p->right);
  }

  while (!isEmpty(resultstack)) {
    treenode *p = pop(resultstack);
    printf("%d ", p->data);
  }
}

void postorder2(treenode *node) {
  bool visited[10] = {0};
  int top = 0;
  stack *s = createstack();
  push(s,  node);
  visited[0] = false;

  while (!isEmpty(s)) {
    treenode *curr = pop(s);
    bool v = visited[top--];
    if (v) {
      printf("%d ", curr->data);
    } else {
      push(s, curr);
      visited[++top] = true;
      if (curr->right != NULL) {
        push(s, curr->right);
        visited[++top] = false;
      }
      if (curr->left != NULL) {
        push(s, curr->left);
        visited[++top] = false;
      }
    }
  }
}

void postorder3(treenode *node) {
  stack *s = createstack();
  treenode *curr = node;
  while (curr != NULL || !isEmpty(s)) {
    if (curr != NULL) {
      // push right first if right exist
      if (curr->right != NULL){
        push(s, curr->right);
      }
      push(s, curr);
      curr = curr->left;
    } else {
      curr = pop(s);
      // check if curr-right == peek(s)
      // if true change order
      if (!isEmpty(s) && curr->right != NULL && curr->right->data == peek(s)->data) {
        pop(s);
        push(s, curr);
        curr = curr->right;
      } else {
        printf("%d ", curr->data);
        curr = NULL;
      }
    }
  }
}

int main() {
  treenode *root = createnode(2);
  root = insert(root, 4);
  root = insert(root, 3);
  root = insert(root, 1);
  root = insert(root, 5);

  printf("preorder\n");
  preorder(root);
  printf("\n");

  printf("inorder\n");
  inorder(root);
  printf("\n");

  printf("postorder1\n");
  postorder1(root);
  printf("\n");

  printf("postorder2\n");
  postorder2(root);
  printf("\n");

  printf("postorder3\n");
  postorder3(root);
  printf("\n");

  return 0;
}