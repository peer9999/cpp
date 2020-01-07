#include <iostream>
using namespace std;
int Max (int a, int b)
{
    return a > b ? a : b;
}
int Min (int a,int b)
{
    return a < b ? a : b;
}
int main()
{
    int a = 8,b = 4,c = 9,d = 2;
    cin >> a  ;
    cin >> b;
    cin >> c;
    cin >> d;
    int max = Max(Max(a,b),Max(c,d));
    int min = Min(Min(a,b),Min(c,d));
    cout<<"Max ="<<max<<endl;
    cout<<"Min ="<<min<<endl;
    cout<<"Summa ="<<min + max<<endl;
    system("pause");
    return 0;
}
