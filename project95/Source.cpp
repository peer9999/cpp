#include <iostream>
#include <cstdlib>
using namespace std;

void arr(int* , int );
int* func1(int [][4], int, int, int);
int* func2(int [][4], int, int);
int** func3(int [][4], int, int, int);

int main()
{
	int const n = 4;
	int m[n][n];
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			m[i][j] = rand() % 10;
			cout << " " << m[i][j] << " ";
		}
		cout << endl;
	}
	int* min;

	min = func1(m, n, n, 0);
	arr(min, n);

	min = func1(m, n, n, 1);
	arr(min, n);
	cout << endl;
//	system("pause");
	return 0;
}

int* func1(int mas[][4], int n, int m, int fl) {
	int min[4];
	int mmas[4][4];
	if (fl) {
		for (int j = 0; j < m; j++) {
			for (int i = 0; i < n; i++) {
				mmas[j][i] = mas[i][j];
			}
		}
		mas = mmas;
	}
	for (int i = n - 1; i >= 0; i--) {
		min[i] = mas[i][0];
		for (int j = 1; j < m; j++) {
			if (min[i] > mas[i][j]) {
				min[i] = mas[i][j];
			}
		}
		cout << " " << min[i];
	}
	return min;
}

int* func2(int mas[][4], int n, int m) {
	int min[4];
	for (int j = 0; j < m; j++) {
		min[j] = mas[0][j];
		for (int i = 1; i < n; i++) {
			if (min[j] > mas[i][j]) {
				min[j] = mas[i][j];
			}
		}
		cout << " " << min[j];
	}
	return min;
}

int** func3(int mas[][4], int n, int m, int fl) {
	int** nmas;
	if (fl == 0) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				nmas[i][j] = mas[i][j];
			}
		}
	}
	else {
		for (int j = 0; j < m; j++) {
			for (int i = 0; i < n; i++) {
				nmas[j][i] = mas[i][j];
			}
		}
	}
	return nmas;
}

void arr(int* min, int n) {
	int max = min[0];
	for (int i = 1; i < n; i++) {
		if (max < min[i]) {
			max = min[i];
		}
	}
	cout << " => " << max << endl;
}
