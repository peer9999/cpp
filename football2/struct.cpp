#include <iostream>
#include <iomanip>
#include <string>
#include <clocale>
#include <cstdlib>
#include <stdexcept>

#include "include/var.h"
#include "include/struct.h"
#include "include/function.h"

using namespace std;

void Output(Football *P,int &len)
{
    setlocale(LC_ALL,"ru_RU.utf8");

    if (len == 0) {
#ifdef _WIN32
        cout << "������ �� ������� �����������. ����������� ����� \"����\"." << endl;
#else
        cout << "Данные об игроках отсутствуют. Используйте пункт \"Ввод\"." << endl;
#endif
        return;
    }

    for (int i = 0; i < len; i++) {
        if (!i) {
#ifdef _WIN32
            cout << "    ������" << endl;
#else
            cout << "    ИГРОКИ" << endl;
#endif
            cout << setfill('-') << setw(102) << "-" << endl;
            cout << "|" << "     " << "|" << "      Страна      " << "|" << "       Клуб       " << "|" << "       Имя        " << "|" << "     Фамилия      " << "|" << " Голы " << "|" << " Нарушения " << "|" << endl;
            cout << setfill('-') << setw(102) << "-" << endl;
        }
        cout << "|" << setfill(' ') << setw(4) << i + 1 << " |";
        print_space(strlen_mb(P[i].country));
        cout << P[i].country << " |";
        print_space(strlen_mb(P[i].club));
        cout << P[i].club << " |";
        print_space(strlen_mb(P[i].name.firstname));
        cout << P[i].name.firstname << " |";
        print_space(strlen_mb(P[i].name.lastname ));
        cout << P[i].name.lastname << " |";
        cout << setfill(' ') << setw(5) << P[i].goals << " |";
        cout << setfill(' ') << setw(10) << P[i].fouls << " |";
        cout << endl;
        if (i == len - 1) {
            cout << setfill('-') << setw(102) << "-" << endl;
        }
    }
}

void Input(Football *P,int &len)
{
    int k,l,country,club;

    cout << endl;
#ifdef _WIN32
    cout << "�������� ���������� ������� ��� �����:";
#else
    cout << "Выберите количество игроков для ввода: ";
#endif
    cin >> k;
    cin.get();

    cout << endl;
    for (int i = len, l = k + len; i < l; i++) {
#ifdef _WIN32
        cout << "    ������ ( ";
#else
        cout << "    Страна ( ";
#endif
        for (int j = 0; j < 3; j++) {
            cout << j + 1 << "-" << PlayerCountry[j] << " ";
        }
        cout << "): ";
        cin >> country;
        cin.get();
        P[i].country = PlayerCountry[country - 1];

#ifdef _WIN32
        cout << "    ���� ( ";
#else
        cout << "    Клуб ( ";
#endif
        for (int j = 0; j < 4; j++) {
            cout << j + 1 << "-" << PlayerClub[j] << " ";
        }
        cout << "): ";
        cin >> club;
        cin.get();
        P[i].club = PlayerClub[club - 1];

#ifdef _WIN32
        cout << "    ���: ";
#else
        cout << "    Имя: ";
#endif
        getline(cin,P[i].name.firstname);

#ifdef _WIN32
        cout << "    �������: ";
#else
        cout << "    Фамилия: ";
#endif
        getline(cin,P[i].name.lastname);

#ifdef _WIN32
        cout << "    ����: ";
#else
        cout << "    Голы: ";
#endif
        cin >> P[i].goals;
        cin.get();

#ifdef _WIN32
        cout << "    ���������: ";
#else
        cout << "    Нарушения: ";
#endif
        cin >> P[i].fouls;
        cin.get();

        len++;
    }
    pause();
}

void Sort(Football *P,int &len)
{
    int field = 0,direct = 0;

    if (len == 0) {
        return;
    }

    cout << endl;
#ifdef _WIN32
    cout << "�������� ���� ��� ���������� ( 1-���� 2-��������� ): ";
#else
    cout << "Выберите поле для сортировки ( 1-Голы 2-Нарушения ): ";
#endif
    cin >> field;
    cin.get();

#ifdef _WIN32
    cout << "�������� ����������� ���������� ( 1-�� ����������� 2-�� �������� ): ";
#else
    cout << "Выберите направление сортировки ( 1-По возрастанию 2-По убывания ): ";
#endif
    cin >> direct;
    cin.get();

    switch (field) {
        case GOALS:
            SortGoals(P,len,direct);
            break;
        case FOULS:
            SortFouls(P,len,direct);
            break;
    }
    pause();
}

void Delete(Football *P,int &len)
{
    int k;

    if (len == 0) {
        return;
    }

    cout << endl;
#ifdef _WIN32
    cout << "�������� ������ ��� ��������:";
#else
    cout << "Выберите игрока для удаления: ";
#endif
    cin >> k;
    cin.get();

    if (k < 1 || k > len) {
#ifdef _WIN32
        cout << "������ ������ �� ����������. ���������� ��� ���." << endl;
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

void SortGoals(Football *P,int &len,int direct)
{
    int i,j;
    bool f;
    Football T;

    for (i = len - 1; i >= 0; i--) {
        for (j = 0; j < i; j++) {
            if (direct == 1) {
                f = P[j].goals > P[j + 1].goals;
            } else {
                f = P[j].goals < P[j + 1].goals;
            }
            if (f) {
                T        = P[j];
                P[j]     = P[j + 1];
                P[j + 1] = T;
            }
        }
    }
}

void SortFouls(Football *P,int &len,int direct)
{
    int i,j;
    bool f;
    Football T;

    for (i = len - 1; i >= 0; i--) {
        for (j = 0; j < i; j++) {
            if (direct == 1) {
                f = P[j].fouls > P[j + 1].fouls;
            } else {
                f = P[j].fouls < P[j + 1].fouls;
            }
            if (f) {
                T        = P[j];
                P[j]     = P[j + 1];
                P[j + 1] = T;
            }
        }
    }
}
