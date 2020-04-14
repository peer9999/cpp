#include <omp.h>
#include <iostream>

#include "include/function.h"

using namespace std;

int main()
{
	const int I = 100;
	int i;
	double min;
	double A[I];

        #pragma omp parallel for
	for (i = 0; i < I; i++) {
		A[i] = extremum(i + 1);
	}

	min = A[0];
	cout << "A = " << A[0] << endl;
	for (i = 1; i < I; i++) {
        	cout << "A = " << A[i] << endl;
		if (min > A[i]) {
			min = A[i];
		}
	}

	cout << "min = " << min << endl;
	return 0;
}
