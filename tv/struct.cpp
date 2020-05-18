#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>
#include "struct.h"

using namespace std;

void Input(TV *tv,int &len)
{
    int i,k,l = len,temp;
    char misc[25];

    cout << "Количество телевизоров: ";
    cin >> k;
    cin.get();

    for (i = l; i < k + l; i++, len++) {
        cout << i + 1 << "." << setw(2) << "Название: ";
        cin.getline(tv[i].title,30);

        cout << setw(2) << "Страна производитель: ";
        cin.getline(tv[i].country,30);

        cout << setw(2) << "Цена: ";
        cin >> temp;
        tv[i].cost = temp;
        cin.get();

        cout << setw(2) << "Размер по диагонали: ";
        cin >> temp;
        tv[i].size = temp;
        cin.get();

        cout << "Разрешение экрана (1 - HD, 2 - FullHD, 3 - 4k UHD, 4 - 8k UHD): ";
        cin >> temp;
        cin.get();
        switch (temp) {
            case HIGHDEFENITION:
                tv[i].resolution = HIGHDEFENITION;
                break;
            case FULLHD:
                tv[i].resolution = FULLHD;
                break;
            case ULTRAHD4K:
                tv[i].resolution = ULTRAHD4K;
                break;
            case ULTRAHD8K:
                tv[i].resolution = ULTRAHD8K;
                break;
        }

        cout << "Дополнительная информация: ";
        cin.get(misc,25);
        cin.get();
        if (isdigit(misc[0])) {
            tv[i].misc.number = atoi(misc);
            tv[i].tag = TYPE_INT;
        } else {
            strcpy(tv[i].misc.note,misc);
            tv[i].tag = TYPE_CHAR;
        }
    }
}

void Edit(TV *tv)
{
    int i;
    char temp[30];
    char misc[25];

    cout << "Введите поле для изменения: ";
    cin >> i;
    cin.get();

    cout << i << "." << setw(2) << "Название: ";
    cin.getline(temp,30);
    if (temp[0] != '\0') {
        strcpy(tv[i - 1].title,temp);
    }

    cout << setw(2) << "Страна производитель: ";
    cin.getline(temp,30);
    if (temp[0] != '\0') {
        strcpy(tv[i - 1].country,temp);
    }

    cout << setw(2) << "Цена: ";
    cin.getline(temp,30);
    if (temp[0] != '\0') {
        tv[i - 1].cost = atoi(temp);
    }

    cout << setw(2) << "Размер по диагонали: ";
    cin.getline(temp,30);
    if (temp[0] != '\0') {
        tv[i - 1].size = atoi(temp);
    }

//    cout << "Разрешение экрана (1 - HD, 2 - FullHD, 3 - 4k UHD, 4 - 8k UHD): ";
//    cin.getline(temp,30);

/*
    if (temp[0] != '\0') {
        switch (atoi(temp)) {
            case HIGHDEFENITION:
                tv[i - 1].resolution = HIGHDEFENITION;
                break;
            case FULLHD:
                tv[i - 1].resolution = FULLHD;
                break;
            case ULTRAHD4K:
                tv[i - 1].resolution = ULTRAHD4K;
                break;
            case ULTRAHD8K:
                tv[i - 1].resolution = ULTRAHD8K;
                break;
        }
    }
*/
    cout << "Дополнительная информация: ";
    cin.get(misc,25);
    cin.get();
    if (misc[0] != '\0') {
        if (isdigit(misc[0])) {
            tv[i - 1].misc.number = atoi(misc);
            tv[i - 1].tag = TYPE_INT;
        } else {
            strcpy(tv[i - 1].misc.note,misc);
            tv[i - 1].tag = TYPE_CHAR;
        }
    }
}

void Output(TV *tv,int &len)
{
    char resolution[4][25] = {
        "High Definition(HD)",
        "FullHD",
        "4K(Ultra HD)",
        "8k(Ultra HD)"
    };
    int i;
    if (len == 0) {
        cout << endl << endl << "Данные отсутствуют! Используйте операцию \"Ввод\"";
        return;
    }

    cout << setfill('-') << setw(125) << "-" << endl;
    cout << setfill(' ') << "|      |"
        << setw(20) << "Название" << " |"
        << setw(10) << "Страна производитель" << " |"
        << setw(9)  << "Цена" << " |"
        << setw(13) << "Размер по диагонали" << " |"
        << setw(20) << "Разрешение" << " |"
        << setw(17) << "Доп.информация" << " |" << endl;
    cout << setfill('-') << setw(125) << "-" << endl;
    for (i = 0; i < len; i++) {
        cout << setfill(' ')
            << "|" << setw(4) << i + 1 << "." << " |"
            << setw(20) << tv[i].title << " |"
            << setw(20) << tv[i].country << " |"
            << setw(9) << tv[i].cost << " |"
            << setw(19) << tv[i].size << " |"
            << setw(20) << resolution[tv[i].resolution - 1] << " |";
        if (tv[i].tag == TYPE_INT) {
            cout << setw(17) << tv[i].misc.number << " |" << endl;
        } else {
            cout << setw(17) << tv[i].misc.note << " |" << endl;
        }
    }
    cout << setfill('-') << setw(125) << "-" << endl;
}

void Delete(TV *tv,int &len)
{
    int z;

    cout << "Введите номер поля для удаления: ";
    cin >> z;
    cin.get();
    for (int i = z - 1; i < len; i++) {
        tv[i] = tv[i + 1];
    }
    len--;
}

void Sort(TV *tv,int &len)
{
    int x;

    cout << "1.По цене" << endl;
    cout << "2.По размеру" << endl;
    cin >> x;
    cin.get();

    switch (x) {
        case SORTSIZE:
            SortBySize(tv,len);
            break;
        case SORTCOST:
            SortByCost(tv,len);
            break;
    }
}

void SortBySize(TV *tv,int &len)
{
    TV temp;

    for (int i = 0; i < len; i++) {
        for (int j = len - 1; j > i; j--) {
            if (tv[j - 1].size > tv[j].size) {
                temp      = tv[j - 1];
                tv[j - 1] = tv[j];
                tv[j]     = temp;
            }
        }
    }
}

void SortByCost(TV *tv, int &len)
{
    TV temp;

    for (int i = 0; i < len; i++) {
        for (int j = len - 1; j > i; j--) {
            if (tv[j - 1].cost > tv[j].cost) {
                temp      = tv[j - 1];
                tv[j - 1] = tv[j];
                tv[j]     = temp;
            }
        }
    }
}

void Analyse(TV *tv, int &len)
{
    int max,i,j = 0;

    max = tv[0].size;
    for (i = 1; i < len; i++) {
        if (max < tv[i].size) {
            j = i;
            max = tv[i].size;
        }
    }

    cout << endl << "Лучший телевизор "
        << tv[j].title << ", " << " стоимость  "
        << tv[j].cost << ", "
        << tv[j].size << " - " << " размер по диагонали " << endl << endl;
    system("pause");
}

void Write(TV *tv,int &len)
{
    ofstream file;
    const char* OUT_FILE = "Out.txt";

    if (len == 0) {
        return;
    }

    file.open(OUT_FILE);
    for (int i = 0; i < len; i++) {
        file << tv[i].title << ";" << tv[i].country << ";" << tv[i].cost << ";" << tv[i].size << ";" << tv[i].resolution << ";";
        if (tv[i].tag == TYPE_INT) {
            file << tv[i].misc.number << ";";
        } else {
            file << tv[i].misc.note << ";";
        }
        file << endl;
    }
    file.close();
}

void Read(TV *tv,int &len)
{
    char line[256];
    char delimiter[] = ";";
    char* token;
    int l;
    ifstream file;
    const char* OUT_FILE = "Out.txt";

    file.open(OUT_FILE);
    if (file.is_open()) {
        while (file.getline(line,256)) {
            token = strtok(line,delimiter);
            l = 0;
            while (token != NULL) {
                switch (l) {
                    case 0:
                        strcpy(tv[len].title,token);
                        break;
                    case 1:
                        strcpy(tv[len].country,token);
                        break;
                    case 2:
                        tv[len].cost = atoi(token);
                        break;
                    case 3:
                        tv[len].size = atoi(token);
                        break;
                    case 4:
                        switch (atoi(token)) {
                            case HIGHDEFENITION:
                            tv[len].resolution = HIGHDEFENITION;
                            break;
                        case FULLHD:
                            tv[len].resolution = FULLHD;
                            break;
                        case ULTRAHD4K:
                            tv[len].resolution = ULTRAHD4K;
                            break;
                        case ULTRAHD8K:
                            tv[len].resolution = ULTRAHD8K;
                            break;
                        }
                        break;
                    case 5:
                        if (isdigit(token[0])) {
                            tv[len].misc.number = atoi(token);
                            tv[len].tag = TYPE_INT;
                        } else {
                            strcpy(tv[len].misc.note,token);
                            tv[len].tag = TYPE_CHAR;
                        }
                        break;
                }
                l++;
                token = strtok(NULL,delimiter);
            }
            len++;
        }
    }
    file.close();
}
