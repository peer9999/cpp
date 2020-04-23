#include <iostream>

using namespace std;

void fun3(int **&arr, int x, int y) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (i == j) {
                cout << " " << arr[i][j];
            }
        }
    }
}

int main(void)
{
    int table[2][2] = { 1,2,3,4 };
    fun3(table,2,2);
    return 0;
}
