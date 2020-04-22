#include <iostream>
using namespace std;

struct comp {
	int data;
	comp* next;
};

struct Que {
	Que* first;
	Que* last;
};

void del(comp**, int);
void print(comp*);

int main() {
	int i;
	comp* top = NULL;
	
	print(top);
	cout << endl;
	cout << endl;
}

void init(Que *q) {
	q->first = 0;
	q->last = 0;
}

int isempty(Que* q) {
	if (q->first == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

void addelem(comp* q, int x) {
	comp* temp, * p;
	temp = (comp*)malloc(sizeof(comp));
	p = q->next;
	q->next = temp;
	temp->data = x;
	temp->next = p;
}

void insert(Que* q, int x) {
	addelem(q->last,x);
}

void del(comp** top, int x) {

}

void print(comp* top,comp *end) {
	comp* p = top;
	//end = p->next;
	while (p != NULL) {
		cout << p->data;
		p = p->next;
	}
}

