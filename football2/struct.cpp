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
        cout << "Äàííûå îá èãðîêàõ îòñóòñòâóþò. Èñïîëüçóéòå ïóíêò \"Ââîä\"." << endl;
#else
        cout << "Ð”Ð°Ð½Ð½Ñ‹Ðµ Ð¾Ð± Ð¸Ð³Ñ€Ð¾ÐºÐ°Ñ… Ð¾Ñ‚ÑÑƒÑ‚ÑÑ‚Ð²ÑƒÑŽÑ‚. Ð˜ÑÐ¿Ð¾Ð»ÑŒÐ·ÑƒÐ¹Ñ‚Ðµ Ð¿ÑƒÐ½ÐºÑ‚ \"Ð’Ð²Ð¾Ð´\"." << endl;
#endif
        return;
    }

    for (int i = 0; i < len; i++) {
        if (!i) {
#ifdef _WIN32
            cout << "    ÈÃÐÎÊÈ" << endl;
#else
            cout << "    Ð˜Ð“Ð ÐžÐšÐ˜" << endl;
#endif
            cout << setfill('-') << setw(102) << "-" << endl;
            cout << "|" << "     " << "|" << "      Ð¡Ñ‚Ñ€Ð°Ð½Ð°      " << "|" << "       ÐšÐ»ÑƒÐ±       " << "|" << "       Ð˜Ð¼Ñ        " << "|" << "     Ð¤Ð°Ð¼Ð¸Ð»Ð¸Ñ      " << "|" << " Ð“Ð¾Ð»Ñ‹ " << "|" << " ÐÐ°Ñ€ÑƒÑˆÐµÐ½Ð¸Ñ " << "|" << endl;
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
    cout << "Âûáåðèòå êîëè÷åñòâî èãðîêîâ äëÿ ââîäà:";
#else
    cout << "Ð’Ñ‹Ð±ÐµÑ€Ð¸Ñ‚Ðµ ÐºÐ¾Ð»Ð¸Ñ‡ÐµÑÑ‚Ð²Ð¾ Ð¸Ð³Ñ€Ð¾ÐºÐ¾Ð² Ð´Ð»Ñ Ð²Ð²Ð¾Ð´Ð°: ";
#endif
    cin >> k;
    cin.get();

    cout << endl;
    for (int i = len, l = k + len; i < l; i++) {
#ifdef _WIN32
        cout << "    Ñòðàíà ( ";
#else
        cout << "    Ð¡Ñ‚Ñ€Ð°Ð½Ð° ( ";
#endif
        for (int j = 0; j < 3; j++) {
            cout << j + 1 << "-" << PlayerCountry[j] << " ";
        }
        cout << "): ";
        cin >> country;
        cin.get();
        P[i].country = PlayerCountry[country - 1];

#ifdef _WIN32
        cout << "    Êëóá ( ";
#else
        cout << "    ÐšÐ»ÑƒÐ± ( ";
#endif
        for (int j = 0; j < 4; j++) {
            cout << j + 1 << "-" << PlayerClub[j] << " ";
        }
        cout << "): ";
        cin >> club;
        cin.get();
        P[i].club = PlayerClub[club - 1];

#ifdef _WIN32
        cout << "    Èìÿ: ";
#else
        cout << "    Ð˜Ð¼Ñ: ";
#endif
        getline(cin,P[i].name.firstname);

#ifdef _WIN32
        cout << "    Ôàìèëèÿ: ";
#else
        cout << "    Ð¤Ð°Ð¼Ð¸Ð»Ð¸Ñ: ";
#endif
        getline(cin,P[i].name.lastname);

#ifdef _WIN32
        cout << "    Ãîëû: ";
#else
        cout << "    Ð“Ð¾Ð»Ñ‹: ";
#endif
        cin >> P[i].goals;
        cin.get();

#ifdef _WIN32
        cout << "    Íàðóøåíèÿ: ";
#else
        cout << "    ÐÐ°Ñ€ÑƒÑˆÐµÐ½Ð¸Ñ: ";
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
    cout << "Âûáåðèòå ïîëå äëÿ ñîðòèðîâêè ( 1-Ãîëû 2-Íàðóøåíèÿ ): ";
#else
    cout << "Ð’Ñ‹Ð±ÐµÑ€Ð¸Ñ‚Ðµ Ð¿Ð¾Ð»Ðµ Ð´Ð»Ñ ÑÐ¾Ñ€Ñ‚Ð¸Ñ€Ð¾Ð²ÐºÐ¸ ( 1-Ð“Ð¾Ð»Ñ‹ 2-ÐÐ°Ñ€ÑƒÑˆÐµÐ½Ð¸Ñ ): ";
#endif
    cin >> field;
    cin.get();

#ifdef _WIN32
    cout << "Âûáåðèòå íàïðàâëåíèå ñîðòèðîâêè ( 1-Ïî âîçðàñòàíèþ 2-Ïî óáûâàíèÿ ): ";
#else
    cout << "Ð’Ñ‹Ð±ÐµÑ€Ð¸Ñ‚Ðµ Ð½Ð°Ð¿Ñ€Ð°Ð²Ð»ÐµÐ½Ð¸Ðµ ÑÐ¾Ñ€Ñ‚Ð¸Ñ€Ð¾Ð²ÐºÐ¸ ( 1-ÐŸÐ¾ Ð²Ð¾Ð·Ñ€Ð°ÑÑ‚Ð°Ð½Ð¸ÑŽ 2-ÐŸÐ¾ ÑƒÐ±Ñ‹Ð²Ð°Ð½Ð¸Ñ ): ";
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
    cout << "Âûáåðèòå èãðîêà äëÿ óäàëåíèÿ:";
#else
    cout << "Ð’Ñ‹Ð±ÐµÑ€Ð¸Ñ‚Ðµ Ð¸Ð³Ñ€Ð¾ÐºÐ° Ð´Ð»Ñ ÑƒÐ´Ð°Ð»ÐµÐ½Ð¸Ñ: ";
#endif
    cin >> k;
    cin.get();

    if (k < 1 || k > len) {
#ifdef _WIN32
        cout << "Òàêîãî èãðîêà íå ñóùåñòâóåò. Ïîïðîáóéòå åùå ðàç." << endl;
#else
        cout << "Ð¢Ð°ÐºÐ¾Ð³Ð¾ Ð¸Ð³Ñ€Ð¾ÐºÐ° Ð½Ðµ ÑÑƒÑ‰ÐµÑÑ‚Ð²ÑƒÐµÑ‚. ÐŸÐ¾Ð¿Ñ€Ð¾Ð±ÑƒÐ¹Ñ‚Ðµ ÐµÑ‰Ðµ Ñ€Ð°Ð·." << endl;
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
