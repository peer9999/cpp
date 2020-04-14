#include <iostream>
#include <string>

using namespace std;

#ifdef _WIN32
string EmptyTable = "������ �� ������� �����������. ����������� ����� \"����\".";
string TitleTable = "    ������";
string ColumnTable[] = {
    "|",
    "     ",
    "|",
    "      ������      ",
    "|",
    "       ����       ",
    "|",
    "       ���        ",
    "|",
    "     �������      ",
    "|",
    "      ������      ",
    "|",
    " ���� ",
    "|",
    " ��������� ",
    "|",
    "    ����������    ",
    "|"
};

string AddPlayer =  "�������� ���������� ������� ��� �����:";
string Country   =  "    ������ ( ";
string Club      =  "    ���� ( ";
string Firstname =  "    ���: ";
string Lastname  =  "    �������: ";
string Position  =  "    ������ ( ";
string Goals     =  "    ����: ";
string Fouls     =  "    ���������: ";
string Misc      =  "    �������������� ����������: ";

string SortField  =  "�������� ���� ��� ���������� ( 1-���� 2-��������� ): ";
string SortDirect =  "�������� ����������� ���������� ( 1-�� ����������� 2-�� �������� ): ";

string DeletePlayer =  "�������� ������ ��� ��������:";
string NotExist     =  "������ ������ �� ����������. ���������� ��� ���.";

string GoodPlayer =  "����� �������� �����: ";
string PlaysFor   =  " ������ �� ";
string Scored     =  " ����� ";
string fGoals     =  " �����";

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

const char *OUT_FILE = "Out_win.txt";
#else
string EmptyTable    = "Данные об игроках отсутствуют. Используйте пункт \"Ввод\".";
string TitleTable    = "    ИГРОКИ";
string ColumnTable[] = {
    "|",
    "     ",
    "|",
    "      Страна      ",
    "|",
    "       Клуб       ",
    "|",
    "       Имя        ",
    "|",
    "     Фамилия      ",
    "|",
    "      Амплуа      ",
    "|",
    " Голы ",
    "|",
    " Нарушения ",
    "|",
    "    Примечания    ",
    "|"
};

string AddPlayer = "Выберите количество игроков для ввода: ";
string Country   = "    Страна ( ";
string Club      = "    Клуб ( ";
string Firstname = "    Имя: ";
string Lastname  = "    Фамилия: ";
string Position  = "    Амплуа ( ";
string Goals     = "    Голы: ";
string Fouls     = "    Нарушения: ";
string Misc      = "    Дополнительная информация: ";

string SortField  = "Выберите поле для сортировки ( 1-Голы 2-Нарушения ): ";
string SortDirect = "Выберите направление сортировки ( 1-По возрастанию 2-По убывания ): ";

string DeletePlayer = "Выберите игрока для удаления: ";
string NotExist     = "Такого игрока не существует. Попробуйте еще раз.";

string GoodPlayer = "Самый полезный игрок: ";
string PlaysFor   = " играет за ";
string Scored     = " забил ";
string fGoals     = " голов";

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

const char *OUT_FILE = "Out.txt";
#endif
int ColumnTableCount = 19;
string RightBracket  = "): ";
