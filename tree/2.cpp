#include <iostream>
#include <cstring>

using namespace std;

struct Node {
    const char* key;
    int data;
    Node* next;
};

void init(Node** hashtab) {
    for (int i = 0; i < 200; i++) {
        hashtab[i] = nullptr;
    }
}

int hashing(const char* key) {
    int hash = 0;
    for (int i = 0; key[i]; i++) {
        hash = (hash * 31) ^ key[i];
    }
    return hash;
}

void add(Node** hashtab,const char* key,int data) {
    int ind = hashing(key);
    Node* node = new Node;
    if (node != nullptr) {
        node->key    = key;
        node->data   = data;
        node->next   = hashtab[ind];
        hashtab[ind] = node;
    }
}

int search(Node** hashtab,const char* key) {
    int ind = hashing(key);
    int i = 0;
    Node* node;
    for (node = hashtab[ind]; node != nullptr; node = node->next) {
        if (strcmp(node->key,key) == 0) {
            cout << "Node: " << node->key << ":" << node->data << endl;
            i++;
        }
    }
    return i;
}

int main() {
    Node* hashtab[200];
    init(hashtab);
    add(hashtab,"a",123);
    add(hashtab,"b",456);
    add(hashtab,"c",789);
    add(hashtab,"d",0);
    add(hashtab,"c",7089);
    int i = search(hashtab,"c");
    cout << "Count Node: " << i << endl;
}
