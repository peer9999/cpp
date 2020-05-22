#include <bits/stdc++.h>

using namespace std;

int const SIZE = 6;

int main() {
//    int a[SIZE][SIZE]; // матрица связей
    int d[SIZE];       // минимальное расстояние
    int v[SIZE];       // посещенные вершины
    int temp,minindex,min;
    int begin_index = 0;
    int a[SIZE][SIZE] = {
        {0,  10, 12, 33, 24, 17},
        {10, 0,  2,  13, 47, 35},
        {12, 2,  0,  3,  21, 55},
        {33, 13, 3,  0,  4,  9},
        {24, 47, 21, 4,  0,  5},
        {17, 35, 55, 9,  5,  0}
    };

/*
    // Инициализация матрицы связей
    for (int i = 0; i < SIZE; i++) {
        a[i][i] = 0;
        for (int j = i + 1; j < SIZE; j++) {
            cout << "Введите расстояние " << i + 1 << " - " << j + 1 << ": ";
            cin >> temp;
            cin.get();
            a[i][j] = a[j][i] = temp;
        }
    }
*/

    // Вывод матрицы связей
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << " " << a[i][j];
        }
        cout << endl;
    }

    // Инициализация вершин и расстояний
    for (int i = 0; i < SIZE; i++) {
        d[i] = INT_MAX;
        v[i] = 1;
    }
    d[begin_index] = 0;

    // Шаг алгоритма
    int z = 1;
    do {
        minindex = INT_MAX;
        min      = INT_MAX;
        for (int i = 0; i < SIZE; i++) { // Если вершину ещё не обошли и вес меньше min
            if ((v[i] == 1) && (d[i] < min)) { // Переприсваиваем значения
                min      = d[i];
                minindex = i;
            }
        }

cout << "z=   " << z << endl;
cout << "ind= " << minindex << endl;
cout << "min= " << min << endl;

        // Добавляем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины
        if (minindex != INT_MAX) {
            for (int i = 0; i < SIZE; i++) {
                if (a[minindex][i] > 0) {
                    temp = min + a[minindex][i];
                    if (temp < d[i]) {
                        d[i] = temp;
                    }
                }
            }
            v[minindex] = 0;
        }
        z++;
    } while (minindex < INT_MAX);

    // Вывод кратчайших расстояний до вершин
    cout << endl << "Кратчайшие расстояния до вершин: " << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << i << " = " << d[i] << "   ";
    }

    // Восстановление пути
    int ver[SIZE];       // массив посещенных вершин
    int end = 4;         // индекс конечной вершины = 5 - 1
    ver[0] = end + 1;    // начальный элемент - конечная вершина
    int k = 1;           // индекс предыдущей вершины
    int weight = d[end]; // вес конечной вершины

    while (end != begin_index) { // пока не дошли до начальной вершины
        for (int i = 0; i < SIZE; i++) { // просматриваем все вершины
            if (a[i][end] != 0) {  // если связь есть
                int temp = weight - a[i][end]; // определяем вес пути из предыдущей вершины
                if (temp == d[i])  { // если вес совпал с рассчитанным значит из этой вершины и был переход
                    weight = temp;   // сохраняем новый вес
                    end    = i;      // сохраняем предыдущую вершину
                    ver[k] = i + 1;  // и записываем ее в массив
                    k++;
                }
            }
        }
    }

    // Вывод пути (начальная вершина оказалась в конце массива из k элементов)
    cout << endl << "Вывод кратчайшего пути: " << endl;
    for (int i = k - 1; i >= 0; i--) {
        cout << " " << ver[i];
    }

    getchar();
    getchar();
    return 0;
}
