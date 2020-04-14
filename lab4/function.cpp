#include <omp.h>
#include <iostream>
#include <cstring>
#include <cmath>

#include "include/function.h"

using namespace std;

double extremum(double x0)
{
	srand(time(NULL));

	double c = 0.75, step = 5, step_min = 0.0001;
	int N = 0, N_max = 100, n = 0, n_max = 10, b = 6;
	char surname[] = "gribovskij";
	int a = strlen(surname);
	double x1, y1, y0, y, min, random;

	y0  = func(x0, a, b);
	y   = y0;
	min = y0;
/*
	cout << "#\t\ty\t\tx\t\tstep\n";
	cout << N + 1 << "\t\t"
		<< setprecision(5) << y0 << "\t\t"
		<< x0 << "\t\t"
		<< step << "\n";
*/
	do {
		N++;
		random = (double)(rand()) / RAND_MAX * 2 - 1;
		x1     = x0 + step * random;
		y1     = func(x1, a, b);

		if (min > y1) { 
			min = y1;
		}
/*
		cout << N + 1 << "\t\t"
 			 << setprecision(5) << y1 << "\t\t"
			 << x1 << "\t\t"
			 << step << "\n";
*/
		if (y1 < y0) {
			x0 = x1;
			y0 = y1;
		}

		if (y == y1) {
			n++;
		}
		else {
			n = 0;
		}
		y = y1;

		if (n > n_max) {
			break;
		}

		step = step * c;
		if (step < step_min) {
			break;
		}

		if (N > N_max) {
			break;
		}
	} while (1);
//        cout << endl;
	return min;
}

double func(int x, int a, int b) {
	return cos(x) + (1 / b) * cos(a * x + 1) + (1 / pow(b, 2)) * cos(pow(a, 2) * x + 2) + (1 / pow(b, 3)) * cos(pow(a, 3) * x + 3) + (1 / pow(b, 4)) * cos(pow(a, 4) * x + 4);
}
