#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int const n = 3;
    int mas[n][n];
    int locmin[n];
    int LocMin = 0;
    int i, j, max, min;
    cout << "Matrix : " << endl;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            mas[i][j] = rand() % 18 + 1;
            cout << " " << mas[i][j];
        }
        cout << endl;
    }
    for (i = 0; i < n; i++) {
        min = mas[i][0];
        for (j = 1; j < n; j++) {
            if (min > mas[i][j]) {
                min = mas[i][j];
            }
        }
        cout << "String " << i + 1 << " min = " << min << endl;
        locmin[LocMin] = min;
        LocMin++;
    }
    max = locmin[0];
    for (i = 1; i < LocMin; i++) {
        if (max < locmin[i]) {
            max = locmin[i];
        }
    }
    cout << "Max = " << max << endl;
//    system("pause");
    return 0;
}
