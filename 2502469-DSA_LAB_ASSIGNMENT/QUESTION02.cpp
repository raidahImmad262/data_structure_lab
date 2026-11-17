
#include <iostream>
#include <string>
#include <queue>
using namespace std;

class Node
{
public:
    int id;
    string location;
    int severity;
    int height;

    Node* left;
    Node* right;

    Node(int i, string l, int s)
    {
        id = i;
        location = l;
        severity = s;
        height = 1;
        left = right = NULL;
    }
};

class AVL
{
public:
    Node* root;

    AVL()
    {
        root = NULL;
    }

    int height(Node* n)
    {
        if (n == NULL)
            return 0;

        return n->height;
    }

    int balance(Node* n)
    {
        if (n == NULL)
            return 0;

        return height(n->left) - height(n->right);
    }

    int maximum(int a, int b)
    {
        return (a > b) ? a : b;
    }

    Node* rightRotate(Node* y)
    {
        Node* x = y->left;
        Node* t = x->right;

        x->right = y;
        y->left = t;

        y->height = 1 + maximum(height(y->left), height(y->right));
        x->height = 1 + maximum(height(x->left), height(x->right));

        return x;
    }

    Node* leftRotate(Node* x)
    {
        Node* y = x->right;
        Node* t = y->left;

        y->left = x;
        x->right = t;

        x->height = 1 + maximum(height(x->left), height(x->right));
        y->height = 1 + maximum(height(y->left), height(y->right));

        return y;
    }

    Node* insert(Node* n, int id, string loc, int s)
    {
        if (n == NULL)
            return new Node(id, loc, s);

        if (id < n->id)
            n->left = insert(n->left, id, loc, s);

        else if (id > n->id)
            n->right = insert(n->right, id, loc, s);

        else
            return n;

        n->height = 1 + maximum(height(n->left), height(n->right));

        int bf = balance(n);

        if (bf > 1 && id < n->left->id)
            return rightRotate(n);

        if (bf < -1 && id > n->right->id)
            return leftRotate(n);

        if (bf > 1 && id > n->left->id)
        {
            n->left = leftRotate(n->left);
            return rightRotate(n);
        }

        if (bf < -1 && id < n->right->id)
        {
            n->right = rightRotate(n->right);
            return leftRotate(n);
        }

        return n;
    }

    Node* search(Node* n, int id)
    {
        if (n == NULL || n->id == id)
            return n;

        if (id < n->id)
            return search(n->left, id);

        return search(n->right, id);
    }

    Node* minimum(Node* n)
    {
        while (n->left != NULL)
            n = n->left;

        return n;
    }

    Node* deleteNode(Node* n, int id)
    {
        if (n == NULL)
            return NULL;

        if (id < n->id)
            n->left = deleteNode(n->left, id);

        else if (id > n->id)
            n->right = deleteNode(n->right, id);

        else
        {
            if (n->left == NULL || n->right == NULL)
            {
                Node* temp;

                if (n->left != NULL)
                    temp = n->left;
                else
                    temp = n->right;

                if (temp == NULL)
                {
                    delete n;
                    return NULL;
                }

                Node* old = n;
                n = temp;
                delete old;
            }
            else
            {
                Node* temp = minimum(n->right);

                n->id = temp->id;
                n->location = temp->location;
                n->severity = temp->severity;

                n->right = deleteNode(n->right, temp->id);
            }
        }

        n->height = 1 + maximum(height(n->left), height(n->right));

        int bf = balance(n);

        if (bf > 1 && balance(n->left) >= 0)
            return rightRotate(n);

        if (bf > 1 && balance(n->left) < 0)
        {
            n->left = leftRotate(n->left);
            return rightRotate(n);
        }

        if (bf < -1 && balance(n->right) <= 0)
            return leftRotate(n);

        if (bf < -1 && balance(n->right) > 0)
        {
            n->right = rightRotate(n->right);
            return leftRotate(n);
        }

        return n;
    }

    void inorder(Node* n)
    {
        if (n == NULL)
            return;

        inorder(n->left);

        cout << n->id << " | "
             << n->location << " | "
             << n->severity << " | "
             << "Height: " << n->height << " | "
             << "BF: " << balance(n) << endl;

        inorder(n->right);
    }

    void levelOrder(Node* n)
    {
        if (n == NULL)
            return;

        queue<Node*> q;
        q.push(n);

        while (!q.empty())
        {
            Node* temp = q.front();
            q.pop();

            cout << temp->id << " | "
                 << temp->location << " | "
                 << temp->severity << " | "
                 << "Height: " << temp->height << " | "
                 << "BF: " << balance(temp) << endl;

            if (temp->left != NULL)
                q.push(temp->left);

            if (temp->right != NULL)
                q.push(temp->right);
        }
    }

    void displayTree(Node* n, int space = 0)
    {
        if (n == NULL)
            return;

        space += 5;

        displayTree(n->right, space);

        cout << endl;

        for (int i = 5; i < space; i++)
            cout << " ";

        cout << n->id << endl;

        displayTree(n->left, space);
    }
};

int main()
{
    AVL a;

    a.root = a.insert(a.root, 50, "Islamabad", 5);
    a.root = a.insert(a.root, 30, "Lahore", 4);
    a.root = a.insert(a.root, 70, "Karachi", 5);
    a.root = a.insert(a.root, 20, "Peshawar", 3);
    a.root = a.insert(a.root, 40, "Quetta", 4);
    a.root = a.insert(a.root, 60, "Multan", 2);
    a.root = a.insert(a.root, 80, "Sialkot", 5);
    a.root = a.insert(a.root, 10, "Murree", 3);
    a.root = a.insert(a.root, 25, "Faisalabad", 4);
    a.root = a.insert(a.root, 35, "Gujranwala", 2);
    a.root = a.insert(a.root, 45, "Hyderabad", 5);
    a.root = a.insert(a.root, 65, "Rawalpindi", 3);

    cout << "\n===== SEARCH EMERGENCY =====\n";

    Node* result = a.search(a.root, 45);

    if (result != NULL)
    {
        cout << "Emergency Found!\n";
        cout << "ID: " << result->id << endl;
        cout << "Location: " << result->location << endl;
        cout << "Severity: " << result->severity << endl;
    }
    else
        cout << "Emergency Not Found!\n";

    cout << "\n===== INORDER TRAVERSAL =====\n";
    a.inorder(a.root);

    cout << "\n===== LEVEL ORDER TRAVERSAL =====\n";
    a.levelOrder(a.root);

    cout << "\n===== DELETING EMERGENCY =====\n";

    a.root = a.deleteNode(a.root, 20);

    cout << "Emergency Deleted Successfully!\n";

    cout << "\n===== AFTER DELETION =====\n";
    a.inorder(a.root);

    cout << "\n===== FINAL AVL TREE =====\n";
    a.displayTree(a.root);

    cout << "\n===== FINAL LEVEL ORDER =====\n";
    a.levelOrder(a.root);

    return 0;
}

