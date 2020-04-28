#include <map>
#include <set>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    std::string str( "abrakadabra" );

    std::map<char, int> letters;
    for (const auto& i : str) {
        ++letters[i];
    }

    for (const auto& it : letters) {
        std::cout << it.first << " " << it.second << std::endl;
    }

    std::set<std::pair<int, char>> s;
    for (auto const &kv : letters) {
        s.emplace(kv.second, kv.first);
    }

    for (auto const &vk : s) {
        std::cout << vk.first << " " << vk.second << std::endl;
    }

    return 0;
}
