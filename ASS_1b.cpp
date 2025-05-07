#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

// Node of the expression tree
typedef struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char c) : data(c), left(nullptr), right(nullptr) {}
} Node;

// Build tree from prefix expression
Node* buildTree(const string& expr, int& idx) {
    // Skip whitespace
    while (idx < (int)expr.size() && isspace(expr[idx]))
        idx++;
    if (idx >= (int)expr.size()) return nullptr;

    char c = expr[idx++];
    Node* node = new Node(c);
    if (c=='+'||c=='-'||c=='*'||c=='/'||c=='^') {
        node->left  = buildTree(expr, idx);
        node->right = buildTree(expr, idx);
    }
    return node;
}

// Non-recursive postorder traversal
void postOrderNonRecursive(Node* root) {
    if (!root) return;
    stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node* n = s1.top(); s1.pop();
        s2.push(n);
        if (n->left)  s1.push(n->left);
        if (n->right) s1.push(n->right);
    }
    cout << "Post-order (non-recursive): ";
    while (!s2.empty()) {
        cout << s2.top()->data << ' ';
        s2.pop();
    }
    cout << "\n";
}

// Count operands and operators
void countNodes(Node* node, int& operands, int& operators) {
    if (!node) return;
    if (node->data=='+'||node->data=='-'||node->data=='*'||node->data=='/'||node->data=='^')
        operators++;
    else
        operands++;
    countNodes(node->left, operands, operators);
    countNodes(node->right, operands, operators);
}

// Delete tree
void deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    Node* root = nullptr;
    string prefix;
    bool built = false;
    int choice;

    do {
        cout << "\n=== Expression Tree Menu ===\n";
        cout << "1. Enter prefix expression\n";
        cout << "2. Non-recursive postorder traversal\n";
        cout << "3. Count operands\n";
        cout << "4. Count operators\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice) {
            case 1:
                // enter and build
                if (root) {
                    deleteTree(root);
                    root = nullptr;
                    built = false;
                }
                cout << "Enter prefix expression (e.g. +-a*bc/def): ";
                getline(cin, prefix);
                {
                    int idx = 0;
                    root = buildTree(prefix, idx);
                    built = true;
                    cout << "Expression tree built.\n";
                }
                break;

            case 2:
                if (!built) {
                    cout << "Build the tree first (option 1).\n";
                } else {
                    postOrderNonRecursive(root);
                }
                break;

            case 3:
                if (!built) {
                    cout << "Build the tree first (option 1).\n";
                } else {
                    int opnds = 0, oprs = 0;
                    countNodes(root, opnds, oprs);
                    cout << "Number of operands: " << opnds << "\n";
                }
                break;

            case 4:
                if (!built) {
                    cout << "Build the tree first (option 1).\n";
                } else {
                    int opnds = 0, oprs = 0;
                    countNodes(root, opnds, oprs);
                    cout << "Number of operators: " << oprs << "\n";
                }
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    if (root) deleteTree(root);
    return 0;
}
