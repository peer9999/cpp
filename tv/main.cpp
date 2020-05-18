#include <iostream>
#include <string>

#include "struct.h"
#include "menu.h"

using namespace std;

int main()
{
    setlocale(0,"");
    int len = 0;
    int selection;
    int const index = 100;
    TV *tv = new TV[index];
    Read(tv,len);
    do {
        MenuView();
        Output(tv,len);
        selection = MenuSelect();
        switch (selection) {
            case INPUT:
                Input(tv,len);
                break;
            case SORT:
                Sort(tv,len);
                break;
            case DELETE:
                Delete(tv,len);
                break;
            case ANALYSE:
                Analyse(tv,len);
                break;
            case WRITE:
                Write(tv,len);
                break;
            case READ:
                Read(tv,len);
                break;
            case EDIT:
                Edit(tv);
                break;
            case EXIT:
                return 0;
        }
    } while (1);
    return 0;
}
