#include <iostream>

using namespace std;

void fun(int **,int,int);

void fun(int **array,int x,int y)
{
    int *p_array = (int*) array;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (i == j) {
                cout << p_array[ i * x + j ] << endl;
            }
        }
    }
}

int main(void)
{
    int table[2][2] = { 1,2,3,4 };
    fun((int**) table,2,2);
    return 0;
}
