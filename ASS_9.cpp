#include <iostream>
#include <string>
using namespace std;

struct Node {
    string key;
    string meaning;
    Node* left;
    Node* right;
    int height;
};

// Create a new node
Node* createNode(string key, string meaning) {
    Node* temp = new Node();
    temp->key = key;
    temp->meaning = meaning;
    temp->left = temp->right = nullptr;
    temp->height = 0;
    return temp;
}

// Get height of a node
int getHeight(Node* T) {
    if (T == nullptr)
        return -1;
    return T->height;
}

// Balance factor
int getBalance(Node* T) {
    if (T == nullptr)
        return 0;
    return getHeight(T->left) - getHeight(T->right);
}

// Update height
int updateHeight(Node* T) {
    return max(getHeight(T->left), getHeight(T->right)) + 1;
}

// Right rotate
Node* rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    x->height = updateHeight(x);
    y->height = updateHeight(y);
    return y;
}

// Left rotate
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = updateHeight(x);
    y->height = updateHeight(y);
    return y;
}

// Left-Right rotate
Node* rotateLeftRight(Node* T) {
    T->left = rotateLeft(T->left);
    return rotateRight(T);
}

// Right-Left rotate
Node* rotateRightLeft(Node* T) {
    T->right = rotateRight(T->right);
    return rotateLeft(T);
}

// Insert a node
Node* insert(Node* T, string key, string meaning) {
    if (T == nullptr)
        return createNode(key, meaning);

    if (key < T->key)
        T->left = insert(T->left, key, meaning);
    else if (key > T->key)
        T->right = insert(T->right, key, meaning);
    else
        return T; // No duplicates allowed

    T->height = updateHeight(T);

    int balance = getBalance(T);

    // LL
    if (balance > 1 && key < T->left->key)
        return rotateRight(T);

    // RR
    if (balance < -1 && key > T->right->key)
        return rotateLeft(T);

    // LR
    if (balance > 1 && key > T->left->key)
        return rotateLeftRight(T);

    // RL
    if (balance < -1 && key < T->right->key)
        return rotateRightLeft(T);

    return T;
}

// In-order display (ascending)
void displayAscending(Node* root) {
    if (root) {
        displayAscending(root->left);
        cout << root->key << " : " << root->meaning << endl;
        displayAscending(root->right);
    }
}

// Reverse in-order display (descending)
void displayDescending(Node* root) {
    if (root) {
        displayDescending(root->right);
        cout << root->key << " : " << root->meaning << endl;
        displayDescending(root->left);
    }
}

// Search keyword with comparisons
bool search(Node* root, string key, int& comparisons) {
    comparisons = 0;
    while (root) {
        comparisons++;
        if (key == root->key) {
            cout << "Found! Meaning: " << root->meaning << endl;
            return true;
        } else if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    cout << "Keyword not found!" << endl;
    return false;
}

// Max comparisons = height + 1 (worst case path length)
int maxComparisons(Node* root) {
    return getHeight(root) + 1;
}

int main() {
    Node* root = nullptr;
    int choice;
    string key, meaning;

    do {
        cout << "\nDictionary (AVL Tree) Menu\n";
        cout << "1. Insert keyword\n";
        cout << "2. Display (Ascending Order)\n";
        cout << "3. Display (Descending Order)\n";
        cout << "4. Search for a keyword\n";
        cout << "5. Max Comparisons Required\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, key);
                cout << "Enter meaning: ";
                getline(cin, meaning);
                root = insert(root, key, meaning);
                cout << "Keyword added successfully!\n";
                break;

            case 2:
                cout << "\nDictionary in Ascending Order:\n";
                displayAscending(root);
                break;

            case 3:
                cout << "\nDictionary in Descending Order:\n";
                displayDescending(root);
                break;

            case 4: {
                cout << "Enter keyword to search: ";
                getline(cin, key);
                int comparisons = 0;
                search(root, key, comparisons);
                cout << "Comparisons made: " << comparisons << endl;
                break;
            }

            case 5:
                cout << "Maximum comparisons required: " << maxComparisons(root) << endl;
                break;

            case 6:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
