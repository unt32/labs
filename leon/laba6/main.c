#include <stdio.h>

typedef int (*q)(const int, const int);

int ba(const int a, const int b){
	return a < b;
}

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void heapify(int a[], int n, int i, q c) {
	int best = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && c(a[left] , a[best])) best = left;
	if (right < n && c(a[right] , a[best])) best = right;

	if (best == i) return;

	swap(&a[i], &a[best]);
	heapify(a, n, best, c);
}

void heap_sort(int a[], int n, q c) {
	if (n <= 1) return;

	for (int i = (n - 1) / 2; i >= 0; --i) {
		heapify(a, n, i, c);
	}

	for (int end = n - 1; end > 0; --end) {
		swap(&a[0], &a[end]);
		heapify(a, end, 0, c);
	}
}

int main(void) {
	int a[] = {12, 11, 13, 5, 34, 7, 1, -5, 19, 3, 6};
	int n = sizeof(a) / sizeof(a[0]);

	for (int i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");

	heap_sort(a, n, ba);

	for (int i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}
