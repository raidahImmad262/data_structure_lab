
#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Node
{
public:
    int orderID;
    string customerName;
    int amount;

    Node* left;
    Node* right;

    Node(int id, string name, int a)
    {
        orderID = id;
        customerName = name;
        amount = a;

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

    
    void swapOrder(Node* a, Node* b)
    {
        swap(a->orderID, b->orderID);
        swap(a->customerName, b->customerName);
        swap(a->amount, b->amount);
    }


    void insert(int id, string name, int amount)
    {
        Node* newNode = new Node(id, name, amount);

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

        if (parent != NULL && newNode->amount > parent->amount)
        {
            swapOrder(newNode, parent);
            heapifyUp(parent);
        }
    }

    int deleteRoot()
    {
        if (root == NULL)
            return -1;

        int deletedAmount = root->amount;

        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
            return deletedAmount;
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

        root->orderID = last->orderID;
        root->customerName = last->customerName;
        root->amount = last->amount;

      
        if (lastParent->right == last)
            lastParent->right = NULL;
        else
            lastParent->left = NULL;

        delete last;

        heapifyDown(root);

        return deletedAmount;
    }

  
    void heapifyDown(Node* temp)
    {
        Node* largest = temp;

        if (temp->left != NULL &&
            temp->left->amount > largest->amount)
        {
            largest = temp->left;
        }

        if (temp->right != NULL &&
            temp->right->amount > largest->amount)
        {
            largest = temp->right;
        }

        if (largest != temp)
        {
            swapOrder(temp, largest);
            heapifyDown(largest);
        }
    }

    
    void heapSort()
    {
        int sorted[100];
        int count = 0;

       
        while (root != NULL)
        {
            sorted[count] = deleteRoot();
            count++;
        }

        cout << "\nOrder Amounts in Ascending Order:\n";

        for (int i = count - 1; i >= 0; i--)
        {
            cout << sorted[i] << " ";
        }
    }
};

int main()
{
    MaxHeap h;

    h.insert(101, "Ali", 4500);
    h.insert(102, "Sara", 1200);
    h.insert(103, "Ahmed", 6500);
    h.insert(104, "Ayesha", 3000);
    h.insert(105, "Usman", 8000);
    h.insert(106, "Hina", 2500);

    h.heapSort();

    return 0;
}
