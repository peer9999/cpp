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
        cout << "Äàííûå îòñóòñòâóþò. Èñïîëüçóéòå ñíà÷àëà ââîä äàííûõ." << endl;
#else
        cout << "Ð”Ð°Ð½Ð½Ñ‹Ðµ Ð¾Ð± Ð¸Ð³Ñ€Ð¾ÐºÐ°Ñ… Ð¾Ñ‚ÑÑƒÑ‚ÑÑ‚Ð²ÑƒÑŽÑ‚. Ð˜ÑÐ¿Ð¾Ð»ÑŒÐ·ÑƒÐ¹Ñ‚Ðµ Ð¿ÑƒÐ½ÐºÑ‚ \"Ð’Ð²Ð¾Ð´\"." << endl;
#endif
    }

    cout.fill('_');
    for (int i = 0; i < len; i++) {
        if (!i) {
            cout << "Ð˜Ð“Ð ÐžÐšÐ˜" << endl;
            cout << setw(5) << " " << setw(20) << "Ð¡Ñ‚Ñ€Ð°Ð½Ð°" << "ÐšÐ»ÑƒÐ±" << "Ð˜Ð¼Ñ" << "Ð¤Ð°Ð¼Ð¸Ð»Ð¸Ñ" << endl;
        }
        cout << setw(5) << i + 1 << setw(20) << P[i].country << P[i].club << P[i].name.firstname << P[i].name.lastname << endl;
    }
}

void Input(Football *P,int &len)
{
    int k,l,country,club;

    cout << endl;
#ifdef _WIN32
    cout << "Âûáåðèòå êîëè÷åñòâî èãðîêîâ äëÿ ââîäà:";
#else
    cout << "Ð’Ñ‹Ð±ÐµÑ€Ð¸Ñ‚Ðµ ÐºÐ¾Ð»Ð¸Ñ‡ÐµÑÑ‚Ð²Ð¾ Ð¸Ð³Ñ€Ð¾ÐºÐ¾Ð² Ð´Ð»Ñ Ð²Ð²Ð¾Ð´Ð°:";
#endif
    cin >> k;
    cin.get();

    for (int i = len, l = k + len; i < l; i++) {

#ifdef _WIN32
        cout << "Èìÿ: ";
#else
        cout << "Ð¡Ñ‚Ñ€Ð°Ð½Ð° ( ";
        for (int j = 0; j < 3; j++) {
            cout << j + 1 << "-" << PlayerCountry[j] << " ";
        }
        cout << "): ";
#endif
        cin >> country;
        cin.get();
        P[i].country = PlayerCountry[country - 1];

#ifdef _WIN32
        cout << "Èìÿ: ";
#else
        cout << "ÐšÐ»ÑƒÐ± (  ";
        for (int j = 0; j < 4; j++) {
            cout << j + 1 << "-" << PlayerClub[j] << " ";
        }
        cout << "): ";
#endif
        cin >> club;
        cin.get();
        P[i].club = PlayerClub[club - 1];

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
    cout << "Âûáåðèòå íîìåð èãðîêà äëÿ óäàëåíèÿ:";
#else
    cout << endl << endl << endl << "Ð’Ñ‹Ð±ÐµÑ€Ð¸Ñ‚Ðµ Ð¸Ð³Ñ€Ð¾ÐºÐ° Ð´Ð»Ñ ÑƒÐ´Ð°Ð»ÐµÐ½Ð¸Ñ:";
#endif
    cin >> k;
    cin.get();

    if (k < 1 || k > len) {
#ifdef _WIN32
        cout << "Èãðîêà ñ òàêèì íîìåðîì íå ñóùåñòâóåò. Ïîïðîáóéòå åùå ðàç." << endl;
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
