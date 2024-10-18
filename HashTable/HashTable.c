#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    dealing conflict using separate chaining
*/
typedef struct node {
    const char *key;
    void *value;
    struct node *next;
} node;

typedef struct hashtable {
    int size;
    node **table;
} hashtable;

unsigned int hash(const char *key, int size) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    // simple hash logic
    for (i = 0; i < key_len; i++) {
        value = value * 37 + key[i];
    }

    value = value % size;
    return value;
}

node *createnode(const char *key, void *value) {
    node *n = malloc(sizeof(node));
    n->key = key;
    n->value = value;
    n->next = NULL;
    return n;
}

hashtable *createtable(int size) {
    hashtable *t = (hashtable*)malloc(sizeof(hashtable));
    t->size = size;
    t->table = malloc(sizeof(node*) * size);

    for (int i = 0; i < size; i++) {
        t->table[i] = NULL;
    }
    return t;
}

void insert(hashtable *t, const char *key, void *value) {
    unsigned int index = hash(key, t->size);
    node *n = createnode(key, value);
    // prepend new node in the front of table[index]
    n->next = t->table[index];
    t->table[index] = n;
}

void *search(hashtable *t, const char *key) {
    unsigned int index = hash(key, t->size);
    node *n = t->table[index];
    while (n != NULL) {
        if (strcmp(n->key, key) == 0) {
            return n->value;
        }
        n = n->next;
    }
    return NULL;
}

void delete(hashtable *t, const char *key) {
    unsigned int index = hash(key, t->size);
    node *n = t->table[index];
    node *prev = NULL;
    while (n != NULL) {
        if (strcmp(n->key, key) == 0) {
            t->table[index] = n->next;
        } else {
            prev->next = n->next;
        }
        // free(n->key);
        free(n);
        return;
    }
    prev = n;
    n = n->next;
}

int main() {
    hashtable *t = createtable(10);
    insert(t, "apple", "red");
    insert(t, "orange", "orange");
    insert(t, "banana", "yellow");
    printf("apple: %s\n", (char*)search(t, "apple"));
    delete(t, "apple");
    printf("apple: %s\n", (char*)search(t, "apple"));
    printf("orange: %s\n", (char*)search(t, "orange"));
    return 0;
}