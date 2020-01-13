#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	int fl;
	int const n = 4;
	int nmas[n][n];
	int mas[n][n];
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			mas[i][j] = rand() % 10;
			cout << " " << mas[i][j] << " ";
		}
		cout << endl;
	}
	cout << " " << endl;
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++) {
			nmas[j][i] = mas[i][j];
			cout << " "<< nmas[j][i] << " ";
		}
		cout << endl;
	}
	
	system("pause");
	return 0;
}