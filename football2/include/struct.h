#include <iostream>
#include <string>

using namespace std;

struct PlayerName {
    string firstname;
    string lastname;
};

struct Football {
    string country;
    string club;
    struct PlayerName name;
    int goals;
    int fouls;
};

enum Fields {
    GOALS = 1,
    FOULS
};

void Output(Football *,int &);
void Input(Football *,int &);
void Sort(Football *,int &);
void Delete(Football *,int &);
void SortGoals(Football *,int &,int);
void SortFouls(Football *,int &,int);
void Read(Football *,int &);
void Write(Football *,int &);
void Find(Football *,int &);
