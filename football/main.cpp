#include <iostream>
#include <string>

#include "include/struct.h"
#include "include/menu.h"

using namespace std;

int const index = 10;
struct Football P[index] = {};
int len = 0;

int main()
{
    int f;

    do {
        f = Menu(P,len);
    } while (f == 1);

    return 0;
}
