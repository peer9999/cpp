#include <iostream>

#include "include/menu.h"

using namespace std;

void MenuView()
{
#ifdef _WIN32
    system("cls");
    cout << endl << "    ÃËÀÂÍÎÅ ÌÅÍÞ" << endl << "1.Ââîä    " << "2.Ñîðòèðîâêà    " << "3.Óäàëåíèå    " << "4.Íàéòè    " << "5.×òåíèå èç ôàéëà    " << "6.Çàïèñü â ôàéë    " << "0.Âûõîä" << endl << endl;
#else
    system("clear");
    cout << endl << "    Ð“Ð›ÐÐ’ÐÐžÐ• ÐœÐ•ÐÐ®" << endl << "1.Ð’Ð²Ð¾Ð´    " << "2.Ð¡Ð¾Ñ€Ñ‚Ð¸Ñ€Ð¾Ð²ÐºÐ°    " << "3.Ð£Ð´Ð°Ð»ÐµÐ½Ð¸Ðµ    " << "4.ÐÐ°Ð¹Ñ‚Ð¸    " << "5.Ð§Ñ‚ÐµÐ½Ð¸Ðµ Ð¸Ð· Ñ„Ð°Ð¹Ð»Ð°    " << "6.Ð—Ð°Ð¿Ð¸ÑÑŒ Ð² Ñ„Ð°Ð¹Ð»    " << "0.Ð’Ñ‹Ñ…Ð¾Ð´" << endl << endl;
#endif
}

int MenuSelect()
{
    int k = 0;
#ifdef _WIN32
    cout << endl << "Âûáåðèòå äåéñòâèå: ";
#else
    cout << endl << "Ð’Ñ‹Ð±ÐµÑ€Ð¸Ñ‚Ðµ Ð´ÐµÐ¹ÑÑ‚Ð²Ð¸Ðµ: ";
#endif
    cin >> k;
    cin.get();
    return k;
}
