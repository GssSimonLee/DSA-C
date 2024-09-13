#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUEUE_SIZE 10

typedef struct queue {
  int front;
  int rear;
  int data[QUEUE_SIZE];
} queue;

queue *createqueue() {
  queue *q = (queue*)malloc(sizeof(queue));
  if (q != NULL) {
    q->front = q->rear = -1;
  }
  return q;
}

bool isEmpty(queue *q) {
  return q->front == -1;
}

bool isFull(queue *q) {
  return q->front == (q->rear + 1) % QUEUE_SIZE;
}

/*
  enqueue from rear (rear should + 1)
  careful the edge case: front == -1
*/
void enqueue(queue *q, int data) {
  if (isFull(q)) {
    printf("queue is full\n");
    return;
  }

  if (q->front == -1) {
    q->front = 0;
  }
  q->rear = (q->rear + 1) % QUEUE_SIZE;
  q->data[q->rear] = data;
}

/*
  dequeue from front (front should + 1)
  1. keep the value
  2. check if queueu is empty after dequeue
  3. if yes reset the queue
  4. return the kept value
*/
int dequeue(queue *q) {
  if (isEmpty(q)) {
    printf("queue is empty\n");
    return -1;
  }
  int output = q->data[q->front];
  // after dequeue the last element, reset queue
  if (q->front == q->rear) {
    q->front = q->rear = -1;
  } else {
    // queue is not empty yet
    q->front = (q->front + 1) % QUEUE_SIZE;
  }
  return output;
}

int main(int argc, char** argv) {
  int output = -1;
  queue *q = createqueue();
  printf("dequeue:\n");
  output = dequeue(q);
  printf("output: %d\n", output);

  printf("enqueue 3\n");
  enqueue(q, 3);
  printf("\n");

  printf("enqueue 7\n");
  enqueue(q, 7);
  printf("\n");

  printf("enqueue 8\n");
  enqueue(q, 8);
  printf("\n");

  printf("dequeue:\n");
  output = dequeue(q);
  printf("output: %d\n", output);
  
  printf("dequeue:\n");
  output = dequeue(q);
  printf("output: %d\n", output);

  printf("dequeue:\n");
  output = dequeue(q);
  printf("output: %d\n", output);

  return 0;
}