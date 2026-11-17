
#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    int flightNo;
    string destination;
    string departureTime;

    Node* left;
    Node* right;

    Node(int f, string d, string t)
    {
        flightNo = f;
        destination = d;
        departureTime = t;

        left = NULL;
        right = NULL;
    }
};

class BST
{
public:
    Node* root;

    BST()
    {
        root = NULL;
    }

    Node* insert(Node* root, int f, string d, string t)
    {
        if (root == NULL)
        {
            return new Node(f, d, t);
        }

        if (f < root->flightNo)
        {
            root->left = insert(root->left, f, d, t);
        }
        else if (f > root->flightNo)
        {
            root->right = insert(root->right, f, d, t);
        }
        else
        {
            cout << "Duplicate flight number not allowed!\n";
        }

        return root;
    }
    Node* search(Node* root, int f)
    {
        if (root == NULL || root->flightNo == f)
        {
            return root;
        }

        if (f < root->flightNo)
        {
            return search(root->left, f);
        }
        else
        {
            return search(root->right, f);
        }
    }

    Node* findMin(Node* root)
    {
        if (root == NULL)
        {
            return NULL;
        }

        while (root->left != NULL)
        {
            root = root->left;
        }

        return root;
    }
    Node* deleteFlight(Node* root, int f)
    {
        if (root == NULL)
        {
            return NULL;
        }

        if (f < root->flightNo)
        {
            root->left = deleteFlight(root->left, f);
        }
        else if (f > root->flightNo)
        {
            root->right = deleteFlight(root->right, f);
        }
        else
        {
        
            if (root->left == NULL && root->right == NULL)
            {
                delete root;
                return NULL;
            }

        
            else if (root->left == NULL)
            {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == NULL)
            {
                Node* temp = root->left;
                delete root;
                return temp;
            }

        
            else
            {
                Node* temp = findMin(root->right);

                root->flightNo = temp->flightNo;
                root->destination = temp->destination;
                root->departureTime = temp->departureTime;

                root->right = deleteFlight(root->right, temp->flightNo);
            }
        }

        return root;
    }


    void inorder(Node* root)
    {
        if (root == NULL)
            return;

        inorder(root->left);

        cout << root->flightNo << " | "
             << root->destination << " | "
             << root->departureTime << endl;

        inorder(root->right);
    }


    void preorder(Node* root)
    {
        if (root == NULL)
            return;

        cout << root->flightNo << " | "
             << root->destination << " | "
             << root->departureTime << endl;

        preorder(root->left);
        preorder(root->right);
    }

    void postorder(Node* root)
    {
        if (root == NULL)
            return;

        postorder(root->left);
        postorder(root->right);

        cout << root->flightNo << " | "
             << root->destination << " | "
             << root->departureTime << endl;
    }

   
    void displayMin()
    {
        Node* temp = findMin(root);

        if (temp != NULL)
            cout << "Minimum Flight Number: "
                 << temp->flightNo << endl;
    }
    void displayMax()
    {
        if (root == NULL)
            return;

        Node* temp = root;

        while (temp->right != NULL)
        {
            temp = temp->right;
        }

        cout << "Maximum Flight Number: "
             << temp->flightNo << endl;
    }

    int countFlights(Node* root)
    {
        if (root == NULL)
            return 0;

        return 1 + countFlights(root->left)
                 + countFlights(root->right);
    }

    int height(Node* root)
    {
        if (root == NULL)
            return -1;

        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        if (leftHeight > rightHeight)
            return leftHeight + 1;
        else
            return rightHeight + 1;
    }
    void displayTree(Node* root, int space = 0)
    {
        if (root == NULL)
            return;

        space += 5;

        displayTree(root->right, space);

        cout << endl;

        for (int i = 5; i < space; i++)
        {
            cout << " ";
        }

        cout << root->flightNo << endl;

        displayTree(root->left, space);
    }
};

int main()
{
    BST airport;

    airport.root = airport.insert(airport.root, 50, "London", "08:00 AM");
    airport.root = airport.insert(airport.root, 30, "Dubai", "09:30 AM");
    airport.root = airport.insert(airport.root, 70, "Paris", "10:00 AM");
    airport.root = airport.insert(airport.root, 20, "Tokyo", "11:00 AM");
    airport.root = airport.insert(airport.root, 40, "Istanbul", "12:00 PM");
    airport.root = airport.insert(airport.root, 60, "New York", "01:00 PM");
    airport.root = airport.insert(airport.root, 80, "Toronto", "02:00 PM");
    airport.root = airport.insert(airport.root, 10, "Doha", "03:00 PM");
    airport.root = airport.insert(airport.root, 25, "Rome", "04:00 PM");
    airport.root = airport.insert(airport.root, 35, "Berlin", "05:00 PM");
    airport.root = airport.insert(airport.root, 45, "Madrid", "06:00 PM");
    airport.root = airport.insert(airport.root, 65, "Sydney", "07:00 PM");

    cout << "\n===== AIRPORT FLIGHT SCHEDULING SYSTEM =====\n";

    int key = 45;

    cout << "\nSearching for Flight " << key << endl;

    Node* result = airport.search(airport.root, key);

    if (result != NULL)
    {
        cout << "Flight Found!\n";
        cout << "Flight Number: " << result->flightNo << endl;
        cout << "Destination: " << result->destination << endl;
        cout << "Departure Time: " << result->departureTime << endl;
    }
    else
    {
        cout << "Flight Not Found!\n";
    }

    cout << "\n===== MINIMUM AND MAXIMUM =====\n";
    airport.displayMin();
    airport.displayMax();

    cout << "\n===== TREE INFORMATION =====\n";
    cout << "Total Flights: "
         << airport.countFlights(airport.root) << endl;

    cout << "Height of Tree: "
         << airport.height(airport.root) << endl;

    cout << "\n===== DELETION OPERATIONS =====\n";

    cout << "Deleting Flight 10 (Leaf Node)\n";
    airport.root = airport.deleteFlight(airport.root, 10);

    cout << "Deleting Flight 60 (One Child)\n";
    airport.root = airport.deleteFlight(airport.root, 60);

    cout << "Deleting Flight 30 (Two Children)\n";
    airport.root = airport.deleteFlight(airport.root, 30);

    cout << "\n===== INORDER TRAVERSAL =====\n";
    airport.inorder(airport.root);

    cout << "\n===== PREORDER TRAVERSAL =====\n";
    airport.preorder(airport.root);

    cout << "\n===== POSTORDER TRAVERSAL =====\n";
    airport.postorder(airport.root);

    cout << "\n===== FINAL TREE STRUCTURE =====\n";
    airport.displayTree(airport.root);

    cout << "\nFinal Total Flights: "
         << airport.countFlights(airport.root) << endl;

    cout << "Final Height: "
         << airport.height(airport.root) << endl;

    return 0;
}
