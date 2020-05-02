#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

struct Tree {
    Tree *left, *right, *parent;
    char c; //символ
    int freq; //частота
    string code; //код
};

Tree *Tree_create(char symbol, int freq, string code) {
    struct Tree *node;
    node = new Tree;
    if (node != NULL) {
        node->c = symbol;
        node->freq = freq;
        node->code = code;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void Tree_add(Tree *tree, char symbol, int freq, string code) {
    struct Tree *parent, *node;
    if (tree == NULL) {
        return;
    }
    for (parent = tree; tree != NULL; ) {
        parent = tree;
        if (freq < tree->freq) {
            tree = tree->left;
        }
        else if (freq > tree->freq) {
            tree = tree->right;
        }
        else {
            return;
        }
    }
    node = Tree_create(symbol, freq, code);
    if (freq < parent->freq) {
        parent->left = node;
    }
    else {
        parent->right = node;
    }
}

void ShannonFano(Tree *tree, Tree *symbols, int end, int start = 0, const string &branch = "", const string &fullBranch = "") {
    Tree_add(tree, symbols[start].c, symbols[start].freq, branch);
    string code = fullBranch + branch;
    if (start == end) { //если дошли до одного символа какого-то, то выводим значения
        symbols[start].code = code;
        return;
    }
    int all_sum = 0; //сумма частот
    for (int i = start; i <= end; i++) {
        all_sum += symbols[i].freq;
    }
    all_sum = all_sum / 2; //делим пополам, чтобы получить идеал равных частот
    int i;
    int sum2 = symbols[start].freq;
//ищем границу раздела массива частот для наиболее равномерного разделения
    for (i = start + 1; abs(all_sum - (sum2 + symbols[i].freq)) < abs(all_sum - sum2) && i < end; i++) {
        sum2 = sum2 + symbols[i].freq;
    }
    ShannonFano(tree, symbols, i - 1, start, "0", code);
    ShannonFano(tree, symbols, end, i, "1", code);
}

int main() {
    string text;
    ifstream file_out("input.txt");
    if (!file_out.is_open()) {
        cout << "Файл не наден." << endl;
    }
    for (int i = 0; !file_out.eof(); i++) {
        char temp[1024];
        file_out.getline(temp, 1024, '\n');
        text = text + temp; //записываем в строку text содержимое файла
    }
    file_out.close();

    Tree *symbols = new Tree[text.length()]; //массив символов и частот строки
    int size = 0; //размер массива
    for (int i = 0; i < text.length(); i++) { //обрабатываем всю строку
        int j = 0;
        while (j < size && symbols[j].c != text[i]) { //ищем в массиве текущий символ
            j++;
        }
        if (j == size) { //если не нашли (j = size), то добавляем этот символ и учитываем, что частота его равна 1
            symbols[size].c = text[i];
            symbols[size++].freq = 1;
        }
        else {
            symbols[j].freq++; //если нашли, увеличиваем значение частоты
        }
    }

    bool isSorted = false;
    while (!isSorted) { //сортировка массива
        isSorted = true;
        for (int i = 0; i < size - 1; i++) {
            if (symbols[i].freq < symbols[i + 1].freq) {
                swap(symbols[i], symbols[i + 1]);
                isSorted = false;
            }
        }
    }

    Tree *tree;
    string parent = "0";
    tree = Tree_create(' ', 0, parent); //создаем 1й элемент дерева
    ShannonFano(tree, symbols, size - 1); //кодировка шеннона-фано

    ofstream file_in("Таблица кодов(Шеннон-Фано).txt");
    file_in << setw(10) << left << "Символ" << setw(10) << left << "Частота" << "Код" << endl;
    cout << setw(10) << left << "Символ" << setw(10) << left << "Частота" << "Код" << endl;
    for (int i = 0; i < size; i++) {
        file_in << setw(10) << left << symbols[i].c << setw(10) << left << symbols[i].freq << symbols[i].code.c_str() << endl; //запись в файл
        cout << setw(10) << left << symbols[i].c << setw(10) << left << symbols[i].freq << symbols[i].code.c_str() << endl; //вывод на консоль
    }
    file_in.close();
    delete[] symbols;
}
