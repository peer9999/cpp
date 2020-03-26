#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <stdexcept>

#include "include/function.h"

using namespace std;

void pause()
{
#ifdef _WIN32
    cout << endl << "Äëÿ ïðîäîëæåíèÿ íàæìèòå ëþáóþ êëàâèøó ...";
#else
    cout << endl << "Ð”Ð»Ñ Ð¿Ñ€Ð¾Ð´Ð¾Ð»Ð¶ÐµÐ½Ð¸Ñ Ð½Ð°Ð¶Ð¼Ð¸Ñ‚Ðµ Ð»ÑŽÐ±ÑƒÑŽ ÐºÐ»Ð°Ð²Ð¸ÑˆÑƒ ...";
#endif
    cin.ignore();
}

void print_space(int l)
{
    int len = 17;
    int ttl = 0;
    if (l < len) {
        ttl = len - l;
        cout << setfill(' ') << setw(ttl) << " ";
    }
}

size_t strlen_mb(string& str)
{
    size_t result   = 0;
    const char* ptr = str.data();
    const char* end = ptr + str.size();
    mblen(NULL,0); // Ð¡Ð±Ñ€Ð¾Ñ Ð²Ð½ÑƒÑ‚Ñ€ÐµÐ½Ð½ÐµÐ³Ð¾ ÑÐ¾ÑÑ‚Ð¾ÑÐ½Ð¸Ñ
    while (ptr < end) {
        int next = mblen(ptr,end - ptr);
        if (next == -1) {
            throw runtime_error("strlen_mb(): Conversion fault");
        }
        ptr += next;
        ++result;
    }
    return result;
}
