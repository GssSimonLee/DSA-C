#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct singlelist {
    struct node *head;
} singlelist;

node* createnode(int data) {
    node* newnode = (node*)malloc(sizeof(node));
    if (newnode != NULL) {
        newnode->data = data;
    }
    return newnode;
}

singlelist *createlist(int data) {
    singlelist *list = (singlelist*)malloc(sizeof(singlelist));
    list->head = createnode(data);
    return list;
}

void append(singlelist *list, int data) {
    if (list == NULL) {
        // do nothing
        return ;
    }
    if (list->head == NULL) {
        list->head = createnode(data);
    }
    node *current = list->head;
    while(current->next) {
        current = current->next;
    }
    current->next = createnode(data);
}

void reverselist(singlelist *list) {
    // list not initial, no head node or has only one node
    if (list == NULL || list->head == NULL || list->head->next == NULL) return;
    node *prev = NULL, *curr = list->head, *next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list->head = prev;
}

// linear search
bool findnumber(singlelist *list, int target) {
    if (list == NULL || list->head == NULL) return false;
    node *current = list->head;
    while (current != NULL) {
        if (current->data == target) return true;
        current = current->next;
    }
    return false;
}

void delete(singlelist *list, int target) {
    node *curr = list->head, *prev = NULL;

    if (curr != NULL && curr->data == target) {
        list->head = curr->next;
        free(curr);
        return;
    }

    while (curr != NULL && curr->data != target) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) return;

    prev->next = curr->next;
    free(curr);
}

void printlist(singlelist *list) {
    if (list == NULL || list->head == NULL) return;
    node *current = list->head;
    while(current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(int argc, char** argv) {
    singlelist *list =  createlist(10);
    append(list, 15);
    append(list, 8);
    append(list, 20);
    append(list, 7);

    printlist(list);

    printf("reverse list\n");
    reverselist(list);
    printlist(list);

    printf("findnumber 10, result: %d\n", findnumber(list, 10));
    printf("findnumber 15, result: %d\n", findnumber(list, 15));
    
    // not exist
    printf("delete 11\n");
    delete(list, 11);
    printlist(list);

    // tail
    printf("delete 10\n");
    delete(list, 10);
    printlist(list);
    
    // head
    printf("delete 7\n");
    delete(list, 7);
    printlist(list);

    // middle
    printf("delete 8\n");
    delete(list, 8);
    printlist(list);

    return 0;
}