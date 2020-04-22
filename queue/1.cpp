#include <iostream>
#include <queue>        // подключаем заголовочный файл очереди
#include <string>       // заголовочный файл для работы со строками типа string

using namespace std;

int main()
{
    queue<string> myQueue;     // создаем пустую очередь типа string

    // добавили в очередь несколько элементов типа string
    myQueue.push("No pain ");
    myQueue.push("[test] ");
    myQueue.push("- no gain");

    cout << "Количество элементов в очереди: " << myQueue.size() << endl;
    cout << "Вот они начало и конец: " << myQueue.front() << myQueue.back() << endl;

    myQueue.pop(); // удаляем один элемент в очереди
    cout << "Теперь в очереди начало и конец: " << myQueue.front() << myQueue.back() << endl;

    while (!myQueue.empty()) {
        cout << myQueue.front() << endl;
        myQueue.pop(); // удаляем один элемент в очереди
    }

    return 0;
}
