#include <iostream>
#include <iomanip>
#include <string>
#include <clocale>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <cstring>

#include "include/var.h"
#include "include/struct.h"
#include "include/function.h"

using namespace std;

void Output(Football *P,int &len)
{
    setlocale(LC_ALL,"ru_RU.utf8");
    string note;

    if (len == 0) {
#ifdef _WIN32
        cout << "Äàííûå îá èãðîêàõ îòñóòñòâóþò. Èñïîëüçóéòå ïóíêò \"Ââîä\"." << endl;
#else
        cout << "Ð”Ð°Ð½Ð½Ñ‹Ðµ Ð¾Ð± Ð¸Ð³Ñ€Ð¾ÐºÐ°Ñ… Ð¾Ñ‚ÑÑƒÑ‚ÑÑ‚Ð²ÑƒÑŽÑ‚. Ð˜ÑÐ¿Ð¾Ð»ÑŒÐ·ÑƒÐ¹Ñ‚Ðµ Ð¿ÑƒÐ½ÐºÑ‚ \"Ð’Ð²Ð¾Ð´\"." << endl;
#endif
        return;
    }

#ifdef _WIN32
    cout << "    ÈÃÐÎÊÈ" << endl;
#else
    cout << "    Ð˜Ð“Ð ÐžÐšÐ˜" << endl;
#endif
    cout << setfill('-') << setw(140) << "-" << endl;
    cout << "|" << "     " << "|" << "      Ð¡Ñ‚Ñ€Ð°Ð½Ð°      " << "|" << "       ÐšÐ»ÑƒÐ±       " << "|" << "       Ð˜Ð¼Ñ        " << "|" << "     Ð¤Ð°Ð¼Ð¸Ð»Ð¸Ñ      " << "|" << "      ÐÐ¼Ð¿Ð»ÑƒÐ°      " << "|" << " Ð“Ð¾Ð»Ñ‹ " << "|" << " ÐÐ°Ñ€ÑƒÑˆÐµÐ½Ð¸Ñ " << "|" << "    ÐŸÑ€Ð¸Ð¼ÐµÑ‡Ð°Ð½Ð¸Ñ    " << "|" << endl;
    cout << setfill('-') << setw(140) << "-" << endl;
    for (int i = 0; i < len; i++) {
        cout << "|" << setfill(' ') << setw(4) << i + 1 << " |";
        print_space(strlen_mb(P[i].country));
        cout << P[i].country << " |";
        print_space(strlen_mb(P[i].club));
        cout << P[i].club << " |";
        print_space(strlen_mb(P[i].name.firstname));
        cout << P[i].name.firstname << " |";
        print_space(strlen_mb(P[i].name.lastname));
        cout << P[i].name.lastname << " |";
        print_space(strlen_mb(PlayerPosition[P[i].position - 1]));
        cout << PlayerPosition[P[i].position - 1] << " |";
        cout << setfill(' ') << setw(5) << P[i].goals << " |";
        cout << setfill(' ') << setw(10) << P[i].fouls << " |";
        if (P[i].tag == TYPE_INT) {
            cout << setfill(' ') << setw(17) << P[i].misc.number << " |";
        } else {
            note = P[i].misc.note;
            print_space(strlen_mb(note));
            cout << P[i].misc.note << " |";
        }
        cout << endl;
    }
    cout << setfill('-') << setw(140) << "-" << endl;
}

void Input(Football *P,int &len)
{
    int k,l,country,club,position,goals,fouls;
    char misc[16];

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
        for (int j = 0; j < 2; j++) {
            cout << j + 1 << "-" << PlayerClub[country - 1][j] << " ";
        }
        cout << "): ";
        cin >> club;
        cin.get();
        P[i].club = PlayerClub[country - 1][club - 1];

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
        cout << "    Àìïëóà ( ";
#else
        cout << "    ÐÐ¼Ð¿Ð»ÑƒÐ° ( ";
#endif
        for (int i = 0; i < 4; i++) {
            cout << i + 1 << "-" << PlayerPosition[i] << " ";
        }
        cout << "): ";
        cin >> position;
        cin.get();
        switch (position) {
            case GOALKEEPER:
                P[i].position = GOALKEEPER;
                break;
            case DEFENDER:
                P[i].position = DEFENDER;
                break;
            case MIDFIELDER:
                P[i].position = MIDFIELDER;
                break;
            case ATTACKER:
                P[i].position = ATTACKER;
                break;
        }

#ifdef _WIN32
        cout << "    Ãîëû: ";
#else
        cout << "    Ð“Ð¾Ð»Ñ‹: ";
#endif
        cin >> goals;
        cin.get();
        P[i].goals = goals;

#ifdef _WIN32
        cout << "    Íàðóøåíèÿ: ";
#else
        cout << "    ÐÐ°Ñ€ÑƒÑˆÐµÐ½Ð¸Ñ: ";
#endif
        cin >> fouls;
        cin.get();
        P[i].fouls = fouls;

#ifdef _WIN32
        cout << "    Äîïîëíèòåëüíàÿ èíôîðìàöèÿ: ";
#else
        cout << "    Ð”Ð¾Ð¿Ð¾Ð»Ð½Ð¸Ñ‚ÐµÐ»ÑŒÐ½Ð°Ñ Ð¸Ð½Ñ„Ð¾Ñ€Ð¼Ð°Ñ†Ð¸Ñ: ";
#endif
        cin >> misc;
        cin.get();
        if (isdigit(misc[0])) {
            P[i].misc.number = atoi(misc);
            P[i].tag = TYPE_INT;
        } else {
            strcpy(P[i].misc.note,misc);
            P[i].tag = TYPE_CHAR;
        }

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

void Read(Football *P,int &len)
{
    string line;
    string delimiter = ";";
    string token;
    size_t pos = 0;
    int l;
    ifstream file;
    Football X;

    ifstream file_bin("Out.bin",ios::binary);
    while (file_bin.read((char*) P,sizeof(X))) {
        cout << P->country << endl;
    }
    file_bin.close();

//    P = &X;
//    len = 4;
//    return;

#ifdef _WIN32
    file.open("Out_win.txt");
#else
    file.open("Out.txt");
#endif

    if (file.is_open()) {
        while (getline(file,line)) {
            l = 0;
            while ((pos = line.find(delimiter)) != string::npos) {
                token = line.substr(0,pos);
                switch (l) {
                    case 0:
                        P[len].country = token;
                        break;
                    case 1:
                        P[len].club = token;
                        break;
                    case 2:
                        P[len].name.firstname = token;
                        break;
                    case 3:
                        P[len].name.lastname = token;
                        break;
                    case 4:
                        switch (stoi(token)) {
                            case GOALKEEPER:
                                P[len].position = GOALKEEPER;
                                break;
                            case DEFENDER:
                                P[len].position = DEFENDER;
                                break;
                            case MIDFIELDER:
                                P[len].position = MIDFIELDER;
                                break;
                            case ATTACKER:
                                P[len].position = ATTACKER;
                                break;
                        }
                        break;
                    case 5:
                        P[len].goals = stoi(token);
                        break;
                    case 6:
                        P[len].fouls = stoi(token);
                        break;
                    case 7:
                        if (isdigit(token[0])) {
                            P[len].misc.number = stoi(token);
                            P[len].tag = TYPE_INT;
                        } else {
                            strcpy(P[len].misc.note,token.c_str());
                            P[len].tag = TYPE_CHAR;
                        }
                        break;
                }
                line.erase(0,pos + delimiter.length());
                l++;
            }
            len++;
        }
    }
    file.close();

    pause();
}

void Write(Football *P,int &len)
{
    ofstream file;
    Football X;

    if (len == 0) {
        return;
    }

#ifdef _WIN32
    file.open("Out_win.txt");
#else
    file.open("Out.txt");
#endif

    for (int i = 0; i < len; i++) {
        file << P[i].country << ";" << P[i].club << ";" << P[i].name.firstname << ";" << P[i].name.lastname << ";" << P[i].position << ";" << P[i].goals << ";" << P[i].fouls << ";";
        if (P[i].tag == TYPE_INT) {
            file << P[i].misc.number << ";";
        } else {
            file << P[i].misc.note << ";";
        }
        file << endl;
    }
    file.close();

    ofstream file_bin("Out.bin",ios::binary);
    file_bin.write((char*) P,sizeof(X) * len);
    file_bin.close();

    pause();
}

void Find(Football *P,int &len)
{
    int goals,fouls,index = 0;

    if (len == 0) {
        return;
    }

    goals = P[0].goals;
    fouls = P[0].fouls;
    for (int i = 1; i < len; i++) {
        if (goals < P[i].goals) {
            index = i;
            goals = P[i].goals;
            fouls = P[i].fouls;
        }
    }

    cout << endl;
#ifdef _WIN32
    cout << "Ñàìûé ïîëåçíûé èãðîê: " << endl;
    cout << "    " << P[index].name.firstname << " " << P[index].name.lastname << " èãðàåò çà " << P[index].club << " " << P[index].country << " çàáèë " << P[index].goals << " ãîëîâ" << endl;
#else
    cout << "Ð¡Ð°Ð¼Ñ‹Ð¹ Ð¿Ð¾Ð»ÐµÐ·Ð½Ñ‹Ð¹ Ð¸Ð³Ñ€Ð¾Ðº: " << endl;
    cout << "    " << P[index].name.firstname << " " << P[index].name.lastname << " Ð¸Ð³Ñ€Ð°ÐµÑ‚ Ð·Ð° " << P[index].club << " " << P[index].country << " Ð·Ð°Ð±Ð¸Ð» " << P[index].goals << " Ð³Ð¾Ð»Ð¾Ð²" << endl;
#endif

    pause();
}
