
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
        left = right = nullptr;
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
        root = new Node("Online Store");

        root->left = new Node("Electronics");
        root->right = new Node("Clothing");

        root->left->left = new Node("Mobiles");
        root->left->right = new Node("Laptops");

        root->right->left = new Node("Men");
        root->right->right = new Node("Women");

        root->left->right->right = new Node("Accessories");
    }

    void BFS()
    {
        Node* q[100];
        int front = 0, rear = 0;

        q[rear++] = root;

        while (front < rear)
        {
            Node* temp = q[front++];

            cout << temp->name << " ";

            if (temp->left != nullptr)
                q[rear++] = temp->left;

            if (temp->right != nullptr)
                q[rear++] = temp->right;
        }
    }
};

int main()
{
    BinaryTree tree;

    tree.createTree();

    cout << "BFS Traversal: ";
    tree.BFS();

    return 0;
}
