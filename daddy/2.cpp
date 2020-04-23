#include <clocale>
#include <string>
#include <iostream>
#include <cstdlib>
#include <stdexcept>

using namespace std;

//Количество символов в многобайтовой строке - это сумма mblen()
//Примечание: более простой подход воспользоваться 
//std::mbstowcs(NULL, s.c_str(), s.size())

size_t strlen_mb(string& s)
{
    size_t result = 0;
    const char* ptr = s.data();
    const char* end = ptr + s.size();
    mblen(NULL,0); // Сброс внутреннего состояния
    while (ptr < end) {
        int next = mblen(ptr,end - ptr);
        if (next == -1) {
            throw runtime_error("strlen_mb(): Ошибка преобразования");
        }
        ptr += next;
        ++result;
    }
    return result;
}

int main()
{
    //позволяет mblen() работать с многобайтовой кодировкой UTF-8
    setlocale(LC_ALL,"ru_RU.utf8");
    string str = "Италия";
    cout << str << " занимает " << str.size() << " байт, но тут "
         << strlen_mb(str) << " символов\n";
}
