#include <iostream>
#include <cstdlib>
using namespace std;

void arr(int*, int);

int main()
{
	int const n = 4;
	int m[n][n];
	int i, j, max;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			m[i][j] = rand() % 10;
			cout << " " << m[i][j] << " ";
		}
		cout << endl;
	}
	int min[n];

	for (i = n - 1; i >= 0; i--) {
		min[i] = m[i][0];
		for (j = 1; j < n; j++) {
			if (min[i] > m[i][j]) {
				min[i] = m[i][j];
			}
		}
		cout << " " << min[i];
	}
	arr(min, n);

	for (j = 0; j < n; j++) {
		min[j] = m[0][j];
		for (i = 1; i < n; i++) {
			if (min[j] > m[i][j]) {
				min[j] = m[i][j];
			}
		}
		cout << " " << min[j];
	}
	arr(min, n);

	cout << endl;
	system("pause");
	return 0;
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
