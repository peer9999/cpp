#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <stdexcept>

#include "include/function_var.h"
#include "include/function.h"

using namespace std;

void pause()
{
    cout << endl << Pause;
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

size_t strlen_mb(string &str)
{
    size_t result   = 0;
    const char* ptr = str.data();
    const char* end = ptr + str.size();
    mblen(NULL,0); // Сброс внутреннего состояния
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
