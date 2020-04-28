#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    string str("abrakadabra");

    map<const char, size_t> letters;
    for (const auto& i : str)
        ++letters[i];

    for (const auto& it : letters)
        cout << it.first << ' ' << it.second << endl;
}
