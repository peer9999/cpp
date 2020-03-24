#include <iostream>

#include "include/function.h"

using namespace std;

void pause()
{
/*
#ifdef _WIN32
    system("pause");
#else
    system("read -p 'Для продолжения нажмите любую клавишу ...' -n 1 -s");
#endif
*/
    cout << endl << "Для продолжения нажмите любую клавишу ...";
    cin.ignore();
}
