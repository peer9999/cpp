#include <iostream>
#include <string>

#include "struct.h"

using namespace std;

void Input(struct Football *P,int index)
{
    cout << endl;
#ifdef _WIN32
    system("cls");
    cout << "���� ������" << endl;
#else
//    system("clear");
    cout << "Ввод данных" << endl;
#endif

    for (int i = 0; i < index; i++) {
#ifdef _WIN32
        cout << "���: ";
#else
        cout << "Имя: ";
#endif
        getline(cin,P[i].name.firstname);

#ifdef _WIN32
        cout << "�������: ";
#else
        cout << "Фамилия: ";
#endif
        getline(cin,P[i].name.lastname);
    }
}

void Output(struct Football *P,int index)
{
    cout << endl;
#ifdef _WIN32
    system("cls");
    cout << "����� ������" << endl;
#else
//    system("clear");
    cout << "Вывод данных" << endl;
#endif

    for (int i = 0; i < index; i++) {
        cout << P[i].name.firstname << " " << P[i].name.lastname << endl;
    }
}
