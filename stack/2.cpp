#include <iostream>

using namespace std;

struct stack
{
    int value;
    struct stack *next;                     // указатель на следующий элемент списка (стека)
};

void push(stack* &NEXT, const int VALUE)
{
    stack *MyStack = new stack;             // объявляем новую динамическую переменную типа stack
    MyStack->value = VALUE;                 // записываем значение, которое помещается в стек
    MyStack->next  = NEXT;                  // связываем новый элемент стека с предыдущим
    NEXT = MyStack;                         // новый элемент стека становится его вершиной
}

int pop(stack* &NEXT)
{
    int temp = NEXT->value;                 // извлекаем в переменную temp значение в вершине стека
    stack *MyStack = NEXT;                  // запоминаем указатель на вершину стека, чтобы затем
                                            // освободить выделенную под него память
    NEXT = NEXT->next;                      // вершиной становится предшествующий top элемент
    delete MyStack;                         // освобождаем память, тем самым удалили вершину
    cout << temp << endl;                   // Вывод текущего элемента на экран
    return temp;                            // возвращаем значение, которое было в вершине
}

int main()
{
    stack *p = 0;

    push(p,100);                            // Положили в стек 100
    push(p,200);                            // Положили в стек 200

    pop(p);                                 // вывели на экран текущий элемент стека = 200
    pop(p);                                 // вывели на экран текущий элемент стека = 100

    return 0;
}
