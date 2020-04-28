#include <iostream>
#include <string>
#include <cstring>

#define MAXWORD 100

using namespace std;

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

// Функция добавления узла к дереву
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    if (p == NULL) {
        p        = new tnode;
        p->word  = strdup(w);
        p->count = 1;
        p->left  = p->right = NULL;
    } else if ((cond = strcmp(w,p->word)) == 0) {
        p->count++;
    } else if (cond < 0) {
        p->left = addtree(p->left,w);
    } else {
        p->right = addtree(p->right,w);
    }
    return p;
}

// Функция удаления поддерева
void freemem(tnode *tree)
{
    if (tree != NULL) {
        freemem(tree->left);
        freemem(tree->right);
        free(tree);
    }
}

// Функция вывода дерева
void treeprint(struct tnode *p,const char *w)
{
    if (p != NULL) {
        treeprint(p->left,"l");
        printf("%d %s %s\n",p->count,p->word,w);
        treeprint(p->right,"r");
    }
}
int main()
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    do {
        cout << "word = ";
        cin >> word;
        cin.get();
//        cout << word << endl;
        if (isalpha(word[0])) {
            root = addtree(root,word);
        }
    } while (word[0] != '0');
    treeprint(root,"g");
    freemem(root);
    return 0;
}
