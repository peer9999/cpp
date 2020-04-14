#include <iostream>
#include <string>

using namespace std;

#ifdef _WIN32
string MenuTitle   = "    ������� ����";
string MenuAction  = "�������� ��������: ";
string MenuPoint[] = {
    "1.����    ",
    "2.����������    ",
    "3.��������    ",
    "4.�����    ",
    "5.������ �� �����    ",
    "6.������ � ����    ",
    "0.�����",
};
const char *ClearCommand = "cls";
#else
string MenuTitle   = "    ГЛАВНОЕ МЕНЮ";
string MenuAction  = "Выберите действие: ";
string MenuPoint[] = {
    "1.Ввод    ",
    "2.Сортировка    ",
    "3.Удаление    ",
    "4.Найти    ",
    "5.Чтение из файла    ",
    "6.Запись в файл    ",
    "0.Выход",
};
const char *ClearCommand = "clear";
#endif
int MenuCount = 7;
