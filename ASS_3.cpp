#include <queue>
#include <bits/stdc++.h>
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode* left_child;
    TreeNode* right_child;
    bool isLeftThread;
    bool isRightThread;

    TreeNode(int val) : value(val), left_child(NULL), right_child(NULL), isLeftThread(false), isRightThread(false) {}
};

TreeNode* find_min(TreeNode* root) {
    while (root->left_child != NULL && root->isLeftThread) {
        root = root->left_child;
    }
    return root;
}

TreeNode* find_max(TreeNode* root) {
    while (root->right_child != NULL && root->isRightThread) {
        root = root->right_child;
    }
    return root;
}

void add_node(TreeNode* root, int new_value) {
    if (root->value > new_value) {
        if (root->left_child && root->isLeftThread) add_node(root->left_child, new_value);
        else {
            root->isLeftThread = true;
            TreeNode* new_node = new TreeNode(new_value);
            new_node->left_child = root->left_child;
            new_node->right_child = root;
            root->left_child = new_node;
        }
    } else {
        if (root->right_child && root->isRightThread) add_node(root->right_child, new_value);
        else {
            root->isRightThread = true;
            TreeNode* new_node = new TreeNode(new_value);
            new_node->right_child = root->right_child;
            new_node->left_child = root;
            root->right_child = new_node;
        }
    }
}

void display_ascending(TreeNode* root) {
    while (root->left_child && root->isLeftThread) {
        root = root->left_child;
    }

    while (root) {
        cout << root->value << " ";
        if (root->isRightThread) {
            root = root->right_child;

            while (root->left_child && root->isLeftThread) {
                root = root->left_child;
            }
        } else {
            root = root->right_child;
        }
    }
}

void display_descending(TreeNode* root) {
    while (root->right_child && root->isRightThread) {
        root = root->right_child;
    }

    while (root) {
        cout << root->value << " ";
        if (root->isLeftThread) {
            root = root->left_child;

            while (root->right_child && root->isRightThread) {
                root = root->right_child;
            }
        } else {
            root = root->left_child;
        }
    }
}

void display_level_order(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            cout << node->value << " ";
            if (node->isLeftThread && node->left_child != NULL) q.push(node->left_child);
            if (node->isRightThread && node->right_child != NULL) q.push(node->right_child);
            q.pop();
        }
        cout << endl;
    }
}

TreeNode* successor_inorder(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left_child != NULL && current->isLeftThread) {
        current = current->left_child;
    }
    return current;
}

TreeNode* remove_node(TreeNode* root, int target_value) {
    if (root == NULL) return NULL;

    if (target_value < root->value && root->isLeftThread) {
        root->left_child = remove_node(root->left_child, target_value);
    } else if (target_value > root->value && root->isRightThread) {
        root->right_child = remove_node(root->right_child, target_value);
    } else if (target_value == root->value) {
        if (root->isLeftThread && root->isRightThread) {
            TreeNode* temp = successor_inorder(root->right_child);
            root->value = temp->value;
            root->right_child = remove_node(root->right_child, temp->value);
        } else {
            TreeNode* temp = NULL;
            if (root->isLeftThread) {
                temp = root->left_child;
            } else if (root->isRightThread) {
                temp = root->right_child;
            }
            delete root;
            return temp;
        }
    }

    return root;

}
void display_preorder(TreeNode* root) {
    if (root == NULL) return;

    stack<TreeNode*> s;
    s.push(root);

    while (!s.empty()) {
        TreeNode* node = s.top();
        s.pop();
        cout << node->value << " ";

        // Push right child first, so left child is processed first.
        if (node->isRightThread && node->right_child != NULL) s.push(node->right_child);
        if (node->isLeftThread && node->left_child != NULL) s.push(node->left_child);
    }
    cout << endl;
}
void display_inorder(TreeNode* root) {
    stack<TreeNode*> s;
    TreeNode* current = root;

    while (current != NULL || !s.empty()) {
        // Reach the leftmost node
        while (current != NULL) {
            s.push(current);
            if (current->isLeftThread) current = current->left_child;
            else break;
        }


        current = s.top();
        s.pop();
        cout << current->value << " ";

        // Move to the right node
        if (current->isRightThread) current = current->right_child;
        else current = current->right_child;
    }
    cout << endl;
}

int search_value(int key, TreeNode* root) {
    int lookup_count = 0;
    TreeNode* current = root;

    while (current != NULL) {
        lookup_count += 1;
        if (current->value == key) return lookup_count;
        else if (current->value > key && current->isLeftThread) current = current->left_child;
        else if (current->value < key && current->isRightThread) current = current->right_child;
        else current = NULL;
    }

    return -lookup_count;
}

int main() {
    string menuText = "Available Options:-\n"
        "(1) Add Node\n"
        "(2) Search for Node\n"
        "(3) Display Preorder (Non-Recursive)\n"
        "(4) Display Inorder (Non-Recursive)\n"
        "(5) Display Level Order\n"
        "(6) Remove Node\n"
        "(7) Exit\n"
        ;

    int root_value;
    cout << "Enter root node value: ";
    cin >> root_value;

    TreeNode *root = new TreeNode(root_value);

    cout << menuText;
    while (true) {
        int option;
        cout << "Choose an operation: ";
        cin >> option;

        int value, lookups;

        switch (option) {
            case 1:
                cout << "Node value to add: ";
                cin >> value;
                add_node(root, value);
                break;
            case 2:
                cout << "Node value to search: ";
                cin >> value;
                lookups = search_value(value, root);
                if (lookups < 0) cout << "Node not found (Lookups = " << -lookups << ")" << endl;
                else cout << "Node found! (Lookups = " << lookups << ")" << endl;
                break;
            case 3:
            	display_preorder(root);
                cout << endl;
                break;
            case 4:
            	display_ascending(root);
                cout << endl;
                break;
            case 5:
                display_level_order(root);
                break;
            case 6:
                cout << "Node value to remove: ";
                cin >> value;
                remove_node(root, value);
                break;
            case 7:
            	break;
            default:
                cout << "Invalid operation!" << endl;
                break;
        }
    }

    return 0;
}

