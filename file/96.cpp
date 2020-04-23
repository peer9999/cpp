#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

union Misc {
    char note[16];
    int number;
};

enum Type {
    TYPE_CHAR = 1,
    TYPE_INT
};

#pragma pack (push,1)
struct MyContainer
{
    int x;
    double y;
    string z;
    Type tag;
    Misc misc;
    unsigned i : 4;
    unsigned j : 4;
};
#pragma pack (pop)

void write(MyContainer *,int);
void read(MyContainer *,int);

int main()
{
    const char* PATH = "out.bin";
    const int SIZE = 5;

    MyContainer O[SIZE];
    MyContainer R[SIZE];

    O[0].x = 10;    O[0].y = 9;    O[0].z = "qwerty";       O[0].tag = TYPE_CHAR;     strcpy(O[0].misc.note,"asdfdcvv");     O[0].i = 9;     O[0].j = 0;
    O[1].x = 8;     O[1].y = 7;    O[1].z = "asdfg";        O[1].tag = TYPE_INT;      O[1].misc.number = 99;                 O[1].i = 8;     O[1].j = 1;
    O[2].x = 6;     O[2].y = 5;    O[2].z = "zxc";          O[2].tag = TYPE_CHAR;     strcpy(O[2].misc.note,"erety");        O[2].i = 7;     O[2].j = 2;
    O[3].x = 4;     O[3].y = 3;    O[3].z = "ghjt";         O[3].tag = TYPE_INT;      O[3].misc.number = 67;                 O[3].i = 6;     O[3].j = 3;
    O[4].x = 2;     O[4].y = 1;    O[4].z = "vcvbbnnb";     O[4].tag = TYPE_CHAR;     strcpy(O[4].misc.note,"sd");           O[4].i = 5;     O[4].j = 4;

    ofstream fo(PATH,ios::binary);
    fo.write((char*)O,sizeof(O));
    fo.close();

    ifstream fr(PATH,ios::binary);
    fr.read((char*)R,sizeof(R));
    fr.close();

    for (unsigned i = 0; i < SIZE; i++) {
        cout << R[i].x << ';' << R[i].y << ';' << R[i].z << ';' << R[i].tag << ';' << R[i].i << ';' << R[i].j << ';';
        if (R[i].tag == TYPE_CHAR) {
            cout << R[i].misc.note << ';';
        } else {
            cout << R[i].misc.number << ';';
        }
        cout << endl;
    }
}
