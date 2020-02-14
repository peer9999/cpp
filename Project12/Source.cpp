#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	int const n = 3;
	int a[n][n];
	int i = 0, j = 0;
	cout<<"Matrix : ";
	cout<<endl;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			a[i][j] = rand() % 100;
		cout<<" "<<a[i][j];
		}
	cout<<endl;
	}
	/*while(i<n&&j<n){
		}*/
	cout<< a[0][2];
	cout<<endl;
	return 0;
}
