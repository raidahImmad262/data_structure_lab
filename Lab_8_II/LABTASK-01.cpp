#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string name;
    Node* left;
    Node* right;

    Node(string n)
    {
        name = n;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree
{
public:
    Node* root;

    BinaryTree()
    {
        root = nullptr;
    }

    void createTree()
    {
        root = new Node("Dr. Ahmed");

        root->left = new Node("Ali");
        root->right = new Node("Sara");

        root->left->left = new Node("Usman");
        root->left->right = new Node("Ayesha");

        root->right->left = new Node("Bilal");
        root->right->right = new Node("Hina");
    }

    void display(Node* node)
    {
        if (node == nullptr)
            return;

        cout << "Member: " << node->name << endl;

        if (node->left != nullptr)
            cout << "Left Child: " << node->left->name << endl;
        else
            cout << "Left Child: NULL" << endl;

        if (node->right != nullptr)
            cout << "Right Child: " << node->right->name << endl;
        else
            cout << "Right Child: NULL" << endl;

        cout << endl;

        display(node->left);
        display(node->right);
    }

    void showTree()
    {
        display(root);
    }
};

int main()
{
    BinaryTree tree;

    tree.createTree();

    tree.showTree();

    return 0;
}