#include <iostream>
using namespace std;

class Node {
public:
    int token;
    Node* left;
    Node* right;
    int height;

    Node(int value) {
        token = value;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree {
public:
    Node* root;

    AVLTree() {
        root = nullptr;
    }

    
    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;

        return node->height;
    }

    
    int getBalance(Node* node) {
        if (node == nullptr)
            return 0;

        return getHeight(node->left) - getHeight(node->right);
    }

    
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* temp = x->right;

        x->right = y;
        y->left = temp;

        y->height = 1 + max(getHeight(y->left),
                            getHeight(y->right));

        x->height = 1 + max(getHeight(x->left),
                            getHeight(x->right));

        return x;
    }

    
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* temp = y->left;

        y->left = x;
        x->right = temp;

        x->height = 1 + max(getHeight(x->left),
                            getHeight(x->right));

        y->height = 1 + max(getHeight(y->left),
                            getHeight(y->right));

        return y;
    }

    
    Node* insert(Node* node, int value) {
        // Normal BST insertion
        if (node == nullptr)
            return new Node(value);

        if (value < node->token)
            node->left = insert(node->left, value);

        else if (value > node->token)
            node->right = insert(node->right, value);

        else
            return node;

        
        node->height = 1 + max(getHeight(node->left),
                               getHeight(node->right));

        
        int balance = getBalance(node);

        
        if (balance > 1 && value < node->left->token)
            return rightRotate(node);

        
        if (balance < -1 && value > node->right->token)
            return leftRotate(node);

        
        if (balance > 1 && value > node->left->token) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        
        if (balance < -1 && value < node->right->token) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorder(Node* node) {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->token << " ";
        inorder(node->right);
    }

    
    void display(Node* node, int space = 0) {
        if (node == nullptr)
            return;

        space += 5;

        display(node->right, space);

        cout << endl;

        for (int i = 5; i < space; i++)
            cout << " ";

        cout << node->token << endl;

        display(node->left, space);
    }
};

int main() {
    AVLTree tree;

    int tokens[] = {15, 25, 35, 45, 55, 65, 75};

    for (int i = 0; i < 7; i++) {
        tree.root = tree.insert(tree.root, tokens[i]);
    }

    cout << "In-order Traversal: ";
    tree.inorder(tree.root);

    cout << "\n\nFinal Balanced AVL Tree:";
    tree.display(tree.root);

    return 0;
}
