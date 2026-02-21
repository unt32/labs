#include <stdio.h>
#include <stdlib.h>

struct arr {
	int* data;
	size_t size;
	size_t cap;
};

void init(struct arr* a) {
	a->data = calloc(1, sizeof(int));
	a->size = 1;
	a->cap = 1;
};

size_t size(struct arr* a) {
	return a->size;
}

size_t empty(struct arr* a) {
	return !size(a);
}

void pop_back(struct arr* a) {
	if(empty(a)) {
		printf("AAA\n");
		return;
	}
	a->size--;
}

void swap(struct arr* a, struct arr* b) {
	struct arr t;
	t.data = a->data;
	t.size = a->size;
	t.cap = a->cap;

	a->data = b->data;
	a->size = b->size;
	a->cap = b->cap;

	b->data = t.data;
	b->size = t.size;
	b->cap = t.cap;
};

void main() {
	struct arr a, b;
	init(&a);
	init(&b);
	a.data[0] = 0;
	b.data[0] = -10;
	printf("%d\t%d\n", a.data[0], b.data[0]);
	swap(&a, &b);
	printf("%d\t%d\n", a.data[0], b.data[0]);
}
