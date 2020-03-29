#include <iostream>
#include <string>

using namespace std;

struct PlayerName {
    string firstname;  // имя
    string lastname;   // фамилия
};

union Misc {
    int number;     // номер на майке
    char note[16];  // примечание
};

enum Position {
    GOALKEEPER,
    DEFENDER,
    MIDFIELDER,
    ATTACKER
};

enum Fields {
    GOALS = 1,
    FOULS
};

struct Football {
    string country;          // страна
    string club;             // клуб
    struct PlayerName name;  // фио
    unsigned goals : 5;      // голы
    unsigned fouls : 5;      // нарушения
    enum Position position;  // амплуа
    union Misc misc;         // разное
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
