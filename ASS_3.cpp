#include <iostream>
#include <queue>
using namespace std;

// Now: isLeftThread == true means left pointer is a thread, false means real child.
//       isRightThread == true means right pointer is a thread, false means real child.
struct TreeNode {
    int value;
    TreeNode *left, *right;
    bool isLeftThread, isRightThread;
    TreeNode(int v)
      : value(v), left(nullptr), right(nullptr),
        isLeftThread(true), isRightThread(true)  // start as threads
    {}
};

// Insert key into the threaded BST
void insertNode(TreeNode *&root, int key) {
    if (!root) {
        root = new TreeNode(key);
        return;
    }
    TreeNode *parent = nullptr, *cur = root;
    while (true) {
        if (key == cur->value) return;  // no duplicates
        parent = cur;
        if (key < cur->value) {
            if (!cur->isLeftThread)  // real child exists
                cur = cur->left;
            else
                break;
        } else {
            if (!cur->isRightThread)
                cur = cur->right;
            else
                break;
        }
    }
    TreeNode *node = new TreeNode(key);
    if (key < parent->value) {
        // new node threads
        node->left = parent->left;
        node->right = parent;
        // attach as child
        parent->left = node;
        parent->isLeftThread = false;
    } else {
        node->right = parent->right;
        node->left = parent;
        parent->right = node;
        parent->isRightThread = false;
    }
}



// Get inorder successor via threads or right subtree
TreeNode* inorderSuccessor(TreeNode *node) {
    if (node->isRightThread)
        return node->right;
    node = node->right;
    while (!node->isLeftThread)
        node = node->left;
    return node;
}

// Inorder traversal without recursion/stack
void inorder(TreeNode *root) {
    if (!root) return;
    // move to leftmost
    TreeNode *cur = root;
    while (!cur->isLeftThread)
        cur = cur->left;
    while (cur) {
        cout << cur->value << " ";
        cur = inorderSuccessor(cur);
    }
    cout << "\n";
}

// Preorder traversal without recursion/stack


void preorder(TreeNode *root) {
    TreeNode *cur = root;
    while (cur) {
        cout << cur->value << " ";
        if (!cur->isLeftThread)
            cur = cur->left;
        else if (!cur->isRightThread)
            cur = cur->right;
        else {

            // backtrack via threads
            while (cur && cur->isRightThread)
                cur = cur->right;
            if (cur) cur = cur->right;
        }
    }

    cout << "\n";
}


                                                                                                                                                                                                                                                                                               
                  


// Find node and its parent
bool findWithParent(TreeNode *root, int key, TreeNode *&parent, TreeNode *&target) {
    parent = nullptr;
    target = root;
    while (target) {
        if (key == target->value) return true;
        parent = target;
        if (key < target->value && !target->isLeftThread)
            target = target->left;
        else if (key > target->value && !target->isRightThread)
            target = target->right;
        else
            break;
    }
    return false;
}

// Delete a node, updating threads
void deleteNode(TreeNode *&root, int key) {
    TreeNode *parent, *target;
    if (!findWithParent(root, key, parent, target)) {
        cout << "Key " << key << " not found.\n";
        return;
    }
    
    // Case: two children
    if (!target->isLeftThread && !target->isRightThread) {
        TreeNode *ps = target, *succ = target->right;
        while (!succ->isLeftThread) {
            ps = succ;
            succ = succ->left;
        }
        target->value = succ->value;
        key = succ->value;
        parent = ps;
        target = succ;
    }
    // One or zero real children
    TreeNode *child = nullptr;
    if (!target->isLeftThread)
        child = target->left;
    else if (!target->isRightThread)
        child = target->right;

    if (!parent)
        root = child;
    else if (parent->left == target) {
        if (child) parent->left = child;
        else {
            parent->isLeftThread = true;
            parent->left = target->left;
        }
    } else {
        if (child) parent->right = child;
        else {
            parent->isRightThread = true;
            parent->right = target->right;
        }
    }
    delete target;
}

int main() {
    TreeNode *root = nullptr;
    int choice, x;
    do {
        cout << "\n--- MENU ---\n"
             << "1. Insert node\n"
             << "2. Delete node\n"
             << "3. Inorder (non-recursive)\n"
             << "4. Preorder (non-recursive)\n"
             << "5. Exit\n"
             << "Choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Value to insert: "; cin >> x;
                insertNode(root, x);
                break;
            case 2:
                cout << "Value to delete: "; cin >> x;
                deleteNode(root, x);
                break;
            case 3:
                cout << "Inorder: "; inorder(root);
                break;
            case 4:
                cout << "Preorder: "; preorder(root);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);
    return 0;
}
