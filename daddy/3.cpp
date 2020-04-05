#include <iostream>
using namespace std;
 
struct DateTime //Опишем структуру с битовыми полями
{
 unsigned short Day : 5;   //5 бит для дня
 unsigned short Month : 4; //4 для месяца
 unsigned short Year : 7;  //7 для года от 0 до 99
 unsigned short Hour : 5;  //5 бит для 24-х часов
 unsigned short Minute : 6;//6 для минут
 unsigned short Second : 6;//6 для секунд
};
 
int main()
{ 
 DateTime d; //объявляем переменную этого типа с битовыми полями
 int i;      //И еще одну, в которую будет поступать ввод данных
 
 //Введем дату
 cout << "Input day (1-31):" << '\t'; cin >> i; d.Day = i;
 cout << "Input month (1-12):" << '\t'; cin >> i; d.Month = i;
 cout << "Input Year (00-99) :" << '\t'; cin >> i; d.Year = i;
 
 //Введем время
 cout << endl << "Input Hour (0-24):" << '\t'; cin >> i; d.Hour = i;
 cout << "Input Minute (0-60):" << '\t'; cin >> i; d.Minute = i;
 cout << "Input Seconds (0-60):" << '\t'; cin >> i; d.Second = i;
 
 //И выведем их с показателем размера в памяти
 cout << endl << "Date is: " << d.Day << "." << d.Month << ".20" << d.Year << " ";
 cout << d.Hour << ":" << d.Minute << ":" << d.Second << endl;
 cout << sizeof(d) << endl;
}
