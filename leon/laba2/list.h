#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct node node;

typedef struct list {
    node* first;
    node* last;
} list;

void list_init(list* s);

bool list_empty(list* s);
int list_size(list* s);

int front(list* s);
int back(list* s);

void push_front(list* s, int v);
void push_back(list* s, int v);

int pop_front(list* s);
int pop_back(list* s);

void clear(list* s);
void fill(list* s, int len);

void print_list(list* s);

#endif
