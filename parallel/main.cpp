#include <omp.h>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <ctime>
#include <chrono>

#include "include/function.h"

using namespace std;

int main()
{
        unsigned int start_time = clock();
        auto begin = std::chrono::steady_clock::now();

	int i, j;
	double A[100],B[100],T[3];

	for (i = 0, j = 1; i < 1000; i++, j++) {
		A[i][0] = j;
		A[i][1] = a;
		A[i][2] = rand() % 10 + 2;
		B[i]    = func(A[i]);
	}

	srand(time(NULL));
	setlocale(0,"");

	int a, i, j;
	double x1, x0, y1, y0, min, random;
	double c = 0.75, step = 555, step_min = 0.0001;
	char surname[30] = "gribovskij";
	a = strlen(surname);


        #pragma omp parallel for
	for (i = 0; i < 1000; i++) {
		y0 = B[i];
		do {
			random = (double)(rand()) / RAND_MAX * 2 - 1;
			x1     = A[i][0] + step * random;
			T[0]   = x1;
			T[1]   = A[i][1];
			T[2]   = A[i][2];
			y1     = func(T);

			if (y1 < y0) {
				A[i][0] = x1;
				B[i]    = y1;
			}

			step = step * c;
			if (step < step_min) {
				break;
			}
		} while (1);
	}

	min = 0;
	for (i = 0; i < 1000; i++) {
//		cout << "B = " << B[i] << endl;
		if (min > B[i]) {
			min = B[i];
		}
	}

	cout << "min = " << min << endl;

        unsigned int end_time = clock();
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

	cout << "time tick   = " << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
	cout << "time clock  = " << (end_time - start_time) / 1000.0 << endl;
        cout << "time chrono = " << elapsed_ms.count() / 1000.0 << endl;
        cout << "time = " << clock() / 1000.0 << endl;

	return 0;
}

double func(double A[3])
{
	int a, b, x;
	x = A[0];
	b = A[1];
	a = A[2];
	return cos(x) + (1 / b) * cos(a * x + 1) + (1 / pow(b, 2)) * cos(pow(a, 2) * x + 2) + (1 / pow(b, 3)) * cos(pow(a, 3) * x + 3) + (1 / pow(b, 4)) * cos(pow(a, 4) * x + 4);
}
