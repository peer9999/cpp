#include <iostream>
#include <cstring>

#include "file.h"

using namespace std;

int main()
{
    MyContainer P[SIZE];
    MyContainerIndex I[SIZE];

    P[0].x = 1; P[0].y = 9.63; strcpy(P[0].z,"qwerty");
    P[1].x = 8; P[1].y = 7.34; strcpy(P[1].z,"asdf");
    P[2].x = 6; P[2].y = 5.09; strcpy(P[2].z,"zxcv");
    P[3].x = 4; P[3].y = 3.98; strcpy(P[3].z,"nmea");
    P[4].x = 2; P[4].y = 1.01; strcpy(P[4].z,"hjklp");

    for (int i = 0; i < SIZE; i++) {
        I[i].key = i;
        I[i].x   = P[i].x;
    }

    write(P,I,SIZE);
}
