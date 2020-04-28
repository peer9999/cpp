#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main()
{
    string str( "abrakadabra" );
    map<char, int> letters;
    for (unsigned it = 0; it < str.size(); ++it) {
        ++letters[str[it]];
    }
    map<char, int>::iterator it;
    for (it = letters.begin() ; it != letters.end(); ++it) {
        cout << it->first << " " << it->second << "\n";
    }
    set<pair<int, string>> s;
    for (auto const &kv : letters)
        s.emplace(kv.second, kv.first);
    for (auto const &vk : s)
        cout << vk.first << " " << vk.second << endl;
}
