#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	int const n = 6000;
	int a[n][n];
	int i, j;
	cout << "Matrix : " << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			a[i][j] = rand() % 1000;
			cout << " " << a[i][j];
		}
		cout << endl;
	}
	int m[n];
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) {
				m[i]=a[i][j];
			}
		}
		cout << " " << m[i];
	}
	system("pause");
	return 0;
}
