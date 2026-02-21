#include <stdio.h>
#include <stdbool.h>
#include "../laba2/list.h"

typedef struct stack {
	list d;
} stack;

void init(stack* s) {
	list_init(&(s->d));
};

void push(stack* s, int v) {
	push_front(&(s->d), v);
}

int pop(stack* s) {
	return pop_front(&(s->d));
}

int top(stack* s) {
	return front(&(s->d));
}

int size(stack* s) {
	return list_size(&(s->d));
}

bool empty(stack* s) {
	return list_empty(&(s->d));
}

int main(void) {
	stack s;
	init(&s);

	for (size_t i = 0; i < 5; i++) push(&s, i);
	for (; !empty(&s); pop(&s)) printf("%d ", top(&s));
	// 4 3 2 1 0
	printf("\n\n");
}
