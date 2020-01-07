#include <iostream>
using namespace std;
int Max(int a,int b)
{
return a > b ? a : b;
}
int Min(int a, int b)
{
    return a < b ? a : b;
}
int main()
{
int a = 4, b = 5, c = 2, d = 7 ;
int max = Max (Max (a, b), Max (c, d));
int min = Min (Min (a, b), Min (c, d));
  cout << "min = " << min << endl << "max = " << max<<endl << max + min << endl;
  cout << endl;
  return 0;
}