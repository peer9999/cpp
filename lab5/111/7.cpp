#include <vector>
#include <iostream>
 
int main()
{
    std::vector<int> math = { 0, 1, 4, 5, 7, 8, 10, 12, 15, 17, 30, 41}; // обратите внимание на использование std::vector здесь вместо фиксированного массива
    math[12] = 100;
    for (const auto &number : math)
        std::cout << number << ' ';

    return 0;
}
