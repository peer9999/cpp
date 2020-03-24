#include <iostream>
#include <string>

#include "include/struct.h"
#include "include/function.h"

using namespace std;

void Input(struct Football *P,int &len)
{
    int k,l;

    cout << endl;
#ifdef _WIN32
    system("cls");
    cout << "���� ������" << endl;
    cout << "�������� ���������� ������� ��� �����:";
#else
    system("clear");
    cout << "Ввод данных" << endl;
    cout << "Выберите количество игроков для ввода:";
#endif
    cin >> k;
    cin.get();

    for (int i = len, l = k + len; i < l; i++) {
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
        len++;
    }

    pause();
}

void Output(struct Football *P,int &len,bool view)
{
    cout << endl;
#ifdef _WIN32
    system("cls");
    cout << "����� ������" << endl;
#else
    system("clear");
    cout << "Вывод данных" << endl;
#endif

    for (int i = 0; i < len; i++) {
        cout << i + 1 << ". " << P[i].name.firstname << " " << P[i].name.lastname << endl;
    }

    if (view) {
        pause();
    }
}

void Delete(struct Football *P,int &len)
{
    int k;

    if (len == 0) {
#ifdef _WIN32
        system("cls");
        cout << "������ �����������. ����������� ������� ���� ������." << endl;
#else
        system("clear");
        cout << "Данные отсутствуют. Используйте сначала ввод данных." << endl;
#endif
        pause();
        return;
    }

    Output(P,len,false);

    do {
        cout << endl;
#ifdef _WIN32
        cout << "�������� ������" << endl;
        cout << "�������� ����� ������ ��� ��������:";
#else
        cout << "Удаление данных" << endl;
        cout << "Выберите номер игрока для удаления:";
#endif
        cin >> k;
        cin.get();

        if (k < 1 || k > len) {
#ifdef _WIN32
            cout << "������ � ����� ������� �� ����������. ���������� ��� ���." << endl;
#else
            cout << "Игрока с таким номером не существует. Попробуйте еще раз." << endl;
#endif
            pause();
        }
    } while (k < 1 || k > len);

    for (int i = k - 1; i < len - 1; i++) {
        P[i] = P[i + 1];
    }
    len--;

    pause();
}
