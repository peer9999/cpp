#include <iostream>
#include <string>

#include "struct.h"
#include "menu.h"

using namespace std;

int Menu(struct Football *P,int index)
{
    int k;

    cout << endl;
#ifdef _WIN32
//    system("cls");
    cout << "Ãëàâíîå ìåíþ" << endl;
    cout << "1. Ââîä äàííûõ" << endl;
    cout << "2. Âûâîä äàííûõ" << endl;
    cout << "3. Óäàëåíèå äàííûõ" << endl;
    cout << "0. Âûõîä èç ïðîãðàììû" << endl << endl;
    cout << "Âûáåðèòå äåéñòâèå:";
#else
//    system("clear");
    cout << "Ð“Ð»Ð°Ð²Ð½Ð¾Ðµ Ð¼ÐµÐ½ÑŽ" << endl;
    cout << "1. Ð’Ð²Ð¾Ð´ Ð´Ð°Ð½Ð½Ñ‹Ñ…" << endl;
    cout << "2. Ð’Ñ‹Ð²Ð¾Ð´ Ð´Ð°Ð½Ð½Ñ‹Ñ…" << endl;
    cout << "3. Ð£Ð´Ð°Ð»ÐµÐ½Ð¸Ðµ Ð´Ð°Ð½Ð½Ñ‹Ñ…" << endl;
    cout << "0. Ð’Ñ‹Ñ…Ð¾Ð´ Ð¸Ð· Ð¿Ñ€Ð¾Ð³Ñ€Ð°Ð¼Ð¼Ñ‹" << endl << endl;
    cout << "Ð’Ñ‹Ð±ÐµÑ€Ð¸Ñ‚Ðµ Ð´ÐµÐ¹ÑÑ‚Ð²Ð¸Ðµ:";
#endif
    cin >> k;
    cin.get();

    switch (k) {
        case 1:
            Input(P,index);
            break;
        case 2:
            Output(P,index);
            break;
        case 3:
            break;
        case 0:
            return 0;
    }
    return 1;
}
