#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct Node {
    int data;
    Node *left,*right;
};

// Function to create a new binary tree node having given key
Node* newNode(int key) {
    Node* node = new Node;
    node->data = key;
    node->left = node->right = nullptr;
    return node;
}

// Function to perform inorder traversal of the tree
void inorder(Node* root) {
    if (root == nullptr) {
        return;
    } 
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void rinorder(Node* root) {
    if (root == nullptr) {
        return;
    } 
    rinorder(root->right);
    cout << root->data << " ";
    rinorder(root->left);
}

void preorder(Node* root) {
    if (root == nullptr) {
        return;
    } 
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (root == nullptr) {
        return;
    } 
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Recursive function to insert a key into BST
Node* insertNode(Node* root,int key) {
    // if the root is null, create a new node and return it
    if (root == nullptr) {
        return newNode(key);
    }
    // if given key is less than the root node, recur for left subtree
    if (key < root->data) {
        root->left = insertNode(root->left,key);
    // if given key is more than the root node, recur for right subtree
    } else {
        root->right = insertNode(root->right,key);
    }
    return root;
}

Node* getMin(Node *root) {
    if (root->left == nullptr) {
        return root;
    }
    return getMin(root->left);
}

Node* getMax(Node *root) {
    if (root->right == nullptr) {
        return root;
    }
    return getMax(root->right);
}

Node* getMinNode(Node *root) {
    while (root->left) {
        root = root->left;
    }
    return root;
}

Node* getMaxNode(Node *root) {
    while (root->right) {
        root = root->right;
    }
    return root;
}

/*
void deleteNode(Node *node) {
    if (node != nullptr) {
        deleteNode(node->left);
        deleteNode(node->right);
        delete node;
    }
}
*/

Node* searchNode(Node *root,int data) {
    if (root == nullptr || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return searchNode(root->left,data);
    } else {
        return searchNode(root->right,data);
    }
}

Node* deleteNode(Node *root,int data) {
    if (root == nullptr) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left,data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right,data);
    } else if (root->left != nullptr && root->right != nullptr) {
        root->data  = getMin(root->right)->data;
        root->right = deleteNode(root->right,root->data);
    } else {
        if (root->left != nullptr) {
            root = root->left;
        } else if (root->right != nullptr) {
            root = root->right;
        } else {
            root = nullptr;
        }
    }
    return root;
}

void levelOrderPrint(Node *root) {
    if (root == nullptr) {
       return;
    }
    queue<Node *> q; // Создаем очередь
    q.push(root); // Вставляем корень в очередь
    while (!q.empty()) { // пока очередь не пуста
        Node* temp = q.front(); // Берем первый элемент в очереди
        q.pop();  // Удаляем первый элемент в очереди
        cout << temp->data << " "; // Печатаем значение первого элемента в очереди
        if (temp->left != nullptr) {
            q.push(temp->left);  // Вставляем  в очередь левого потомка
        }
        if (temp->right != nullptr) {
            q.push(temp->right);  // Вставляем  в очередь правого потомка
        }
   }
}

void levelPreorderPrint(Node *root) {
    if (root == nullptr) {
       return;
    }
    stack<Node *> s;  // Создаем стек
    s.push(root);  // Вставляем корень в стек
    while (!s.empty()) {
        Node *temp = s.top(); // Извлекаем вершину стека и печатаем
        s.pop();
        cout << temp->data << " ";
        if (temp->right != nullptr) {
            s.push(temp->right); // Вставляем в стек правого потомка
        }
        if (temp->left != nullptr) {
            s.push(temp->left);  // Вставляем в стек левого потомка
        }
    }
}

int main() {
    Node* root = nullptr;
    int keys[] = { 15, 10, 20, 8, 12, 16, 25 };

    for (int key : keys) {
        root = insertNode(root,key);
    }

    cout << "Inorder (sort asc)" << endl;
    inorder(root);
    cout << endl;

    cout << "Reverse Inorder (sort desc)" << endl;
    rinorder(root);
    cout << endl;

    cout << "Preorder (root-left-right)" << endl;
    preorder(root);
    cout << endl;

    cout << "Postorder (left-right-root)" << endl;
    postorder(root);
    cout << endl;

    cout << "Level order (root-left-right)" << endl;
    levelOrderPrint(root);
    cout << endl;

    cout << "Level preorder (root-left-right)" << endl;
    levelPreorderPrint(root);
    cout << endl;

    cout << "Minimum" << endl;
    cout << getMin(root)->data;
    cout << endl;

    cout << "Maximum" << endl;
    cout << getMax(root)->data;
    cout << endl;

    cout << "Minimum2" << endl;
    cout << getMinNode(root)->data;
    cout << endl;

    cout << "Maximum2" << endl;
    cout << getMaxNode(root)->data;
    cout << endl;

    cout << "Search 8" << endl;
    Node* temp = searchNode(root,8);
    cout << temp->data;
    cout << endl;

    cout << "Search 20" << endl;
    cout << searchNode(root,20)->data;
    cout << endl;

    cout << "Search 15" << endl;
    cout << searchNode(root,15)->data;
    cout << endl;

    temp = deleteNode(root,10);
    cout << "Level order (root-left-right)" << endl;
    levelOrderPrint(temp);
    cout << endl;

    return 0;
}
