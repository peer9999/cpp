#include <iostream>
#include <string>

#include "include/struct.h"
#include "include/menu.h"

using namespace std;

int len = 0;
int const index = 10;
Football P[index] = {};

int main()
{
    int f;

    setlocale(LC_ALL,"");

    do {
        MenuView();
        Output(P,len);
        switch (f) {
            case 1:
                Input(P,len);
                f = 1000;
                break;
            case 2:
                Sort(P,len);
                f = 1000;
                break;
            case 3:
                Delete(P,len);
                f = 1000;
                break;
            default:
                f = MenuSelect();
                break;
        }
    } while (f > 0);

    return 0;
}
