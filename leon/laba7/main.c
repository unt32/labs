#include <stdio.h>

static void pref(const char* s, int* m, const int n) {
	m[0] = 0;
	for(int i = 1; i < n; i++) {
		int j = m[i - 1];

		while (j > 0 && s[i] != s[j])
			j = m[j-1];

		if (s[i] == s[j])
			++j;

		m[i] = j;
	}
};

int search(const char *s, const int n, const char *sub, const int sn) {
	int len = n + sn + 1;
	char a[len];
	for(int i = 0; i < sn; i++)
		a[i] = sub[i];
	for(int i = 0; i < n; i++)
		a[sn+i+1] = s[i];
	a[sn] = '#';

	int m[len];
	pref(a, m, len);

	for(int i = 0; i < len; i++)
		if(m[i] == sn)
			return i - 2*sn;
	return -1;
}

int main(void) {
	char s[] = "ABABABCABABC";
	char sub[] = "ABABC";
	int n = sizeof(s) / sizeof(s[0]) - 1;
	int sn = sizeof(sub) / sizeof(sub[0]) - 1;

	printf("\t%d\n", search(s, n, sub, sn));


	return 0;
}
