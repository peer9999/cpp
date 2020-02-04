#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	int i;
	int n = 5;
	while (1) {
		for (i = 0; i < n ; i++) {
			cout << " " << i ;
		}
		cout << endl;
		if (--n == 0) break;
	}
	system("pause");
	return 0;
}
