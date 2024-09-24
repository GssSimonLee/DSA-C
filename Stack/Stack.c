#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define STACK_SIZE 10

typedef struct stack
{
  int top;
  int data[STACK_SIZE];
} stack;

bool isEmpty(stack *s)
{
  return s->top == -1;
}

bool isFull(stack *s)
{
  return s->top == STACK_SIZE - 1;
}

stack *createstack()
{
  stack *s = (stack *)malloc(sizeof(stack));
  if (s != NULL)
  {
    s->top = -1;
  }
  return s;
}

void push(stack *s, int value)
{
  if (isFull(s))
  {
    printf("stack is full, cannot push\n");
    return;
  }

  s->data[++s->top] = value;
}

int peek(stack *s)
{
  if (isEmpty(s))
  {
    printf("stack is empty!\n");
    return -1;
  }
  return s->data[s->top];
}

int pop(stack *s)
{
  if (isEmpty(s))
  {
    printf("stack is empty!\n");
    return -1;
  }
  return s->data[s->top--];
}

int main(int argc, char **argv)
{
  int p = -1;
  int out = -1;
  stack *s = createstack();
  p = peek(s);

  printf("push 3 into stack\n");
  push(s, 3);
  printf("push 5 into stack\n");
  push(s, 5);
  p = peek(s);
  printf("peek stack %d\n", p);

  out = pop(s);
  printf("pop stack %d\n", out);

  p = peek(s);
  printf("peek stack %d\n", p);

  free(s);
  return 0;
}