#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
};

struct Queue {
    int size;
    Node *first;
    Node *last;
};

void Init(Queue *Q) {
    Q->first       = new Node;
    Q->first->next = NULL;
    Q->last        = Q->first;
    Q->size        = 0;
}

bool Empty(Queue *Q) {
    return (Q->size == 0) ? true : false;
}

int Top(Queue *Q) {
    return Q->first->data;
}

int End(Queue *Q) {
    return Q->last->data;
}

void Add(Queue *Q) {
    int value;
    cout << "\nЗначение > ";
    cin >> value;
    cin.get();
    if (Empty(Q)) {
        Q->first->data = value;
    } else {
        Q->last->next = new Node;
        Q->last       = Q->last->next;
        Q->last->data = value;
        Q->last->next = NULL;
    }
    Q->size++;
    cout << "\nЭлемент добавлен\n\n";
}

void Delete(Queue *Q) {
    Q->first = Q->first->next;
    Q->size--;
    cout << "\nЭлемент удален\n\n";
}

int Size(Queue *Q) {
    return Q->size;
}

void Print(Queue *Q) {
    Node *N;
    for (N = Q->first; N != NULL; N = N->next) {
        cout << N->data << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL,"Rus");
    Queue Q;
    Init(&Q);
    char number;
    do {
        cout << "1. Добавить элемент" << endl;
        cout << "2. Удалить элемент" << endl;
        cout << "3. Вывести верхний элемент" << endl;
        cout << "4. Вывести последний элемент" << endl;
        cout << "5. Узнать размер очереди" << endl;
        cout << "6. Напечатать всю очередь" << endl;
        cout << "0. Выйти\n\n";
        cout << "Номер команды > ";
        cin >> number;
        cin.get();
        switch (number) {
            case '1':
                Add(&Q);
                break;
            case '2':
                if (Empty(&Q)) cout << endl << "Очередь пуста\n\n";
                else Delete(&Q);
                break;
            case '3':
                if (Empty(&Q)) cout << endl << "Очередь пуста\n\n";
                else { cout << "\nНачальный элемент: " << Top(&Q) << "\n\n"; }
                break;
            case '4':
                if (Empty(&Q)) cout << endl << "Очередь пуста\n\n";
                else { cout << "\nПоследний элемент: " << End(&Q) << "\n\n"; }
                break;
            case '5':
                if (Empty(&Q)) cout << endl << "Очередь пуста\n\n";
                else { cout << "\nРазмер очереди: " << Size(&Q) << "\n\n"; }
                break;
            case '6':
                if (Empty(&Q)) cout << endl << "Очередь пуста\n\n";
                else Print(&Q);
                break;
            case '0':
                break;
            default:
                cout << endl << "Команда не определена\n\n";
                break;
        }
    } while (number != '0');
    return 0;
}
