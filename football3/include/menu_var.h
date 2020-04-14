#include <iostream>
#include <string>

using namespace std;

#ifdef _WIN32
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
const char *ClearCommand = "cls";
#else
string MenuTitle   = "    Р“Р›РђР’РќРћР• РњР•РќР®";
string MenuAction  = "Р’С‹Р±РµСЂРёС‚Рµ РґРµР№СЃС‚РІРёРµ: ";
string MenuPoint[] = {
    "1.Р’РІРѕРґ    ",
    "2.РЎРѕСЂС‚РёСЂРѕРІРєР°    ",
    "3.РЈРґР°Р»РµРЅРёРµ    ",
    "4.РќР°Р№С‚Рё    ",
    "5.Р§С‚РµРЅРёРµ РёР· С„Р°Р№Р»Р°    ",
    "6.Р—Р°РїРёСЃСЊ РІ С„Р°Р№Р»    ",
    "0.Р’С‹С…РѕРґ",
};
const char *ClearCommand = "clear";
#endif
int MenuCount = 7;
