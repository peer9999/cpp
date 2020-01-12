#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	int i;
	for(i = 0; i < 5; i++){
		cout << " " << 1 ;
		for(i = 0; i < 4; i++){
			cout << " " << 1  ;
			for(i = 0; i < 3; i++){
				cout << " " << 1 ;
				for(i = 0; i < 2; i++){
					cout << " " << 1 ;
					for(i = 0; i < 1; i++){
						cout << " " << 1 ;
						cout<<endl;
					}
				 cout<<endl;
				}
				cout<<endl;
			}
			cout<<endl;
		}
		cout<<endl;
	}
	system("pause");
	return 0;
}
