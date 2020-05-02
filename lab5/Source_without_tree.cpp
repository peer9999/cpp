#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    char letter;
    int freq;
    string code;
};

bool compare(const pair<char,int>& a,const pair<char,int>& b) {
    return a.second > b.second;
}

void shannon(Node *nodes,int start,int end,const string &oneCode = "",const string &allCode = "") {
    string code = allCode + oneCode;

    if (start == end) { // если символ остался один, то выводим значения
        nodes[start].code = code;
        return;
    }

    int i;
    int allSum = 0; // сумма частот
    for (i = start; i <= end; i++) {
        allSum += nodes[i].freq;
    }
    allSum = allSum / 2; // делим пополам, чтобы получить идеал равных частот
    int sum = nodes[start].freq;
    // ищем границу раздела массива частот для равномерного разделения
    for (i = start + 1; abs(allSum - (sum + nodes[i].freq)) < abs(allSum - sum) && i < end; i++) {
        sum += nodes[i].freq;
    }

    shannon(nodes,start,i - 1,"0",code);
    shannon(nodes,i,end,"1",code);
}

void print(Node *nodes,int size) {
    cout << setw(10) << left << "Символ " << setw(10) << left << "Частота " << setw(10) << left << "Код" << endl;
    for (int i = 0; i < size; i++) {
        cout << setw(10) << left << nodes[i].letter << setw(10) << left << nodes[i].freq << setw(10) << left << nodes[i].code.c_str() << endl;
    }
}

string readfile() {
    string text = "";
    string line;
//    ifstream file("D:/Labs/Language/Lab5/text4.txt");
    ifstream file("input.txt");

    if (file.is_open()) {
        while (getline(file,line)) {
            text += line;
        }
    }
    file.close();

    return text;
}

int main() {
    string text = readfile();

    map<char,int> mFreq;
    for (int i = 0; i < text.size(); i++) {
        mFreq[text[i]]++;
    }

    vector<pair<char,int>> vFreq;
    for (const pair<char,int>& pair : mFreq) {
        vFreq.push_back(pair);
    }
    sort(vFreq.begin(),vFreq.end(),compare);
    int size = vFreq.size();

    Node *nodes = new Node[size];
    int i = 0;
    for (const pair<char,int>& pair : vFreq) {
        nodes[i].letter = pair.first;
        nodes[i].freq   = pair.second;
        i++;
    }

    shannon(nodes,0,size - 1);
    print(nodes,size);

    return 0;
}
