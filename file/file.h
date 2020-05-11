#include <iostream>

#pragma pack (push,1)
struct MyContainer {
    int x;
    double y;
    char z[10];
};

struct MyContainerIndex {
    int key;
    int x;
};
#pragma pack (pop)

const int SIZE = 5;

void write(MyContainer *,MyContainerIndex *,int);
void read(MyContainer *,MyContainerIndex *,int);
