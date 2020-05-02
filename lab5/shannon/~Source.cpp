#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>
#include <iterator>
#include <map>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

struct Tree {
    char letter;
    int freq;
    string code;
    Tree *left, *right, *parent;
};

struct Node {
    char letter;
    int freq;
    string code;
};

void shannon(Tree*, Node*, int, int, const string&, const string&);
Tree *init(char, int, string);
void add(char, int, string, Tree*);
void addnode(char, int, string, Tree*&);
void del(Tree*&);
void print(Tree*&);

bool compare(const pair<char, int>& a, const pair<char, int>& b)
{
    return a.second > b.second;
}

int main()
{
    unsigned int i, j;
    string line;
    char letter;
    int freq;
    string text = "";
//    ifstream file("D:/Labs/Language/Lab5/text4.txt");
    ifstream file("input.txt");

    if (file.is_open()) {
        while (getline(file, line)) {
            text = text + line;
        }
    }
    file.close();

    vector<pair<char, int>> Maps;
    map<char, int> Map;

    for (i = 0; i < text.size(); i++) {
        Map[text[i]]++;
    }

    for (const pair<char, int>& i : Map) {
        Maps.push_back(i);
    }
    sort(Maps.begin(), Maps.end(), compare);
    int tsize = Maps.size();
//    cout << Maps.size() << " " << tsize << endl;

    Node *symbols = new Node[tsize];
    i = 0;
    for (const pair<char, int>& map : Maps) {
        symbols[i].letter = map.first;
        symbols[i].freq   = map.second;
        i++;
    }
/*    for (i = 0; i < tsize; i++) {
        cout << symbols[i].letter << " " << symbols[i].freq << endl;
    }
  */
//return 0;




    Tree *tree = init(' ', 0, "0");

//print(tree);
//return 0;

    shannon(tree, symbols, tsize - 1, 0, "", "");

    cout << setw(10) << left << "Символ" << setw(10) << left << "Частота" << "Код" << endl;
    for (int i = 0; i < tsize; i++) {
        cout << setw(10) << left << symbols[i].letter << setw(10) << left << symbols[i].freq << symbols[i].code.c_str() << endl; //вывод на консоль
    }

/*    for (const pair<char, int>& map : Maps) {
        letter = map.first;
        freq   = map.second;
        addnode(letter, freq, "0", tree);
//print(tree);
//return 0;
    }*/
//    print(tree);
    return 0;
}

void shannon(Tree *tree, Node *symbols, int end, int start = 0, const string &branch = "", const string &fullBranch = "") {
    add(symbols[start].letter, symbols[start].freq, branch, tree);

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
    shannon(tree, symbols, i - 1, start, "0", code);
    shannon(tree, symbols, end, i, "1", code);
}

Tree *init(char letter, int freq, string code) {
    Tree *node;
    node         = new Tree;
    node->letter = letter;
    node->freq   = freq;
    node->code   = code;
    node->left   = NULL;
    node->right  = NULL;
    return node;
}

void add(char letter, int freq, string code, Tree *tree) {
    struct Tree *parent, *node;
    if (tree == NULL) {
        return;
    }
    for (parent = tree; tree != NULL;) {
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
    node = init(letter, freq, code);
    if (freq < parent->freq) {
        parent->left = node;
    }
    else {
        parent->right = node;
    }
}

void addnode(char l, int f, string c, Tree *&tree) {
    if (f < tree->freq) {
        tree->left         = new Tree;
        tree->left->letter = l;
        tree->left->freq   = f;
        tree->right->code += c;
        tree->left->left   = tree->left->right = NULL;
    }
    if (f > tree->freq) {
        tree->right         = new Tree;
        tree->right->letter = l;
        tree->right->freq   = f;
        tree->right->code  += c;
        tree->right->left   = tree->right->right = NULL;
    }
}

void del(Tree *&tree) {
    if (tree != NULL) {
        del(tree->left);
        del(tree->right);
        delete tree;
    }
}

void print(Tree *&tree) {
    if (tree != NULL) {
        print(tree->left);
        cout << tree->letter << " " << tree->freq << " " << tree->code << endl;
        print(tree->right);
    }
}
