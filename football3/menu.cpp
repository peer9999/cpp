#include <iostream>

#include "include/menu_var.h"
#include "include/menu.h"

using namespace std;

void MenuView()
{
    system(ClearCommand);
    cout << endl << MenuTitle << endl;
    for (int i = 0; i < MenuCount; i++) {
        cout << MenuPoint[i];
    }
    cout << endl << endl;
}

int MenuSelect()
{
    int k = 0;
    cout << endl << MenuAction;
    cin >> k;
    cin.get();
    return k;
}
