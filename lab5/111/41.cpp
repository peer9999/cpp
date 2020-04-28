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
    map<int, char> result;

    for (unsigned it = 0; it < str.size(); ++it) {
        letters[(int)str[it]]++;
    }

    for (i = 0, z = 0; i < 255; i++) {
        if (letters[i] > 0) {
            result[letters[i]] = (char)i;
            carr[z] = (char)i;
            iarr[z] = letters[i];
//            cout << (char)i << " = " << letters[i] << "\n";
//            cout << carr[z] << " = " << iarr[z] << "\n";
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

    for (auto r : result) {
        cout << r.first << " = " << r.second << endl;    
    }

    return 0;
}
