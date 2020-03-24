#include <iostream>
#include <string>

using namespace std;

struct PlayerName {
    string firstname;
    string lastname;
};

struct Football {
//    enum PlayerCountry country;
//    enum PlayerClub club;
    struct PlayerName name;
    int goals;
    int fouls;
};

void Output(Football *,int &);
void Input(Football *,int &);
void Sort(Football *,int &);
void Delete(Football *,int &);
