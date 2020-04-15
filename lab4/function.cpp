#include <omp.h>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>

#include "include/function.h"

using namespace std;

double extremum(double x0,int thread)
{
    srand(time(NULL));

    double c = 0.75, step = 5, step_min = 0.0001;
    int N = 0, N_max = 100, n = 0, n_max = 10, b = 6;
    char surname[] = "gribovskij";
    int a = strlen(surname);
    double x1, y1, y0, y, min, random, X0 = x0;

    y0  = func(x0, a, b);
    y   = y0;
    min = y0;

    do {
        N++;
        random = (double)(rand()) / RAND_MAX * 2 - 1;
        x1     = x0 + step * random;
        y1     = func(x1, a, b);

        if (min > y1) { 
            min = y1;
        }

        if (y1 < y0) {
            x0 = x1;
            y0 = y1;
        }

        step = step * c;
        if (step < step_min) {
            break;
        }
/*
        if (y == y1) {
            n++;
        } else {
            n = 0;
        }
        y = y1;

        if (n > n_max) {
            break;
        }

        if (N > N_max) {
            break;
        }
*/
    } while (1);

    #pragma omp critical
    {
        cout << setprecision(5) << setfill(' ') << setw(10) << min << setw(10) << X0 << setw(10) << x0 << setw(10) << thread << endl;
    }

    return min;
}

double func(int x, int a, int b) {
    return cos(x) + (1 / b) * cos(a * x + 1) + (1 / pow(b, 2)) * cos(pow(a, 2) * x + 2) + (1 / pow(b, 3)) * cos(pow(a, 3) * x + 3) + (1 / pow(b, 4)) * cos(pow(a, 4) * x + 4);
}
