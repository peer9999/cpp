#include <iostream>

using namespace std;

struct Node
{
   int x;
   Node *l,*r;
};

void show(Node *&Tree,char w)
{
    if (Tree != NULL) {
       show(Tree->l,'l');
       cout << Tree->x << " " << w << endl;
       show(Tree->r,'r');
    }
}

void add_node(int x,Node *&MyTree)
{
    if (NULL == MyTree) {
        MyTree    = new Node;
        MyTree->x = x;
        MyTree->l = MyTree->r = NULL;
    } else if (x <= MyTree->x) {
        if (MyTree->l != NULL) {
            add_node(x,MyTree->l);
        } else {
            MyTree->l    = new Node;
            MyTree->l->l = MyTree->l->r = NULL;
            MyTree->l->x = x;
        }
    } else if (x > MyTree->x) {
        if (MyTree->r != NULL) {
            add_node(x,MyTree->r);
        } else {
            MyTree->r    = new Node;
            MyTree->r->l = MyTree->r->r = NULL;
            MyTree->r->x = x; 
        }
    }
}

int main()
{
    Node *Tree = NULL;
    int s[12] = {1,2,3,8,4,5,6,2,7,8,9,0};

    for (int i = 0; i < 12; i++) {
//    for (int i = 5; i > 0; i--) {
        add_node(s[i],Tree);
    }

    show(Tree,'g');
    cin.get();
    return 0;
}

