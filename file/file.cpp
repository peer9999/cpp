#include <iostream>
#include <fstream>

#include "file.h"

using namespace std;

void write(MyContainer *P,MyContainerIndex *I,int len)
{
    ofstream f;
    f.open("out.bin",ios::binary);
    f.write((char*)P,sizeof(MyContainer) * len);
    f.close();
    f.open("out.idx",ios::binary);
    f.write((char*)I,sizeof(MyContainerIndex) * len);
    f.close();
}

void read(MyContainer *P,MyContainerIndex *I,int len)
{
    ifstream f;
    f.open("out.bin",ios::binary);
    f.read((char*)P,sizeof(MyContainer) * len);
    f.close();
    f.open("out.idx",ios::binary);
    f.read((char*)I,sizeof(MyContainerIndex) * len);
    f.close();
}
