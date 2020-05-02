#include <bits/stdc++.h> 

using namespace std; 

struct pnode {
    char ch; // char
    float p; // probability
    int f; // probability
};
pnode *ptable; // table of probabilities
map<char, string> codes; // codeword for each char

static int pnode_compare(const void *elem1, const void *elem2)
{
    const pnode a = *(pnode*)elem1;
    const pnode b = *(pnode*)elem2;
    if (a.p < b.p) return 1; // 1 - less (reverse for decreasing sort)
    else if (a.p > b.p) return -1;
    return 0;
}

void EncShannon(int li, int ri, int RRR)
{
    int i, isp;
    float p;
    float pfull;
    float phalf;

    if (li == ri) {
        return;
    } else if (ri - li == 1) {
        //  If interval consist of 2 elements then it's simple
        codes[ptable[li].ch] += '0';
        codes[ptable[ri].ch] += '1';
    } else {
        //  Calculating sum of probabilities at specified interval
        pfull = 0;
        for (i = li; i <= ri; ++i) {
            pfull += ptable[i].p;
        }

        //  Searching center
        p = 0;
        isp = -1; // index of split pos
        phalf = pfull * 0.5f;
        for (i = li; i <= ri; ++i) {
            p += ptable[i].p;
            if (p <= phalf) {
                codes[ptable[i].ch] += '0';
            } else {
                codes[ptable[i].ch] += '1';
                if (isp < 0) isp = i;
            }
        }
 
        if (isp < 0) isp = li + 1;

//cout << li << " " << ri << " " << isp << " " << RRR << " " << pfull << endl;

        //  Next step (recursive)
        EncShannon(li, isp - 1, 0);
        EncShannon(isp, ri, 1);
    }
}

void Encode(const char *inputFilename)
{
    map<char, int> freqs; // frequency for each char from input text
    int i;

    //  Opening input file
    FILE *inputFile;
    inputFile = fopen(inputFilename,"r");

    //  Counting chars
    char ch; // char
    unsigned total = 0;
    int tsize; // table size (number of chars)

    while (fscanf(inputFile,"%c",&ch) != EOF) {
        freqs[ch]++;
        total++;
    }
    tsize = (int)freqs.size();

    //  Building decreasing freqs table
    ptable = new pnode[tsize];
    float ftot = float(total);
    map<char, int>::iterator fi;
    for (fi = freqs.begin(), i = 0; fi != freqs.end(); ++fi, ++i) {
        ptable[i].ch = (*fi).first;
        ptable[i].p  = float((*fi).second) / ftot;
        ptable[i].f  = (*fi).second;
    }
    qsort(ptable,tsize,sizeof(pnode),pnode_compare);

/*    for (fi = freqs.begin(), i = 0; fi != freqs.end(); ++fi, ++i) {
cout << ptable[i].ch << " " << ptable[i].p << " " << ptable[i].f << endl;
    }
return;*/

    //  Encoding
    EncShannon(0,tsize - 1, 0);
//return;
//    printf("%i\n", tsize);
    cout << setw(10) << left << "Символ " << setw(10) << left << "Частота " << setw(10) << left << "Код" << endl;
    for (i = 0; i < tsize; i++) {
        printf("%c\t%f\t%s\n", ptable[i].ch, ptable[i].p, codes[ptable[i].ch].c_str());
    }

    //  Outputing encoded text
    while (fscanf(inputFile, "%c", &ch) != EOF) {
        printf("%s\n", codes[ch].c_str());
    }

    codes.clear();
    delete[] ptable;

    fclose(inputFile);
}

int main()
{
    char inputFilename[128] = "input.txt";

    Encode(inputFilename);

    return 0;
}
