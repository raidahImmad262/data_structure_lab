
#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Node
{
public:
    string name;
    int patientID;
    int priority;

    Node* left;
    Node* right;

    Node(string n, int id, int p)
    {
        name = n;
        patientID = id;
        priority = p;

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

    void swapPatient(Node* a, Node* b)
    {
        swap(a->name, b->name);
        swap(a->patientID, b->patientID);
        swap(a->priority, b->priority);
    }

    void insert(string name, int id, int priority)
    {
        Node* newNode = new Node(name, id, priority);

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

    // Heapify Up
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

        if (parent != NULL && newNode->priority > parent->priority)
        {
            swapPatient(newNode, parent);
            heapifyUp(parent);
        }
    }

  
    void display()
    {
        if (root == NULL)
        {
            cout << "No patients in queue!";
            return;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            Node* temp = q.front();
            q.pop();

            cout << temp->name << " ("
                 << temp->patientID << ", "
                 << temp->priority << ")  ";

            if (temp->left != NULL)
                q.push(temp->left);

            if (temp->right != NULL)
                q.push(temp->right);
        }
    }

    
    void highestPriority()
    {
        if (root != NULL)
        {
            cout << "\nPatient to be treated first: ";
            cout << root->name;
            cout << " | ID: " << root->patientID;
            cout << " | Priority: " << root->priority;
        }
    }

    void deleteRoot()
    {
        if (root == NULL)
        {
            cout << "No patients available!";
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
        root->patientID = last->patientID;
        root->priority = last->priority;

        // Delete last node
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
            temp->left->priority > largest->priority)
        {
            largest = temp->left;
        }

        if (temp->right != NULL &&
            temp->right->priority > largest->priority)
        {
            largest = temp->right;
        }

        if (largest != temp)
        {
            swapPatient(temp, largest);
            heapifyDown(largest);
        }
    }
};

int main()
{
    MaxHeap h;

  
    h.insert("Ali", 101, 90);
    h.insert("Sara", 102, 70);
    h.insert("Ahmed", 103, 60);
    h.insert("Ayesha", 104, 40);
    h.insert("Usman", 105, 50);
    h.insert("Hina", 106, 80);

    cout << "Hospital Emergency Queue:\n";
    h.display();

    h.highestPriority();

    
    cout << "\n\nPatient treated and removed from queue.";

    h.deleteRoot();

    cout << "\n\nUpdated Hospital Queue:\n";
    h.display();

    h.highestPriority();

    return 0;
}
