#include <iostream>
#include <iomanip>
#include <string>

#include "include/var.h"
#include "include/struct.h"
#include "include/function.h"

using namespace std;

void Output(Football *P,int &len)
{
    if (len == 0) {
#ifdef _WIN32
        cout << "������ �����������. ����������� ������� ���� ������." << endl;
#else
        cout << "Данные об игроках отсутствуют. Используйте пункт \"Ввод\"." << endl;
#endif
    }

    cout.fill('_');
    for (int i = 0; i < len; i++) {
        if (!i) {
            cout << "ИГРОКИ" << endl;
            cout << setw(5) << " " << setw(20) << "Страна" << "Клуб" << "Имя" << "Фамилия" << endl;
        }
        cout << setw(5) << i + 1 << setw(20) << P[i].country << P[i].club << P[i].name.firstname << P[i].name.lastname << endl;
    }
}

void Input(Football *P,int &len)
{
    int k,l,country,club;

    cout << endl;
#ifdef _WIN32
    cout << "�������� ���������� ������� ��� �����:";
#else
    cout << "Выберите количество игроков для ввода:";
#endif
    cin >> k;
    cin.get();

    for (int i = len, l = k + len; i < l; i++) {

#ifdef _WIN32
        cout << "���: ";
#else
        cout << "Страна ( ";
        for (int j = 0; j < 3; j++) {
            cout << j + 1 << "-" << PlayerCountry[j] << " ";
        }
        cout << "): ";
#endif
        cin >> country;
        cin.get();
        P[i].country = PlayerCountry[country - 1];

#ifdef _WIN32
        cout << "���: ";
#else
        cout << "Клуб (  ";
        for (int j = 0; j < 4; j++) {
            cout << j + 1 << "-" << PlayerClub[j] << " ";
        }
        cout << "): ";
#endif
        cin >> club;
        cin.get();
        P[i].club = PlayerClub[club - 1];

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

void Sort(Football *P,int &len)
{
    pause();
}

void Delete(Football *P,int &len)
{
    int k;

    if (len == 0) {
        return;
    }

#ifdef _WIN32
    cout << "�������� ����� ������ ��� ��������:";
#else
    cout << endl << endl << endl << "Выберите игрока для удаления:";
#endif
    cin >> k;
    cin.get();

    if (k < 1 || k > len) {
#ifdef _WIN32
        cout << "������ � ����� ������� �� ����������. ���������� ��� ���." << endl;
#else
        cout << "Такого игрока не существует. Попробуйте еще раз." << endl;
#endif
        pause();
        return;
    }

    for (int i = k - 1; i < len - 1; i++) {
        P[i] = P[i + 1];
    }
    len--;
}
