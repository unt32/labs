#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../laba2/list.h"

#define NEG   1
#define POS   2
#define MULT  3
#define DIV   4
#define OP    5
#define CL    6

#define NUM   0
#define OPR 1

int prec(int op) {
	if(op == MULT || op == DIV)
		return 2;

	if (op == POS || op == NEG)
		return 1;
	return 0;
}

bool operator(int t) {
	return t == POS || t == NEG || t == MULT || t == DIV;
}

int ct(char c) {
	switch(c) {
	case '+':
		return POS;
	case '-':
		return NEG;
	case '*':
		return MULT;
	case '/':
		return DIV;
	case '(':
		return OP;
	case ')':
		return CL;
	default:
		return 0;
	}
}

void shunt(const char *expr, list *out, list *ind) {
	list st;
	list_init(&st);

	for (int i = 0; expr[i]; i++) {
		if (isdigit(expr[i])) {
			int num = 0;
			while (isdigit(expr[i]))
				num = num * 10 + (expr[i++] - '0');
			push_back(out, num);
			push_back(ind, NUM);
			i--;
			continue;
		}

		int t = ct(expr[i]);

		if (operator(t)) {
			while (!list_empty(&st) && operator(back(&st)) && prec(back(&st)) >= prec(t)) {
				push_back(out, pop_back(&st));
				push_back(ind, OPR);
			}
			push_back(&st, t);
		}
		else if (t == OP) {
			push_back(&st, t);
		}
		else {
			while (!list_empty(&st) && back(&st) != OP) {
				push_back(out, pop_back(&st));
				push_back(ind, OPR);
			}
			if (!list_empty(&st))
				pop_back(&st);
		}
	}

	while (!list_empty(&st)) {
		push_back(out, pop_back(&st));
		push_back(ind, OPR);
	}

	clear(&st);
}

int eval(list *out, list *ind) {
	list st;
	list_init(&st);

	while (!list_empty(out)) {
		int val = pop_front(out);
		int typ = pop_front(ind);

		if (typ == NUM) {
			push_back(&st, val);
		} else {
			int b = pop_back(&st);
			int a = pop_back(&st);
			int res;

			switch(val) {
			case POS:
				res = a + b;
				break;
			case NEG:
				res = a - b;
				break;
			case MULT:
				res = a * b;
				break;
			case DIV:
				res = a / b;
				break;
			default:
				res = 0;
			}
			push_back(&st, res);
		}
	}

	int res = pop_back(&st);
	clear(&st);
	return res;
}

int main() {
	list out, ind;
	list_init(&out);
	list_init(&ind);

	char task[100];
	scanf("%99s", task);

	shunt(task, &out, &ind);
	printf("\n\t%d\n", eval(&out, &ind));

	clear(&out);
	clear(&ind);
	return 0;
}
