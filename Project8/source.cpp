#include <iostream>
#include <cstdlib>
using namespace std;
int main()
{
    int const n=9;
    int a[n]={1,2,0,7,0,0,6,0,2};
    int i;
    for(i=0;i<n;i++){
        if (a[i]>0){
            cout<<" "<<a[i];
        }
    }
    system("pause");
    return 0;
}