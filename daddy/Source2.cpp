#include <iostream>
#include <cstring>
//#include <Windows.h>

using namespace std;
int main()
{
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
	int const max = 100;
	int const k = 3;
	char s[k][max];
	int i, j;
	for (i = 0; i < k; i++) {
		cin.getline(s[i], max, '.');;
	}

	int n;
	cin >> n;
	char* p = strtok(s[n], " ");
	int y, z;
	int x = 0, q = max;
	char* ss = p;
	char* hh = p;
	while (p != NULL) {
		y = strlen(p);
		if (x < y) {
			x = y;
			ss = p;
		}
		z = strlen(p);
		if (q > z) {
			q = z;
			hh = p;
		}
		p = strtok(NULL, " ");
	}
	cout << "����� ������� �����: " << ss << "\n"
		<< "C���� �������� �����: " << hh << "\n";
	return 0;
}