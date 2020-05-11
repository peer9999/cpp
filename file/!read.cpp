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

    read(P,SIZE);

    for (unsigned i = 0; i < SIZE; i++) {
        cout << P[i].x << ';' << P[i].y << ';' << P[i].z << endl;
    }
}

void write(MyContainer *P,int len)
{
    const char* PATH = "out.bin";
    MyContainer O[len];
    ofstream fo(PATH,ios::binary);
    fo.write((char*)P,sizeof(O));
    fo.close();
}

void read(MyContainer *P,int len)
{
    const char* PATH = "out.bin";
    MyContainer R[len];
    ifstream fr(PATH,ios::binary);
    fr.read((char*)P,sizeof(R));
    fr.close();
}
