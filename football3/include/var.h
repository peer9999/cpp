#include <iostream>
#include <string>

using namespace std;

#ifdef _WIN32
string PlayerCountry[] = {
    "������",
    "�������",
    "������"
};

string PlayerClub[3][2] = {
    "�������","������",
    "���������","����",
    "��������� ����","�����"
};

string PlayerPosition[] = {
    "��������",
    "��������",
    "������������",
    "����������"
};
#else
string PlayerCountry[] = {
    "Италия",
    "Испания",
    "Англия"
};

string PlayerClub[3][2] = {
    "Ювентус","Наполи",
    "Барселона","Реал",
    "Манчестер Сити","Челси"
};

string PlayerPosition[] = {
    "Голкипер",
    "Защитник",
    "Полузащитник",
    "Нападающий"
};
#endif
