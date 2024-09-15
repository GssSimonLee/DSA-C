#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define QUEUE_SIZE 10

typedef struct treenode {
  struct treenode *left, *right;
  int data;
} treenode;

treenode *createnode(int data) {
  treenode *n = (treenode*)malloc(sizeof(treenode));
  if (n != NULL) {
    n->left = n->right = NULL;
    n->data = data;
  }
  return n;
}

typedef struct queue {
  int front, rear;
  struct treenode *data[QUEUE_SIZE];
} queue;

bool isEmpty(queue *q) {
  return q->front == -1;
}

bool isFull(queue *q) {
  return q->front == (q->rear + 1) % QUEUE_SIZE;
}

queue *createqueue() {
  queue *q = (queue*)malloc(sizeof(queue));
  if (q != NULL) {
    q->front = q->rear = -1;
  }
  return q;
}

treenode *dequeue(queue *q) {
  if (isEmpty(q)) {
    printf("dequeue fail, queue is empty\n");
    return NULL;
  }
  treenode *p = q->data[q->front];
  if (q->front == q->rear) {
    q->front = q->rear = -1;
  } else {
    q->front = (q->front + 1) % QUEUE_SIZE;
  }
  return p;
}

void enqueue(queue *q, treenode *node) {
  if (isFull(q)) {
    printf("enqueue %d fail, queue is full\n", node->data);
    return;
  }
  if (q->front == -1) q->front = 0;
  q->rear = (q->rear + 1) % QUEUE_SIZE;
  q->data[q->rear] = node;
}

void levelorder(treenode *root) {
  if (root == NULL) return;

  queue *q = createqueue();
  enqueue(q, root);

  while (!isEmpty(q)) {
    treenode *curr = dequeue(q);
    printf("%d ", curr->data);
    if (curr->left != NULL) enqueue(q, curr->left);
    if (curr->right != NULL) enqueue(q, curr->right);
  }
}

int main() {
  treenode *root = createnode(2);
  root->left = createnode(1);
  root->right = createnode(4);
  root->right->left = createnode(3);
  root->right->right = createnode(5);

  printf("level order traversal\n");
  levelorder(root);
  printf("\n");
  return 0;
}