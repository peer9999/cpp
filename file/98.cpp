#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#pragma pack (push,1)
struct MyContainer
{
    int x;
    double y;
    char z[10];
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

    O[0].x = 10;    O[0].y = 9;    strcpy(O[0].z,"йцукен");
    O[1].x = 8;     O[1].y = 7;    strcpy(O[1].z,"фывап");
    O[2].x = 6;     O[2].y = 5;    strcpy(O[2].z,"ячс");
    O[3].x = 4;     O[3].y = 3;    strcpy(O[3].z,"мить");
    O[4].x = 2;     O[4].y = 1;    strcpy(O[4].z,"ролджэъх");

cout << sizeof(O) << endl;

    ofstream fo(PATH,ios::binary);
    fo.write((char*)O,sizeof(O));
    fo.close();

    ifstream fr(PATH,ios::binary);
    fr.read((char*)R,sizeof(R));
    fr.close();

    for (unsigned i = 0; i < SIZE; i++) {
        cout << R[i].x << ';' << R[i].y << ';' << R[i].z << endl;
    }
}
