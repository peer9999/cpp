#include <iostream>
#include <string>

#include "include/struct.h"
#include "include/menu.h"

using namespace std;

int Menu(struct Football *P,int &len)
{
    int k;

    cout << endl;
#ifdef _WIN32
    system("cls");
    cout << "������� ����" << endl;
    cout << "1. ���� ������" << endl;
    cout << "2. ����� ������" << endl;
    cout << "3. �������� ������" << endl;
    cout << "0. ����� �� ���������" << endl << endl;
    cout << "�������� ��������:";
#else
    system("clear");
    cout << "Главное меню" << endl;
    cout << "1. Ввод данных" << endl;
    cout << "2. Вывод данных" << endl;
    cout << "3. Удаление данных" << endl;
    cout << "0. Выход из программы" << endl << endl;
    cout << "Выберите действие:";
#endif
    cin >> k;
    cin.get();

    switch (k) {
        case 1:
            Input(P,len);
            break;
        case 2:
            Output(P,len,true);
            break;
        case 3:
            Delete(P,len);
            break;
        case 0:
            return 0;
    }
    return 1;
}
