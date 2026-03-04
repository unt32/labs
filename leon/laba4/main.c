#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node {
	int x;
	struct node *a;
	struct node *b;
} node;

node* mknode(int v) {
	node* t = malloc(sizeof(node));
	assert(t);

	t->x = v;
	t->a = NULL;
	t->b = NULL;

	return t;
}

void clear(node* r) {
	if(!r)
		return;

	clear(r->a);
	clear(r->b);

	free(r);
}

node* insert(node* r, node *n) {
	if(!r)
		return n;

	if(r == n)
		return r;

	if(n->a) {
		r = insert(r, n->a);
		n->a = NULL;
	}

	if(n->b) {
		r = insert(r, n->b);
		n->b = NULL;
	}

	if(r->x ==  n->x) {
		clear(n);
		return r;
	}

	if(r->x > n->x)
		r->a = insert(r->a, n);
	else
		r->b = insert(r->b, n);

	return r;
}

int height(node* r) {
	if(!r)
		return 0;

	int a = height(r->a);
	int b = height(r->b);
	if(a < b)
		a = b;

	return 1 + a;
}

node* find(node* r, int v) {
	if(!r)
		return NULL;

	if(r->x == v)
		return r;


	if(r->x > v)
		return find(r->a, v);
	else
		return find(r->b, v);
}

void print(node* r) {
	if(!r)
		return;

	print(r->a);
	printf("%d ", r->x);
	print(r->b);
}


int main(void) {

	node* root = NULL;

	root = insert(root, mknode(-50));
	root = insert(root, mknode(50));
	root = insert(root, mknode(1));
	root = insert(root, mknode(10));
	root = insert(root, mknode(8));
	root = insert(root, mknode(0));
	root = insert(root, mknode(9));
	root = insert(root, mknode(100));
	root = insert(root, mknode(13));


	print(root);
	printf("\n");
}
