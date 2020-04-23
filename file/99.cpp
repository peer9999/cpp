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
    const int SIZE = 5;

    MyContainer P[SIZE];

    P[0].x = 10;    P[0].y = 9;    strcpy(P[0].z,"qwerty");
    P[1].x = 8;     P[1].y = 7;    strcpy(P[1].z,"asdf");
    P[2].x = 6;     P[2].y = 5;    strcpy(P[2].z,"zxcv");
    P[3].x = 4;     P[3].y = 3;    strcpy(P[3].z,"nm,.");
    P[4].x = 2;     P[4].y = 1;    strcpy(P[4].z,"hjkl;p");

    write(P,SIZE);
    read(P,SIZE);

    for (unsigned i = 0; i < SIZE; i++) {
        cout << P[i].x << ';' << P[i].y << ';' << P[i].z << endl;
    }
}

void write(MyContainer *P,int len)
{
    const char* PATH = "out.bin";
    MyContainer O;
    ofstream fo(PATH,ios::binary);
    fo.write((char*)P,sizeof(O));
    fo.close();
}

void read(MyContainer *P,int len)
{
    const char* PATH = "out.bin";
    MyContainer R;
    ifstream fr(PATH,ios::binary);
    fr.read((char*)P,sizeof(R));
    fr.close();
}
