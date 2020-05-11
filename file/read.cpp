#include <iostream>
#include <cstring>

#include "file.h"

using namespace std;

int main()
{
    MyContainer P[SIZE];
    MyContainerIndex I[SIZE];
    int key,x;

    read(P,I,SIZE);

    for (int i = 0; i < SIZE; i++) {
        cout << P[i].x << ';' << P[i].y << ';' << P[i].z << endl;
    }
    for (int i = 0; i < SIZE; i++) {
        cout << I[i].key << " => " << I[i].x << endl;
    }

    cout << "find x: ";
    cin >> x;
    cin.get();

    for (int i = 0; i < SIZE; i++) {
        if (I[i].x == x) {
            key = i;
            break;
        }
    }

    cout << "found: " << endl;
    cout << P[key].x << ';' << P[key].y << ';' << P[key].z << endl;
}
