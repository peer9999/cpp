#include <iostream>
#include <string>

using namespace std;

#pragma pack (push,1)
struct PlayerName {
    char firstname[30];  // имя
    char lastname[30];   // фамилия
};
#pragma pack (pop)

#pragma pack (push,1)
union Misc {
    char note[16];  // примечание
    int number;     // номер на майке
};
#pragma pack (pop)

#pragma pack (push,1)
enum Position {
    GOALKEEPER = 1,
    DEFENDER,
    MIDFIELDER,
    ATTACKER
};
#pragma pack (pop)

#pragma pack (push,1)
enum Fields {
    GOALS = 1,
    FOULS
};
#pragma pack (pop)

#pragma pack (push,1)
enum Type {
    TYPE_CHAR = 1,
    TYPE_INT
};
#pragma pack (pop)

#pragma pack (push,1)
struct Football {
    char country[30];        // страна
    char club[30];           // клуб
    struct PlayerName name;  // фио
    unsigned goals : 5;      // голы
    unsigned fouls : 5;      // нарушения
    enum Position position;  // амплуа
    union Misc misc;         // разное
    enum Type tag;           // тип данных в поле разное
};
#pragma pack (pop)

void Output(Football *,int &);
void Input(Football *,int &);
void Sort(Football *,int &);
void Delete(Football *,int &);
void SortGoals(Football *,int &,int);
void SortFouls(Football *,int &,int);
void Read(Football *,int &);
void Read_binary(Football *,int &);
void Write(Football *,int &);
void Write_binary(Football *,int &);
void Find(Football *,int &);
void Filter(Football *,int &);
