#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	int i, j, x = 1;
	int const n = 3;
	int* a = new int[n];
	int** p = new int* [n];
	for (i = 0; i < n; i++) {
		p[i] = new int[n];
		for (j = 0; j < n; j++) {
			p[i][j] = rand() % 10;
			cout << " " << p[i][j];
		}
		cout << endl;
	}

	cout << endl;
	int* m = new int[n];
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) {
				m[i] = p[i][j];
			}
		}
		cout << " " << m[i];
	}

	cout << endl;
	for (i = 0; i < n; i++) {
		x *= m[i];
		cout << " " <<x;
	}
	cout << endl;
	delete[]p;
	delete[]m;
	system("pause");
	return 0;
}
