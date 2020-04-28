#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    string str("abrakadabra");
    int letters[255] = {0};
    int iarr[255];
    char carr[255];
    int i, j, z;

    for (i = 0; i < str.size(); i++) {
        letters[(int)str[i]]++;
    }

    for (i = 0, z = 0; i < 255; i++) {
        if (letters[i] > 0) {
            carr[z] = (char)i;
            iarr[z] = letters[i];
            z++;
        }
    }

    for (i = 0; i < z - 1; i++) {
        for (j = 0; j < z - i - 1; j++) {
            if (iarr[j] > iarr[j + 1]) {
                swap(iarr[j],iarr[j + 1]);
                swap(carr[j],carr[j + 1]);
            }
        }
    }

    for (i = 0; i < z; i++) {
        cout << carr[i] << " = " << iarr[i] << "\n";
    }

    return 0;
}
