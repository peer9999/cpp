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
    cout << "Ââîä äàííûõ" << endl;
    cout << "Âûáåðèòå êîëè÷åñòâî èãðîêîâ äëÿ ââîäà:";
#else
    system("clear");
    cout << "Ð’Ð²Ð¾Ð´ Ð´Ð°Ð½Ð½Ñ‹Ñ…" << endl;
    cout << "Ð’Ñ‹Ð±ÐµÑ€Ð¸Ñ‚Ðµ ÐºÐ¾Ð»Ð¸Ñ‡ÐµÑÑ‚Ð²Ð¾ Ð¸Ð³Ñ€Ð¾ÐºÐ¾Ð² Ð´Ð»Ñ Ð²Ð²Ð¾Ð´Ð°:";
#endif
    cin >> k;
    cin.get();

    for (int i = len, l = k + len; i < l; i++) {
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

void Output(struct Football *P,int &len,bool view)
{
    cout << endl;
#ifdef _WIN32
    system("cls");
    cout << "Âûâîä äàííûõ" << endl;
#else
    system("clear");
    cout << "Ð’Ñ‹Ð²Ð¾Ð´ Ð´Ð°Ð½Ð½Ñ‹Ñ…" << endl;
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
        cout << "Äàííûå îòñóòñòâóþò. Èñïîëüçóéòå ñíà÷àëà ââîä äàííûõ." << endl;
#else
        system("clear");
        cout << "Ð”Ð°Ð½Ð½Ñ‹Ðµ Ð¾Ñ‚ÑÑƒÑ‚ÑÑ‚Ð²ÑƒÑŽÑ‚. Ð˜ÑÐ¿Ð¾Ð»ÑŒÐ·ÑƒÐ¹Ñ‚Ðµ ÑÐ½Ð°Ñ‡Ð°Ð»Ð° Ð²Ð²Ð¾Ð´ Ð´Ð°Ð½Ð½Ñ‹Ñ…." << endl;
#endif
        pause();
        return;
    }

    Output(P,len,false);

    do {
        cout << endl;
#ifdef _WIN32
        cout << "Óäàëåíèå äàííûõ" << endl;
        cout << "Âûáåðèòå íîìåð èãðîêà äëÿ óäàëåíèÿ:";
#else
        cout << "Ð£Ð´Ð°Ð»ÐµÐ½Ð¸Ðµ Ð´Ð°Ð½Ð½Ñ‹Ñ…" << endl;
        cout << "Ð’Ñ‹Ð±ÐµÑ€Ð¸Ñ‚Ðµ Ð½Ð¾Ð¼ÐµÑ€ Ð¸Ð³Ñ€Ð¾ÐºÐ° Ð´Ð»Ñ ÑƒÐ´Ð°Ð»ÐµÐ½Ð¸Ñ:";
#endif
        cin >> k;
        cin.get();

        if (k < 1 || k > len) {
#ifdef _WIN32
            cout << "Èãðîêà ñ òàêèì íîìåðîì íå ñóùåñòâóåò. Ïîïðîáóéòå åùå ðàç." << endl;
#else
            cout << "Ð˜Ð³Ñ€Ð¾ÐºÐ° Ñ Ñ‚Ð°ÐºÐ¸Ð¼ Ð½Ð¾Ð¼ÐµÑ€Ð¾Ð¼ Ð½Ðµ ÑÑƒÑ‰ÐµÑÑ‚Ð²ÑƒÐµÑ‚. ÐŸÐ¾Ð¿Ñ€Ð¾Ð±ÑƒÐ¹Ñ‚Ðµ ÐµÑ‰Ðµ Ñ€Ð°Ð·." << endl;
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
