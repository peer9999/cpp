#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int i, j, max;
    int const n = 3;
    int** p = new int* [n];
    int LocMin = 0;
    for (i = 0; i < n; i++) {
        p[i] = new int[n];
        for (j = 0; j < n; j++) {
            p[i][j] = rand() % 18;
            cout << " " << p[i][j];
        }
        cout << endl;
    }
    int* x = new int[n];
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == 0) {
                if (j == 0) {
                    if (p[i][j] < p[i][j + 1] && p[i][j] < p[i + 1][j]) {
                        cout << "String: " << i + 1 << " Column: " << j + 1 << " Min: " << p[i][j] << endl;
                        x[LocMin] = p[i][j];
                        LocMin++;
                    }
                }
                else if (j == n - 1) {
                    if (p[i][j] < p[i][j - 1] && p[i][j] < p[i + 1][j]) {
                        cout << "String: " << i + 1 << " Column: " << j + 1 << " Min: " << p[i][j] << endl;
                        x[LocMin] = p[i][j];
                        LocMin++;
                    }
                }
                else {
                    if (p[i][j] < p[i][j - 1] && p[i][j] < p[i][j + 1] && p[i][j] < p[i + 1][j]) {
                        cout << "String: " << i + 1 << " Column: " << j + 1 << " Min: " << p[i][j] << endl;
                        x[LocMin] = p[i][j];
                        LocMin++;
                    }
                }
            }
            else if (i == n - 1) {
                if (j == 0) {
                    if (p[i][j] < p[i][j + 1] && p[i][j] < p[i - 1][j]) {
                        cout << "String: " << i + 1 << " Column: " << j + 1 << " Min: " << p[i][j] << endl;
                        x[LocMin] = p[i][j];
                        LocMin++;
                    }
                }
                else if (j == n - 1) {
                    if (p[i][j] < p[i][j - 1] && p[i][j] < p[i - 1][j]) {
                        cout << "String: " << i + 1 << " Column: " << j + 1 << " Min: " << p[i][j] << endl;
                        x[LocMin] = p[i][j];
                        LocMin++;
                    }
                }
                else {
                    if (p[i][j] < p[i][j - 1] && p[i][j] < p[i][j + 1] && p[i][j] < p[i - 1][j]) {
                        cout << "String: " << i + 1 << " Column: " << j + 1 << " Min: " << p[i][j] << endl;
                        x[LocMin] = p[i][j];
                        LocMin++;
                    }
                }
            }
            else {
                if (j == 0) {
                    if (p[i][j] < p[i][j + 1] && p[i][j] < p[i - 1][j] && p[i][j] < p[i + 1][j]) {
                        cout << "String: " << i + 1 << " Column: " << j + 1 << " Min: " << p[i][j] << endl;
                        x[LocMin] = p[i][j];
                        LocMin++;
                    }
                }
                else if (j == n - 1) {
                    if (p[i][j] < p[i][j - 1] && p[i][j] < p[i - 1][j] && p[i][j] < p[i + 1][j]) {
                        cout << "String: " << i + 1 << " Column: " << j + 1 << " Min: " << p[i][j] << endl;
                        x[LocMin] = p[i][j];
                        LocMin++;
                    }
                }
                else {
                    if (p[i][j] < p[i][j - 1] && p[i][j] < p[i][j + 1] && p[i][j] < p[i - 1][j] && p[i][j] < p[i + 1][j]) {
                        cout << "String: " << i + 1 << " Column: " << j + 1 << " Min: " << p[i][j] << endl;
                        x[LocMin] = p[i][j];
                        LocMin++;
                    }
                }
            }
        }
    }
    max = x[0];
    for (i = 0; i < LocMin; i++) {
        if (max < x[i]) {
            max = x[i];
            cout << max << endl;
        }
    }

    int** c = new int* [n + 1];
    for (i = 0; i < n; i++) {
        c[i] = new int[n];
        for (j = 0; j < n; j++) {
            c[i][j] = p[i][j];
        }
    }
    c[3] = new int[n];
    for (j = 0; j < n; j++) {
        c[3][j] = rand() % 18;
    }
    for (i = 0; i < n + 1; i++) {
        for (j = 0; j < n; j++) {
            cout << " " << c[i][j];
        }
        cout << endl;
    }
/*
    system("pause");
*/
    return 0;
}
