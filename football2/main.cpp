#include <iostream>
#include <string>

#include "include/struct.h"
#include "include/menu.h"
#include "include/var.h"

using namespace std;

int main()
{
    int f;

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
