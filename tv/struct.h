enum SORT {
    SORTSIZE = 1,
    SORTCOST

};

enum TYPE {
    TYPE_INT = 1,
    TYPE_CHAR
};

enum RESOLUTION {
    HIGHDEFENITION = 1,
    FULLHD,
    ULTRAHD4K,
    ULTRAHD8K
};

union MISC {
    int number;
    char note[25];
};

struct TV {
    char country[30];
    char title[30];
    unsigned int size : 6;
    float cost;
    RESOLUTION resolution;
    MISC misc;
    TYPE tag;
};

void Input(TV*,int&);
void Output(TV*,int&);
void Delete(TV*,int&);
void Sort(TV*,int&);
void SortBySize(TV*,int&);
void SortByCost(TV*,int&);
void Analyse(TV*,int&);
void Write(TV*,int&);
void Read(TV*,int&);
void Edit(TV*);
