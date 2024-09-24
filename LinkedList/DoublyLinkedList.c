#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    struct node *prev, *next;
    int data;
} node;

typedef struct linkedlist {
    struct node *head;
    int len;
} linkedlist;

node *createnode(int data) {
    node *n = (node*)malloc(sizeof(node));
    if (n != NULL) {
        n->data = data;
        n->next = n->prev = NULL;
    }
    return n;
}

linkedlist *createlist() {
    linkedlist *list = (linkedlist*)malloc(sizeof(linkedlist));
    if (list != NULL) {
        node *dummy = createnode(0);
        dummy->next = dummy->prev = dummy;
        list->head = dummy;
        list->len = 0;
    }
    return list;
}

linkedlist *append(linkedlist *list, int data) {
    node *newnode = createnode(data);
    // last node: list->head->prev
    // first node: list->head
    // append: add and become last node
    newnode->next = list->head;
    newnode->prev = list->head->prev;

    list->head->prev->next = newnode;
    list->head->prev = newnode;
    return list;
}

linkedlist *prepend(linkedlist *list, int data) {
    node *newnode = createnode(data);

    newnode->next = list->head->next;
    newnode->prev = list->head;

    list->head->next->prev = newnode;
    list->head->next = newnode;
    return list;
}

linkedlist *deleteforward(linkedlist *list, int target) {
    node *curr = list->head;
    while (curr->next != list->head) {
        // target found
        if (curr->next->data == target) {
            node *tmp = curr->next;
            curr->next->next->prev = curr;
            curr->next = curr->next->next;
            free(tmp);
            break;
        }
        curr = curr->next;
    }
    return list;
}

linkedlist *deletebackward(linkedlist *list, int target) {
    node *curr = list->head;
    while (curr->prev != list->head) {
        // target found
        if (curr->prev->data == target) {
            node *tmp = curr->prev;
            curr->prev->prev->next = curr;
            curr->prev = curr->prev->prev;
            free(tmp);
            break;
        }
        curr = curr->prev;
    }
    return list;
}
void printforward(linkedlist *list) {
    node *curr = list->head;
    while (curr->next != list->head) {
        printf("%d ", curr->next->data);
        curr = curr->next;
    }
    printf("\n");
}

void printbackward(linkedlist *list) {
    node *curr = list->head;
    while (curr->prev != list->head) {
        printf("%d ", curr->prev->data);
        curr = curr->prev;
    }
    printf("\n");
}

int main() {
    linkedlist *list = createlist();
    list = append(list, 10);
    list = append(list, 34);
    list = append(list, 2);
    list = append(list, 83);

    printf("printforward: ");
    printforward(list);

    printf("printbackward: ");
    printbackward(list);

    list = prepend(list, 3);
    list = prepend(list, 8);

    printf("printforward: ");
    printforward(list);

    printf("printbackward: ");
    printbackward(list);

    printf("delete 10\n");
    list = deleteforward(list, 10);

    printf("printforward: ");
    printforward(list);

    printf("printbackward: ");
    printbackward(list);

    printf("delete 8\n");
    list = deleteforward(list, 8);

    printf("printforward: ");
    printforward(list);

    printf("printbackward: ");
    printbackward(list);

    return 0;
}