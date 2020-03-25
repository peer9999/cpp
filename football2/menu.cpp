#include <iostream>

#include "include/menu.h"

using namespace std;

void MenuView()
{
#ifdef _WIN32
    system("cls");
    cout << endl << "    ������� ����" << endl << "1.����    " << "2.����������    " << "3.��������    " << "0.�����" << endl << endl;
#else
    system("clear");
    cout << endl << "    ГЛАВНОЕ МЕНЮ" << endl << "1.Ввод    " << "2.Сортировка    " << "3.Удаление    " << "0.Выход" << endl << endl;
#endif
}

int MenuSelect()
{
    int k = 0;
#ifdef _WIN32
    cout << endl << "�������� ��������: ";
#else
    cout << endl << "Выберите действие: ";
#endif
    cin >> k;
    cin.get();
    return k;
}
