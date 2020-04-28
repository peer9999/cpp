#include <iostream>
 
int main()
{
    int math[] = { 0, 1, 4, 5, 7, 8, 10, 12, 15, 17, 30, 41};
    for (int number : math) // итерация по массиву math
       std::cout << number << ' '; // получаем доступ к элементу массива в этой итерации через переменную number
 
    return 0;
}
