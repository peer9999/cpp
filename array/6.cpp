#include <iostream>

using namespace std;

void fun3(int arr[][3],int x) {
    int i, j;
    for (i = 0; i < x; i++) {
        for (j = 0; j < 3; j++) {
            if (i == j) {
                cout << " " << arr[i][j];
            }
        }
    }
    cout << endl;
}

int main(void)
{
    int table[3][3] = { 1,2,3,4,5,6,7,8,9 };
    fun3(table,3);
    return 0;
}
