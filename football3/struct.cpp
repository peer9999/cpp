#include <iostream>
#include <iomanip>
#include <string>
#include <clocale>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <cstring>

#include "include/struct_var.h"
#include "include/struct.h"
#include "include/function.h"

using namespace std;

void Output(Football *P,int &len)
{
    setlocale(LC_ALL,"ru_RU.utf8");
    string temp;

    if (len == 0) {
        cout << EmptyTable << endl;
        return;
    }

    cout << TitleTable << endl;
    cout << setfill('-') << setw(140) << "-" << endl;
    for (int i = 0; i < ColumnTableCount; i++) {
        cout << ColumnTable[i];
    }
    cout << endl;
    cout << setfill('-') << setw(140) << "-" << endl;
    for (int i = 0; i < len; i++) {
        cout << "|" << setfill(' ') << setw(4) << i + 1 << " |";
        temp = P[i].country;
        print_space(strlen_mb(temp));
        cout << P[i].country << " |";
        temp = P[i].club;
        print_space(strlen_mb(temp));
        cout << P[i].club << " |";
        temp = P[i].name.firstname;
        print_space(strlen_mb(temp));
        cout << P[i].name.firstname << " |";
        temp = P[i].name.lastname;
        print_space(strlen_mb(temp));
        cout << P[i].name.lastname << " |";
        print_space(strlen_mb(PlayerPosition[P[i].position - 1]));
        cout << PlayerPosition[P[i].position - 1] << " |";
        cout << setfill(' ') << setw(5) << P[i].goals << " |";
        cout << setfill(' ') << setw(10) << P[i].fouls << " |";
        if (P[i].tag == TYPE_INT) {
            cout << setfill(' ') << setw(17) << P[i].misc.number << " |";
        } else {
            temp = P[i].misc.note;
            print_space(strlen_mb(temp));
            cout << P[i].misc.note << " |";
        }
        cout << endl;
    }
    cout << setfill('-') << setw(140) << "-" << endl;
}

void Input(Football *P,int &len)
{
    int k,l,country,club,position,goals,fouls;
    char misc[16],temp[30];

    cout << endl << AddPlayer;
    cin >> k;
    cin.get();

    cout << endl;
    for (int i = len, l = k + len; i < l; i++) {
        cout << Country;
        for (int j = 0; j < 3; j++) {
            cout << j + 1 << "-" << PlayerCountry[j] << " ";
        }
        cout << RightBracket;
        cin >> country;
        cin.get();
        strcpy(P[i].country,PlayerCountry[country - 1].c_str());

        cout << Club;
        for (int j = 0; j < 2; j++) {
            cout << j + 1 << "-" << PlayerClub[country - 1][j] << " ";
        }
        cout << RightBracket;
        cin >> club;
        cin.get();
        strcpy(P[i].club,PlayerClub[country - 1][club - 1].c_str());

        cout << Firstname;
        cin >> temp;
        cin.get();
        strcpy(P[i].name.firstname,temp);

        cout << Lastname;
        cin >> temp;
        cin.get();
        strcpy(P[i].name.lastname,temp);


        cout << Position;
        for (int i = 0; i < 4; i++) {
            cout << i + 1 << "-" << PlayerPosition[i] << " ";
        }
        cout << RightBracket;
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

        cout << Goals;
        cin >> goals;
        cin.get();
        P[i].goals = goals;

        cout << Fouls;
        cin >> fouls;
        cin.get();
        P[i].fouls = fouls;

        cout << Misc;
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

    cout << endl << SortField;
    cin >> field;
    cin.get();

    cout << SortDirect;
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

    cout << endl << DeletePlayer;
    cin >> k;
    cin.get();

    if (k < 1 || k > len) {
        cout << NotExist << endl;
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

    file.open(OUT_FILE);
    if (file.is_open()) {
        while (getline(file,line)) {
            l = 0;
            while ((pos = line.find(delimiter)) != string::npos) {
                token = line.substr(0,pos);
                switch (l) {
                    case 0:
                        strcpy(P[len].country,token.c_str());
                        break;
                    case 1:
                        strcpy(P[len].club,token.c_str());
                        break;
                    case 2:
                        strcpy(P[len].name.firstname,token.c_str());
                        break;
                    case 3:
                        strcpy(P[len].name.lastname,token.c_str());
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

void Read_binary(Football *P,int &len)
{
    ifstream file;

    file.open("Out.bin",ios::binary);
    file.read((char*)&len,sizeof(len));

    Football X[len];

    file.seekg(4,ios::beg);
    file.read((char*)P,sizeof(X));
    file.close();

    pause();
}

void Write(Football *P,int &len)
{
    ofstream file;

    if (len == 0) {
        return;
    }

    file.open(OUT_FILE);
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

    pause();
}

void Write_binary(Football *P,int &len)
{
    ofstream file;

    if (len == 0) {
        return;
    }

    Football X[len];

    file.open("Out.bin",ios::binary);
    file.write((char*)&len,sizeof(len));
    file.write((char*)P,sizeof(X));
    file.close();
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

    cout << endl << GoodPlayer << endl << "    " << P[index].name.firstname << " " << P[index].name.lastname << PlaysFor << P[index].club << " " << P[index].country << Scored << P[index].goals << fGoals << endl;
    pause();
}
