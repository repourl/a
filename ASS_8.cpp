#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class OBST {
private:
    vector<int> keys;
    vector<double> p, q;
    int n;
    Node* root;
    double optCost;

    Node* createTree(vector<vector<int>>& r, int i, int j) {
        if (i == j)
            return nullptr;
        int rootIdx = r[i][j];
        Node* root = new Node(keys[rootIdx]);
        root->left = createTree(r, i, rootIdx);
        root->right = createTree(r, rootIdx + 1, j);
        return root;
    }

    void printTree(Node* node, int space = 0, int spacing = 6) {
        if (!node) return;
        space += spacing;
        printTree(node->right, space);
        cout << setw(space) << node->key << endl;
        printTree(node->left, space);
    }

    bool search(Node* node, int val) {
        if (!node) return false;
        if (node->key == val) return true;
        return search(node->left, val) || search(node->right, val);
    }

public:
    OBST() : root(nullptr), optCost(0), n(0) {}

    void inputData() {
        cout << "Enter number of keys: ";
        cin >> n;
        keys.resize(n);
        p.resize(n + 1);
        q.resize(n + 1);

        cout << "Enter keys: ";
        for (int i = 0; i < n; i++)
            cin >> keys[i];

        cout << "Enter successful search probabilities (p1 to pn): ";
        for (int i = 1; i <= n; i++)
            cin >> p[i];

        cout << "Enter unsuccessful search probabilities (q0 to qn): ";
        for (int i = 0; i <= n; i++)
            cin >> q[i];

        cout << "Data stored successfully!\n";
    }

    void buildOptimalBST() {
        vector<vector<double>> w(n + 1, vector<double>(n + 1, 0));
        vector<vector<double>> c(n + 1, vector<double>(n + 1, 0));
        vector<vector<int>> r(n + 1, vector<int>(n + 1, 0));

        for (int i = 0; i <= n; i++) {
            w[i][i] = q[i];
            c[i][i] = 0;
            r[i][i] = 0;
        }

        for (int m = 1; m <= n; m++) {
            for (int i = 0; i <= n - m; i++) {
                int j = i + m;
                w[i][j] = w[i][j - 1] + p[j] + q[j];

                double minCost = DBL_MAX;
                int bestRoot = -1;

                for (int k = i; k < j; k++) {
                    double cost = c[i][k] + c[k + 1][j] + w[i][j];
                    if (cost < minCost) {
                        minCost = cost;
                        bestRoot = k;
                    }
                }

                c[i][j] = minCost;
                r[i][j] = bestRoot;
            }
        }

        optCost = c[0][n];
        root = createTree(r, 0, n);
        cout << "Optimal BST built. Cost: " << optCost << endl;
    }

    void displayTree() {
        if (!root) {
            cout << "Error: Compute BST first!\n";
            return;
        }
        cout << "Optimal BST Structure:\n";
        printTree(root);
    }

    void searchKey(int val) {
        if (!root) {
            cout << "Error: Compute BST first!\n";
            return;
        }
        if (search(root, val))
            cout << "Element found.\n";
        else
            cout << "Element not found.\n";
    }
};

int main() {
    OBST obst;
    int choice;

    while (true) {
        cout << "\n----- OPTIMAL BINARY SEARCH TREE MENU -----\n";
        cout << "1. Enter keys and probabilities\n";
        cout << "2. Compute Optimal BST\n";
        cout << "3. Print Optimal BST (Vertically)\n";
        cout << "4. Search an element\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            obst.inputData();
            break;
        case 2:
            obst.buildOptimalBST();
            break;
        case 3:
            obst.displayTree();
            break;
        case 4:
            int val;
            cout << "Enter element to search: ";
            cin >> val;
            obst.searchKey(val);
            break;
        case 5:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}