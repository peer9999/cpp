#include <iostream>
#include <string>

using namespace std;

enum PlayerCountry {
    Italy,
    Spain,
    England
};

enum PlayerClub {
    Manchester_city,
    Barcelona,
    Real_Madrid
};

struct PlayerName {
    string firstname;
    string lastname;
};

struct Football {
//    enum PlayerCountry country;
//    enum PlayerClub club;
    struct PlayerName name;
    int goals;
    int fouls;
};

void Input(struct Football *,int);
void Output(struct Football *,int);
