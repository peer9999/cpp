#include <iostream>
#include <iomanip>
#include <Windows.h>
using namespace std;

double func(int , int, int );

int main()
{
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int a, N = 0, N_max, n = 0, n_max = 10;
	double x1, x0, b, step, min, y1, y0, y, random;
	double c = 0.85, step_min = 0.0001;
	char surname[30];

	cout << "x0 =  ";
	cin >> x0;

	cout << "Введите шаг step = ";
	cin >> step;

	cout << "Фамилия: ";
	cin >> surname;
	a = strlen(surname);

	cout << "Количество итераций : ";
	cin >> N_max;

	cout << "b = ";
	do
	{
		cin >> b;
		if ((b >= 2) && (b <= 10)) {
			break;
		}
		else {
			cout << "Введены неверные значения\n";
		}
	} while (1);
	

	y0 = func(x0, a, b);
	y  = y0;
	min = y0;
	cout << "#\ty\tx\tstep\n";

	cout << N + 1 << "\t"
		<< setprecision(5) << y0 << "\t"
		<< x0 << "\t"
		<< step << "\n";

	do {
		random = (double)(rand()) / RAND_MAX * (1 - (-1)) + (-1);
		N++;

		x1 = x0 + step * random;
		y1 = func(x1, a, b);

		if (min > y1) { 
			min = y1;
		}

		cout << N + 1 << "\t"
 			 << setprecision(5) << y1 << "\t"
			 << x1 << "\t"
			 << step << "\n";

		if (y1 < y0) {
			x0 = x1;
			y0 = y1;
		}

		step = step * c;

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

		if (step < step_min) {
			break;
		}

		if (N > N_max) {
			break;
		}

	} while (1);

	cout << "min = " << min << endl;
	cout << endl;
	return 0;
}

double func(int x, int a, int b) {
	return cos(x) + (1 / b) * cos(a * x + 1) + (1 / pow(b, 2)) * cos(pow(a, 2) * x + 2) + (1 / pow(b, 3)) * cos(pow(a, 3) * x + 3) + (1 / pow(b, 4)) * cos(pow(a, 4) * x + 4);
}
