#include <iostream>
#include <string>

#include "struct.h"

using namespace std;

void Input(struct Football *P,int index)
{
    cout << endl;
#ifdef _WIN32
    system("cls");
    cout << "Ââîä äàííûõ" << endl;
#else
//    system("clear");
    cout << "Ð’Ð²Ð¾Ð´ Ð´Ð°Ð½Ð½Ñ‹Ñ…" << endl;
#endif

    for (int i = 0; i < index; i++) {
#ifdef _WIN32
        cout << "Èìÿ: ";
#else
        cout << "Ð˜Ð¼Ñ: ";
#endif
        getline(cin,P[i].name.firstname);

#ifdef _WIN32
        cout << "Ôàìèëèÿ: ";
#else
        cout << "Ð¤Ð°Ð¼Ð¸Ð»Ð¸Ñ: ";
#endif
        getline(cin,P[i].name.lastname);
    }
}

void Output(struct Football *P,int index)
{
    cout << endl;
#ifdef _WIN32
    system("cls");
    cout << "Âûâîä äàííûõ" << endl;
#else
//    system("clear");
    cout << "Ð’Ñ‹Ð²Ð¾Ð´ Ð´Ð°Ð½Ð½Ñ‹Ñ…" << endl;
#endif

    for (int i = 0; i < index; i++) {
        cout << P[i].name.firstname << " " << P[i].name.lastname << endl;
    }
}
