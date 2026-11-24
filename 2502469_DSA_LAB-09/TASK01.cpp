
#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Node
{
public:
    string name;
    int rollNo;
    int marks;

    Node* left;
    Node* right;

    Node(string n, int r, int m)
    {
        name = n;
        rollNo = r;
        marks = m;

        left = NULL;
        right = NULL;
    }
};

class MaxHeap
{
public:
    Node* root;

    MaxHeap()
    {
        root = NULL;
    }

   
    void swapStudent(Node* a, Node* b)
    {
        swap(a->name, b->name);
        swap(a->rollNo, b->rollNo);
        swap(a->marks, b->marks);
    }

    
    void insert(string name, int rollNo, int marks)
    {
        Node* newNode = new Node(name, rollNo, marks);

        if (root == NULL)
        {
            root = newNode;
            return;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            Node* temp = q.front();
            q.pop();

            if (temp->left == NULL)
            {
                temp->left = newNode;
                break;
            }
            else
                q.push(temp->left);

            if (temp->right == NULL)
            {
                temp->right = newNode;
                break;
            }
            else
                q.push(temp->right);
        }

        heapifyUp(newNode);
    }

   
    void heapifyUp(Node* newNode)
    {
        Node* parent = NULL;

        queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            Node* temp = q.front();
            q.pop();

            if (temp->left == newNode || temp->right == newNode)
            {
                parent = temp;
                break;
            }

            if (temp->left != NULL)
                q.push(temp->left);

            if (temp->right != NULL)
                q.push(temp->right);
        }

        if (parent != NULL && newNode->marks > parent->marks)
        {
            swapStudent(newNode, parent);
            heapifyUp(parent);
        }
    }

   
    void display()
    {
        if (root == NULL)
        {
            cout << "Heap is empty!";
            return;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            Node* temp = q.front();
            q.pop();

            cout << temp->name << " ("
                 << temp->rollNo << ", "
                 << temp->marks << ")  ";

            if (temp->left != NULL)
                q.push(temp->left);

            if (temp->right != NULL)
                q.push(temp->right);
        }
    }

   
    void deleteRoot()
    {
        if (root == NULL)
        {
            cout << "Heap is empty!";
            return;
        }

        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
            return;
        }

        queue<Node*> q;
        q.push(root);

        Node* last = root;
        Node* lastParent = NULL;

        // Find last node
        while (!q.empty())
        {
            Node* temp = q.front();
            q.pop();

            if (temp->left != NULL)
            {
                lastParent = temp;
                last = temp->left;
                q.push(temp->left);
            }

            if (temp->right != NULL)
            {
                lastParent = temp;
                last = temp->right;
                q.push(temp->right);
            }
        }

       
        root->name = last->name;
        root->rollNo = last->rollNo;
        root->marks = last->marks;

       
        if (lastParent->right == last)
            lastParent->right = NULL;
        else
            lastParent->left = NULL;

        delete last;

        heapifyDown(root);
    }

   
    void heapifyDown(Node* temp)
    {
        Node* largest = temp;

        if (temp->left != NULL &&
            temp->left->marks > largest->marks)
        {
            largest = temp->left;
        }

        if (temp->right != NULL &&
            temp->right->marks > largest->marks)
        {
            largest = temp->right;
        }

        if (largest != temp)
        {
            swapStudent(temp, largest);
            heapifyDown(largest);
        }
    }
};

int main()
{
    MaxHeap h;

    // Insert six students
    h.insert("Ali", 101, 85);
    h.insert("Sara", 102, 92);
    h.insert("Ahmed", 103, 78);
    h.insert("Ayesha", 104, 95);
    h.insert("Usman", 105, 88);
    h.insert("Hina", 106, 90);

    cout << "Before Deletion:\n";
    h.display();

    cout << "\n\nDeleting student with highest marks...\n";

    h.deleteRoot();

    cout << "\nAfter Deletion:\n";
    h.display();

    return 0;
}
