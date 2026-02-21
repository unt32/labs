#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct node {
	int data;
	struct node* prev;
	struct node* next;
} node;

typedef struct list {
	node* first;
	node* last;
} list;

void list_init(list* s) {
	s->first = NULL;
	s->last = NULL;
}

bool list_empty(list *s) {
	return s->first == NULL;
}


int list_size(list *s) {
	int i = 0;
	for(node* t = s->first; t != NULL; t = t->next)
		i++;
	return i;
}

void print_list(list *s) {
	printf("\n\n\n");
	for(node* t = s->first; t != NULL; t = t->next)
		printf("n = %14p; prev = %14p; next = %14p; data = %3d\n", t, t->prev, t->next, t->data);
	printf("size = %d;\tempty = %d\n\n\n", list_size(s), list_empty(s));
}

int front(list* s) {
	assert(!list_empty(s));
	return s->first->data;
}

int back(list* s) {
	assert(!list_empty(s));
	return s->last->data;
}

void push_front(list* s, int v) {
	node* t = malloc(sizeof(node));
	assert(t != NULL);

	t->data = v;
	t->prev = NULL;
	t->next = s->first;

	if(list_empty(s))
		s->last = t;
	else
		s->first->prev = t;
	s->first = t;
}

int pop_front(list* s) {
	assert(!list_empty(s));

	int v = s->first->data;
	node* t = s->first;

	if(s->first == s->last) {
		s->first = NULL;
		s->last = NULL;
	}
	else {
		s->first = s->first->next;
		s->first->prev = NULL;
	}

	free(t);
	return v;
}

void push_back(list* s, int v) {
	if(list_empty(s)) {
		push_front(s, v);
		return;
	}

	node* t = malloc(sizeof(node));
	assert(t != NULL);
	t->data = v;
	t->prev = s->last;
	t->next = NULL;

	s->last->next = t;
	s->last = t;
}

int pop_back(list* s) {
	assert(!list_empty(s));

	if(s->first == s->last)
		return pop_front(s);

	int v = s->last->data;
	node* t = s->last;

	s->last = s->last->prev;
	s->last->next = NULL;

	free(t);

	return v;
}

void clear(list* s) {
	while(!list_empty(s))
		pop_front(s);
}

void fill(list* s, int len) {
	clear(s);

	while(len-- > 0)
		push_front(s, 0);
}
