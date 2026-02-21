#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>


void
printAdjM (int n, bool **a)
{
	printf ("\n\n\nThe adjacency matrix is:\n\t");
	for (int i = 0; i < n; i++)
		printf ("%6d", i + 1);
	printf ("\n\n");

	for (int i = 0; i < n; i++)
	{
		printf ("%d\t", i + 1);
		for (int j = 0; j < n; j++)
		{
			printf ("%6d", a[i][j] ? 1 : 0);
		}
		printf ("\n");
	}
}

int
printIncM (int n, bool **a)
{
	printf ("\nIncidence matrix:\n\t");
	for (int i = 0; i < n; i++)
		printf ("%d\t", i + 1);
	printf ("\n\n\n");

	int t = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j])
			{
				printf ("%d)\t", ++t);
				if (i == j)
				{
					for (int c = 0; c < n; c++)
						if (c == i)
							printf ("2\t");
						else
							printf ("0\t");
				}
				else
				{
					for (int c = 0; c < n; c++)
					{
						if (c == i)
							printf ("-1\t");
						else if (c == j)
							printf ("1\t");
						else
							printf ("0\t");
					}
				}
				printf ("\n\n");
			}
		}
	}

	return t;
}

void
printAdjL (int n, bool **a)
{
	printf ("\nThe adjacency list is:\n");
	for (int i = 0; i < n; i++)
	{
		printf ("%2d: ", i + 1);
		for (int j = 0; j < n; j++)
		{
			if (a[i][j])
				printf ("%d ", j + 1);
		}
		printf ("0\n");
	}
}

void
print (int n, bool **a)
{
	int flag = 0;
	printf
	("\n\nPrint\n\t1 = incidence matrix\n\t2 = adjacency matrix\n\t3 = adjacency list\n : ");
	while (scanf ("%d", &flag) != 1 || flag < 1 || flag > 3)
	{
		printf ("enter num from 1 to 3: ");
		while (getchar () != '\n');
	}

	switch (flag)
	{
	case 1:
		printIncM (n, a);
		break;
	case 2:
		printAdjM (n, a);
		break;
	case 3:
		printAdjL (n, a);
		break;
	default:
		printf ("AAAA");
	}
}

void
printAll (int n, bool **a)
{
	printIncM (n, a);
	printAdjM (n, a);
	printAdjL (n, a);
}

void
readIncM (int n, bool **a)
{
	bool exit = false;
	int t = 0;

	printf ("\nEnter the incidence matrix, non digit to exit:\n");
	for (int i = 0; i < n; i++)
		printf ("%d\t", i + 1);
	printf ("\n\n\n");

	do
	{
		int x = -1, y = -1;
		for (int i = 0; i < n; i++)
		{
			if (scanf ("%d", &t) != 1)
			{
				exit = true;
				break;
			}


			if (t != 0)
				if (t == 2)
					x = y = i;
				else if (t < 0)
					x = i;
				else
					y = i;
		}

		if (x != -1 && y != -1)
			a[x][y] = 1;
	}
	while (!exit);
}

void
readAdjM (int n, bool **a, int i, int j)
{
	bool exit = false;
	int t = 0;

	printf ("Enter the adjacency matrix, non digit to exit:\n");
	for (; i < n && !exit; i++)
	{
		t = -1;
		for (; j < n; j++)
		{
			if (scanf ("%d", &t) != 1)
			{
				exit = true;
				break;
			}

			if (t)
				a[i][j] = 1;
			else
				a[i][j] = 0;
		}
		j = 0;
	}
}

void
readAdjL (int n, bool **a, int i)
{
	bool exit = false;
	int t = 0;

	printf ("Enter the adjacency list, non digit to exit, 0 to next vertex:\n");
	for (; i < n && !exit; i++)
	{
		t = -1;
		for (int j = 0; j < n; j++)
			a[i][j] = 0;

		printf ("%d : ", i + 1);
		while (t != 0)
		{
			if (scanf ("%d", &t) != 1)
			{
				exit = true;
				break;
			}

			if (t > 0 && t <= n)
				a[i][t - 1] = 1;
			else if (t)
				printf ("\nno vertex %d, skipping...\n", t);
		}
	}
}

void
read (int n, bool **a)
{
	int flag = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[i][j] = 0;

	printf
	("\n\nRead\n\t1 = incidence matrix\n\t2 = adjacency matrix\n\t3 = adjacency list\n : ");
	while (scanf ("%d", &flag) != 1 || flag < 1 || flag > 3)
	{
		printf ("enter num from 1 to 3: ");
		while (getchar () != '\n');
	}

	switch (flag)
	{
	case 1:
		readIncM (n, a);
		break;
	case 2:
		readAdjM (n, a, 0, 0);
		break;
	case 3:
		readAdjL (n, a, 0);
		break;
	default:
		printf ("AAAA");
	}
}

bool**
edit (int n, bool **a)
{
	int flag = 0, t = 0;
	bool exit = false;

	while(!exit) {
		printf
		("\n\nEdit\n\t1 = add vertex\n\t2 = delete vertex\n\t3 = skip\n : ");
		while (scanf ("%d", &flag) != 1 || flag < 1 || flag > 3)
		{
			printf ("enter num from 1 to 3: ");
			while (getchar () != '\n');
		}

		switch (flag)
		{
		case 1:
			bool **a = malloc(n * sizeof(bool *));
			assert(a);
			for (int i = 0; i < n; i++) {
				a[i] = malloc(n * sizeof(bool));
				assert(a[i]);
			}
			break;

		case 2:
			break;

		case 3:
			exit = true;
			break;
		default:
			printf ("AAAA");
		}
	};


	printf("\n\nPrint\n\t1 = incidence matrix\n\t2 = adjacency matrix\n\t3 = adjacency list\n : ");
	while (scanf ("%d", &flag) != 1 || flag < 1 || flag > 3)
	{
		printf ("enter num from 1 to 3: ");
		while (getchar () != '\n');
	}

	exit = false;
	switch (flag)
	{
	case 1:
		int del;
		printf ("U want to del existing arcs?\n\t0 = no\n\t1 = yes\n : ");
		while (scanf ("%d", &del) != 1)
		{
			printf ("enter num: ");
			while (getchar () != '\n');
		}

		if (del)
		{
			while (!exit)
			{
				int rows = printIncM (n, a);
				if (!rows)
					break;

				int row = -1;
				printf
				("\nChoose a row in the incidence matrix, non digit to exit:\n");
				while (row <= 0 || row > rows)
				{
					printf ("Enter 1 <= num <= %d : ", rows);
					if (scanf ("%d", &row) != 1)
					{
						exit = true;
						while (getchar () != '\n');
						break;
					}
				}

				if (!exit)
				{
					int x = 0, y = 0, curr = 0;
					for (int i = 0; i < n && curr < row; i++)
						for (int j = 0; j < n && curr < row; j++)
							if (a[i][j])
							{
								curr++;
								if (curr == row)
								{
									x = i;
									y = j;
								}
							}
					a[x][y] = 0;
				}
			}
			exit = false;
		}

		readIncM (n, a);
		break;

	case 2:
		printAdjM (n, a);

		printf ("Enter coords to start overwriting : ");
		int i = -1, j = -1;
		while (scanf ("%d", &i) != 1 || i <= 0 || i > n)
		{
			printf ("enter 1 <= num <= %d: ", n);
			while (getchar () != '\n');
		}
		while (scanf ("%d", &j) != 1 || j <= 0 || j > n)
		{
			printf ("enter 1 <= num <= %d: ", n);
			while (getchar () != '\n');
		}

		readAdjM (n, a, i - 1, j - 1);
		break;

	case 3:
		printAdjL (n, a);

		printf ("Enter vertex to start overwriting : ");
		i = -1;
		while (scanf ("%d", &i) != 1 || i <= 0 || i > n)
		{
			printf ("enter 1 <= num <= %d: ", n);
			while (getchar () != '\n');
		}

		readAdjL (n, a, i - 1);

		break;
	default:
		printf ("AAAA");
	}
}

int
main ()
{
	int n;

	printf ("Enter the number of vertices: ");
	while (scanf ("%d", &n) != 1 || n <= 0)
	{
		while (getchar () != '\n');
		printf ("Enter num >= 1 : ");
	}

	bool **a = malloc(n * sizeof(bool *));
	assert(a);
	for (int i = 0; i < n; i++) {
		a[i] = malloc(n * sizeof(bool));
		assert(a[i]);
	}

	read (n, a);

	printAll (n, a);

	edit (n, a);

	printAll (n, a);


	return 0;
}
