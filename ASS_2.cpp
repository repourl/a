#include <bits/stdc++.h>
using namespace std;
   int count;

class treenode {
public:
    int val;
    treenode* llink;
    treenode* rlink;
    treenode(int val) {
        this->val = val;
        llink = nullptr;
        rlink = nullptr;
//        count=0;
    }
};

class BST {
    treenode* root;

public:
    BST() {
        root = nullptr;
    }

    void insert(int value) {
        treenode* child = new treenode(value);
        if (root == nullptr) {
            root = child;
            return;
        }
        treenode* parent = root;

        while (true) {
            if (child->val < parent->val) {
                if (parent->llink == nullptr) {
                    parent->llink = child;
                    break;
                } else {
                    parent = parent->llink;
                }
            } else if (child->val > parent->val) {
                if (parent->rlink == nullptr) {
                    parent->rlink = child;
                    break;
                } else {
                    parent = parent->rlink;
                }
            } else {
                cout << "Duplicate value not allowed!" << endl;
                delete child; // Free memory of duplicate node
                break;
            }
        }
    }

    int longesthelp(treenode* t) {
        if (t == nullptr) return 0;
        int l = 1 + longesthelp(t->llink);
        int r = 1 + longesthelp(t->rlink);
        return max(l, r);
    }

    void SwapTreemember() {
        partition();
        swaptree(this->root);
        cout << "\nSwapped Binary Tree is\n";
        partition();
        printBinaryTree();
    }

    void swaptree(treenode *root) {
        if (root == nullptr) return;
        treenode *temp = root->llink;
        root->llink = root->rlink;
        root->rlink = temp;

        swaptree(root->llink);
        swaptree(root->rlink);
    }

    void LongestNodeinPath() {
        partition();
        cout << "Number of node in longest path is : " << longesthelp(root) << endl;
        partition();
    }

    int minfind(treenode * t) {
        if (t->llink == nullptr) return t->val;
        return minfind(t->llink);
    }

    int maxfind(treenode * t) {
        if (t->rlink == nullptr) return t->val;
        return maxfind(t->rlink);
    }

    void MinMaxIntree() {
        partition();
        cout << "Minimum element in the BST is: " << minfind(root) << endl;
        cout << "Maximum element in the BST is: " << maxfind(root) << endl;
        partition();
    }

    bool recursiveSearch(int target, treenode* t,int& count) {
        if (t == nullptr) return false;
        if (t->val == target) return true;
        count+=1;
        if (target < t->val)
            return recursiveSearch(target, t->llink,count);
        else
            return recursiveSearch(target, t->rlink,count);
    }

    void partition() {
        cout << "----------------------------------------------------" << endl;
    }

    void searchElement() {
        partition();
        int target;
        int count=0;
        cout << "\nEnter element to search:" << endl;
        cin >> target;
        bool found = recursiveSearch(target, root,count);
        if (found) {
            cout << "\nElement is found." << endl;
            cout<<"\nIteration required is: "<<count<<endl;
        } else {
            cout << "\nElement is not found." << endl;
//            cout<<"\nIteration required is: "<<count<<endl;
        }
        partition();
    }

    void printBinaryTree() {
//        partition();
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }

        queue<treenode*> q;
        q.push(root);
        q.push(nullptr);

        while (!q.empty()) {
            if (q.front() != nullptr) {
                treenode* parent = q.front();
                int value = parent->val;
                q.pop();
                cout << value << " ";
                if (parent->llink) {
                    q.push(parent->llink);
                }
                if (parent->rlink) {
                    q.push(parent->rlink);
                }
            } else {
                q.pop();
                cout << endl;
                if (!q.empty()) {
                    q.push(nullptr);
                }
            }
        }
    }

    void deletemember(int data) {
        cout << "Deleting node with value " << data << endl;

        treenode* child = root;
        treenode* parent = nullptr;
        while (child && child->val != data) {
            parent = child;
            if (data < child->val) {
                child = child->llink;
            } else {
                child = child->rlink;
            }
        }

        if (!child) {
            cout << "Node not found!" << endl;
            return;
        }

        if (child->llink == nullptr && child->rlink == nullptr) {

            if (child == root) {
                root = nullptr;
            } else if (parent->llink == child) {
                parent->llink = nullptr;
            } else {
                parent->rlink = nullptr;
            }
            delete child;
        } else if (child->llink && !child->rlink) {

            if (child == root) {
                root = child->llink;
            } else if (parent->llink == child) {
                parent->llink = child->llink;
            } else {
                parent->rlink = child->llink;
            }
            delete child;
        } else if (child->rlink && !child->llink) {

            if (child == root) {
                root = child->rlink;
            } else if (parent->llink == child) {
                parent->llink = child->rlink;
            } else {
                parent->rlink = child->rlink;
            }
            
            delete child;
        } else {

            treenode* successor = child->rlink;
            treenode* successorParent = child;

            while (successor->llink != nullptr) {
                successorParent = successor;
                successor = successor->llink;
            }

            child->val = successor->val;

            if (successorParent->llink == successor) {
                successorParent->llink = successor->rlink;
            }
            else {
                successorParent->rlink = successor->rlink;
            }
            delete successor;
        }

        printBinaryTree();
    }

    void input() {
        while (true) {
            int value;
            cout << "Enter Node (or -1 to stop): ";
            cin >> value;

            if (value == -1) {
                break;
            } else {
                insert(value);
            }
        }

        printBinaryTree();
    }
};

int main() {
    cout << "Binary Search Tree Operations\n";
    BST b;
    int choice;
    do {
        cout << "1) Create BST. \n";
        cout << "2) Insert a new node\n";
        cout << "3) Find numbers of node in longest path\n";
        cout << "4) Minimum and maximum data value found in tree\n";
        cout << "5) Swap every node\n";
        cout << "6) Search an element\n";
        cout << "7) Delete node.\n";
        cout << "8) Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            b.input();
            break;
        case 2:
            cout << "\nEnter element to insert: ";
            int ele;
            cin >> ele;
            b.insert(ele);
            break;
        case 3:
            b.LongestNodeinPath();
            break;
        case 4:
            b.MinMaxIntree();
            break;
        case 5:
            b.SwapTreemember();
            break;
        case 6:
            b.searchElement();
            break;
        case 7:
            int data;
            cout << "Enter number to be deleted: ";
            cin >> data;
            b.deletemember(data);
            break;
        case 8:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid input.\n";
            break;
        }
    } while (choice != 8);

    return 0;
}
