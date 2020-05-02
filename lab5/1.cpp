#include <bits/stdc++.h> 

using namespace std; 

struct Node {
    char letter;
    float prob;
    int freq;
};
Node *node;
map<char,string> codes;
map<char,int> freqs;

static int compare(const void *elem1,const void *elem2) {
    const Node a = *(Node*)elem1;
    const Node b = *(Node*)elem2;

    if (a.prob < b.prob) return 1;
    else if (a.prob > b.prob) return -1;
    return 0;
}

void print(int size) {
    cout << setw(10) << left << "Символ " << setw(10) << left << "Частота " << setw(10) << left << "Код" << endl;
    for (int i = 0; i < size; i++) {
        printf("%c\t%i\t%s\n",node[i].letter,node[i].freq,codes[node[i].letter].c_str());
    }
}

float readfile() {
    char ch;
    char filename[128] = "input.txt";
    FILE *file;
    float total = 0;

    file = fopen(filename,"r");
    while (fscanf(file,"%c",&ch) != EOF) {
        freqs[ch]++;
        total++;
    }
    fclose(file);

    return total;
}

void shannon(int li,int ri) {
    int i,isp;
    float prob;
    float full;
    float half;

    if (li == ri) {
        return;
    } else if (ri - li == 1) {
        // If interval consist of 2 elements then it's simple
        codes[node[li].letter] += '0';
        codes[node[ri].letter] += '1';
    } else {
        // Calculating sum of probabilities at specified interval
        full = 0;
        for (i = li; i <= ri; ++i) {
            full += node[i].prob;
        }
        // Searching center
        prob = 0;
        isp  = -1; // index of split pos
        half = full * 0.5f;
        for (i = li; i <= ri; ++i) {
            prob += node[i].prob;
            if (prob <= half) {
                codes[node[i].letter] += '0';
            } else {
                codes[node[i].letter] += '1';
                if (isp < 0) isp = i;
            }
        }
        if (isp < 0) isp = li + 1;

        shannon(li,isp - 1);
        shannon(isp,ri);
    }
}

int encode(float total) {
    int i = 0;
    int size = (int)freqs.size();

    node = new Node[size];
    map<char,int>::iterator fi;
    for (fi = freqs.begin(); fi != freqs.end(); ++fi, ++i) {
        node[i].letter = (*fi).first;
        node[i].prob   = float((*fi).second) / total;
        node[i].freq   = (*fi).second;
    }
    qsort(node,size,sizeof(Node),compare);

    return size;
}

int main() {
    float total = readfile();
    int size = encode(total);
    shannon(0,size - 1);
    print(size);

    codes.clear();
    freqs.clear();
    delete[] node;

    return 0;
}
