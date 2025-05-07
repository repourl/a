#include <bits/stdc++.h>
using namespace std;

class binaryTree;

class treenode {
    int val;
    treenode *llink, *rlink;

public:
    treenode(int val) {
        this->val = val;
        llink = nullptr;
        rlink = nullptr;
    }
    friend class binaryTree;
};

class binaryTree {
    treenode *root;
    int leafc, intnodes;

public:
    binaryTree() {
        root = nullptr;
        leafc = 0;
        intnodes = 0;
    }

    binaryTree(const binaryTree &other) {
        root = copyTree(other.root);
    }

    binaryTree &operator=(binaryTree &other) {
        if (this != &other) {
            eraseTree(root);
            root = copyTree(other.root);
        }
        return *this;
    }

    ~binaryTree() {
        eraseTree(root);
    }

    void eraseTree(treenode *node) {
        if (!node) return;
        eraseTree(node->llink);
        eraseTree(node->rlink);
        delete node;
    }

    treenode *copyTree(treenode *node) {
        if (!node) return nullptr;
        treenode *newNode = new treenode(node->val);
        newNode->llink = copyTree(node->llink);
        newNode->rlink = copyTree(node->rlink);
        return newNode;
    }

    void createBinaryTree() {
        cout << "Enter Root Value: ";
        int value;
        cin >> value;
        if (value == 0) return;

        root = new treenode(value);
        queue<treenode *> q;
        q.push(root);

        while (!q.empty()) {
            treenode *parent = q.front(); q.pop();
            cout << "Enter Left child of " << parent->val << " (0 for NULL): ";
            int left; cin >> left;
            if (left != 0) {
                parent->llink = new treenode(left);
                q.push(parent->llink);
            }

            cout << "Enter Right child of " << parent->val << " (0 for NULL): ";
            int right; cin >> right;
            if (right != 0) {
                parent->rlink = new treenode(right);
                q.push(parent->rlink);
            }
        }
    }

    void printBinaryTree() {
        if (!root) return;
        queue<treenode *> q;
        q.push(root); q.push(nullptr);
        while (!q.empty()) {
            treenode *node = q.front(); q.pop();
            if (node) {
                cout << node->val << " ";
                if (node->llink) q.push(node->llink);
                if (node->rlink) q.push(node->rlink);
            } else {
                cout << "\n";
                if (!q.empty()) q.push(nullptr);
            }
        }
    }

    void preorder(treenode *node) {
        if (!node) return;
        cout << node->val << " ";
        preorder(node->llink);
        preorder(node->rlink);
    }

    void inorder(treenode *node) {
        if (!node) return;
        inorder(node->llink);
        cout << node->val << " ";
        inorder(node->rlink);
    }

    void postorder(treenode *node) {
        if (!node) return;
        postorder(node->llink);
        postorder(node->rlink);
        cout << node->val << " ";
    }

    void iterativePreorder(treenode *node) {
        if (!node) return;
        stack<treenode *> st;
        while (node || !st.empty()) {
            while (node) {
                cout << node->val << " ";
                if (node->rlink) st.push(node->rlink);
                node = node->llink;
            }
            
            if (!st.empty()) {
                node = st.top(); st.pop();
            }
        }
    }

    void iterativeInorder(treenode *node) {
        if (!node) return;
        stack<treenode *> st;
        while (node || !st.empty()) {
            while (node) {
                st.push(node);
                node = node->llink;
            }
            node = st.top(); st.pop();
            cout << node->val << " ";
            node = node->rlink;
        }
    }

    void iterativePostorder(treenode *node) {
        if (!node) return;
        stack<treenode *> s1, s2;
        s1.push(node);
        while (!s1.empty()) {
            treenode *curr = s1.top(); s1.pop();
            s2.push(curr);
            if (curr->llink) s1.push(curr->llink);
            if (curr->rlink) s1.push(curr->rlink);
        }
        while (!s2.empty()) {
            cout << s2.top()->val << " ";
            s2.pop();
        }
    }

    void leafcount(treenode *node) {
        if (!node) return;
        if (!node->llink && !node->rlink) {
            leafc++;
        } else {
            intnodes++;
        }
        leafcount(node->llink);
        leafcount(node->rlink);
    }

    void leafcountmember() {
        leafc = 0;
        leafcount(root);
        cout << "Leaf nodes count: " << leafc << endl;
    }

    void internalnodes() {
        intnodes = 0;
        leafcount(root);
        cout << "Internal nodes count: " << intnodes << endl;
    }

    int height(treenode *node) {
        if (!node) return 0;
        int lh = height(node->llink);
        int rh = height(node->rlink);
        return max(lh, rh) + 1;
    }

    void BT_height() {
        int h = height(root);
        cout << "Height (recursive): " << h << endl;
    }

    void btheightiterative() {
        if (!root) {
            cout << "Height: 0\n";
            return;
        }
        queue<treenode *> q;
        q.push(root);
        int height = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                treenode *node = q.front(); q.pop();
                if (node->llink) q.push(node->llink);
                if (node->rlink) q.push(node->rlink);
            }
            height++;
        }
        cout << "Height (iterative): " << height << endl;
    }

    void swaptree(treenode *node) {
        if (!node) return;
        swap(node->llink, node->rlink);
        swaptree(node->llink);
        swaptree(node->rlink);
    }

    void SwapTreemember() {
        swaptree(root);
        cout << "Tree has been mirrored.\n";
    }

    // Wrapper Methods for Menu
    void inordermember() { cout << "Inorder: "; inorder(root); cout << endl; }
    void preordermember() { cout << "Preorder: "; preorder(root); cout << endl; }
    void postordermember() { cout << "Postorder: "; postorder(root); cout << endl; }
    void iterativeinordermember() { cout << "Iterative Inorder: "; iterativeInorder(root); cout << endl; }
    void iterativepreordermember() { cout << "Iterative Preorder: "; iterativePreorder(root); cout << endl; }
    void iterativepostordermember() { cout << "Iterative Postorder: "; iterativePostorder(root); cout << endl; }
};

int main() {
    binaryTree bt;
    int choice;

    while (true) {
        cout << "\n--- Binary Tree Menu ---\n";
        cout << "1. Create Binary Tree\n";
        cout << "2. Recursive Inorder\n";
        cout << "3. Recursive Preorder\n";
        cout << "4. Recursive Postorder\n";
        cout << "5. Iterative Inorder\n";
        cout << "6. Iterative Preorder\n";
        cout << "7. Iterative Postorder\n";
        cout << "8. Leaf Count\n";
        cout << "9. Internal Nodes Count\n";
        cout << "10. Tree Height (Recursive)\n";
        cout << "11. Tree Height (Iterative)\n";
        cout << "12. Swap Left & Right Subtrees\n";
        cout << "13. Print Tree Level-wise\n";
        cout << "14. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bt.createBinaryTree(); break;
            case 2: bt.inordermember(); break;
            case 3: bt.preordermember(); break;
            case 4: bt.postordermember(); break;
            case 5: bt.iterativeinordermember(); break;
            case 6: bt.iterativepreordermember(); break;
            case 7: bt.iterativepostordermember(); break;
            case 8: bt.leafcountmember(); break;
            case 9: bt.internalnodes(); break;
            case 10: bt.BT_height(); break;
            case 11: bt.btheightiterative(); break;
            case 12: bt.SwapTreemember(); break;
            case 13: bt.printBinaryTree(); break;
            case 14: exit(0);
            default: cout << "Invalid choice!\n";
        }
    }

    return 0;
}
