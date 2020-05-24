#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Heap {
	int* arr;
	int count;
	int capacity;
};

Heap* heap_create(int capacity);
void heap_insert(Heap* h, int key);
void heapify_bottom_top(Heap* h, int index);
void Read(int** graph, int n);
void Print(int** graph, int n);
void Dijkstra(int n, int** graph);

int main() {
	setlocale(LC_ALL, "rus");
	int n = 5;
	int** graph = new int* [n];
	for (int i = 0; i < n; i++) {
		graph[i] = new int[n];
	}
	Read(graph, n);
	Print(graph, n);
	Dijkstra(n, graph);
	for (int i = 0; i < n; i++) {
		delete[] graph[i];
	}
	delete[] graph;
	return 0;
}

void Dijkstra(int n, int** graph) {
	Heap* h;
	h = heap_create(400);

	bool* S = new bool[n];
	int* D = new int[n];
	int* P = new int[n];
	int Max_Sum = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			Max_Sum += graph[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (graph[i][j] == 0) {
				graph[i][j] = Max_Sum;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		S[i] = false;
		P[i] = 0;
		D[i] = graph[0][i];
		heap_insert(h, D[i]);
	}

	S[0] = true;
	P[0] = -1;

	for (int i = 0; i < n - 1; i++) {
		int k = 0;
		for (int j = 1; j < n; j++) {
			if (!S[k]) {
				if (!S[j] && D[j] <= D[k]) {
					k = j;
				}
			}
			else k++;
		}
		S[k] = true;

		for (int j = 1; j < n; j++) {
			if (!S[j]) {
				if (D[k] + graph[k][j] < D[j]) {
					D[j] = D[k] + graph[k][j];
					heap_insert(h, D[j]);
					P[j] = k;
				}
			}
		}
	}

	D[0] = 0;
	heap_insert(h, D[0]);
	cout << "Путь " << " Расстояние" << endl;
	int min = D[1],
		min_ind;
	for (int i = 0; i < n; i++) {
		cout << 1 << "-" << setw(4) << left << i + 1;
		cout << D[i] << endl;
		if (D[i] <= min && D[i] != 0) {
			min = D[i];
			min_ind = i + 1;
		}
	}
	cout << "\nКратчайший путь:\n";
	cout << 1 << "-" << setw(4) << left << min_ind;
	cout << min << endl;

	delete[] P;
	delete[] D;
	delete[] S;
}

void Read(int** graph, int n) {
	ifstream matrix;
	matrix.open("matrix.txt");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix >> graph[i][j];
		}
	}
	matrix.close();
}

void Print(int** graph, int n) {
	cout << "Матрица смежности графа: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << setw(4) << graph[i][j];
		}
		cout << endl;
	}
}

Heap* heap_create(int capacity) {
	Heap* h = new Heap[sizeof(Heap)];
	h->count = 0;
	h->capacity = capacity;
	h->arr = new int[capacity * sizeof(int)];

	return h;
}

void heap_insert(Heap* h, int key) {
	if (h->count < h->capacity) {
		h->arr[h->count] = key;
		heapify_bottom_top(h, h->count);
		h->count++;
	}
}

void heapify_bottom_top(Heap* h, int index) {
	int temp;
	int parent_node = (index - 1) / 2;

	if (h->arr[parent_node] > h->arr[index]) {  //swap and recursive call
		temp = h->arr[parent_node];
		h->arr[parent_node] = h->arr[index];
		h->arr[index] = temp;
		heapify_bottom_top(h, parent_node);
	}
}