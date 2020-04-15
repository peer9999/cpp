#include <omp.h>
#include <iostream>
#include <iomanip>

#include "include/function.h"

using namespace std;

int main()
{
    const int I = 100;
    int i, thread = 0;
    double min;
    double A[I];

    cout << setprecision(5) << setfill(' ') << setw(10) << "Extremum" << setw(10) << "Xbgn" << setw(10) << "Xend" << setw(10) << "Thread" << endl;

    #pragma omp parallel for
    for (i = 0; i < I; i++) {
        thread = omp_get_thread_num();
        A[i] = extremum(i + 1,thread);
    }

    min = A[0];
    for (i = 1; i < I; i++) {
        if (min > A[i]) {
            min = A[i];
        }
    }

    cout << "Min Extremum = " << min << endl;
    return 0;
}
