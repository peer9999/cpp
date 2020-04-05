#include <iostream>
#include <string>

using namespace std;

struct PlayerName {
    string firstname;  // имя
    string lastname;   // фамилия
};

union Misc {
    char note[16];  // примечание
    int number;     // номер на майке
};

enum Position {
    GOALKEEPER = 1,
    DEFENDER,
    MIDFIELDER,
    ATTACKER
};

enum Fields {
    GOALS = 1,
    FOULS
};

enum Type {
    TYPE_CHAR = 1,
    TYPE_INT
};

struct Football {
    string country;          // страна
    string club;             // клуб
    struct PlayerName name;  // фио
    unsigned goals : 5;      // голы
    unsigned fouls : 5;      // нарушения
    enum Position position;  // амплуа
    union Misc misc;         // разное
    enum Type tag;           // тип данных в поле разное
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
void Filter(Football *,int &);
