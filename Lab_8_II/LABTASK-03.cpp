
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
        root = new Node("C Drive");

        root->left = new Node("Documents");
        root->right = new Node("Pictures");

        root->left->left = new Node("Assignments");
        root->left->right = new Node("Projects");

        root->left->left->left = new Node("DSA");

        root->right->left = new Node("Photos");
        root->right->right = new Node("Videos");
    }

    void inorder(Node* node)
    {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->name << " ";
        inorder(node->right);
    }

    void preorder(Node* node)
    {
        if (node == nullptr)
            return;

        cout << node->name << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node)
    {
        if (node == nullptr)
            return;

        postorder(node->left);
        postorder(node->right);
        cout << node->name << " ";
    }
};

int main()
{
    BinaryTree tree;

    tree.createTree();

    cout << "In-order Traversal: ";
    tree.inorder(tree.root);

    cout << "\nPre-order Traversal: ";
    tree.preorder(tree.root);

    cout << "\nPost-order Traversal: ";
    tree.postorder(tree.root);

    return 0;
}