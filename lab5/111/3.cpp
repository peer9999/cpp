#include<iostream>
#include <map>      // STL контейнер map
#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    map <char,int> chars;// создаем контейнер
    map <char,int>::iterator begin, at, end;

    char str[500] = "abrakadabra";
//    cout<<"Ввести строку:"<<endl;
//    gets(str);// вводим строку

    for (unsigned int i = 0; i < strlen(str); i++) {
        chars[str[i]]++;// считаем каждый символ
    }

    begin = chars.begin();
    end   = chars.end();
    for (at = begin; at != end; at++) {
        cout << at->first << ' ' << at->second << endl; // выводим результат
    }
    return 0;
}
