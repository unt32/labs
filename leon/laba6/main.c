#include <stdio.h>

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void heapify(int a[], int n, int i) {
	int best = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && a[left] > a[best]) best = left;
	if (right < n && a[right] > a[best]) best = right;

	if (best == i) return;

	swap(&a[i], &a[best]);
	heapify(a, n, best);
}

void heap_sort(int a[], int n) {
	if (n <= 1) return;

	for (int i = (n - 1) / 2; i >= 0; --i) {
		heapify(a, n, i);
	}

	for (int end = n - 1; end > 0; --end) {
		swap(&a[0], &a[end]);
		heapify(a, end, 0);
	}
}

int main(void) {
	int a[] = {12, 11, 13, 5, 34, 7, 1, -5, 19, 3, 6};
	int n = (int)(sizeof(a) / sizeof(a[0]));

	for (int i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");

	heap_sort(a, n);

	for (int i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}
