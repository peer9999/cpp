#include <iostream>
#include <stack>

using namespace std;

int main()
{
    stack <int> steck;
    int i = 0;

    cout << "Введите шесть любых целых чисел: " << endl;

    while (i != 10) {
        int a;
        cin >> a; 
        cin.get();
        steck.push(a);
        i++;
    }
 
    if (steck.empty()) cout << "Стек не пуст";

    cout << "Верхний элемент стека: " << steck.top() << endl;
    cout << "Давайте удалим верхний элемент " << endl;

    steck.pop();

    cout << "А это новый верхний элемент: " << steck.top() << endl;

    return 0;
}
