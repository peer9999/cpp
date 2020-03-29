#include <iostream>
#include <string>

#include "include/struct.h"
#include "include/menu.h"

using namespace std;

int main()
{
    int len = 0;
    int selection;
    int const index = 10;
    Football P[index] = {};

    do {
        MenuView();
        Output(P,len);
        switch (selection) {
            case INPUT:
                Input(P,len);
                selection = 1001;
                break;
            case SORT:
                Sort(P,len);
                selection = 1002;
                break;
            case DELETE:
                Delete(P,len);
                selection = 1003;
                break;
            case FIND:
                Find(P,len);
                selection = 1004;
                break;
            case READ:
                Read(P,len);
                selection = 1005;
                break;
            case WRITE:
                Write(P,len);
                selection = 1006;
                break;
            default:
                selection = MenuSelect();
                break;
        }
    } while (selection > 0);
    return 0;
}
