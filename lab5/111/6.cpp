#include <iostream>
 
int main()
{
    int math[4] = {};
    math[0] = 2;
    math[1] = 3;
    math[2] = 5;
    for (int number : math) // итерация по массиву math
       std::cout << number << ' '; // получаем доступ к элементу массива в этой итерации через переменную number
 
    return 0;
}
