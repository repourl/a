#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class binaryTree; // Forward declaration of binaryTree class

class treenode
{
    int val;
    treenode *llink;
    treenode *rlink;

public:
    // Constructor
    treenode(int val)
    {
        this->val = val;
        llink = nullptr;
        rlink = nullptr;
    }

    // Declare binaryTree as a friend to access private members
    friend class binaryTree;
};

class binaryTree
{
private:
    treenode *root;
    int height;
    int leafc;
    int intnodes;

public:
    // Constructor to initialize the tree
    binaryTree()
    {
        root = nullptr;
        height = 0;
        leafc = 0;
        intnodes = 0;
    }

    binaryTree(const binaryTree &other)
    {
        root = copyTree(other.root);
    }

    binaryTree &operator=(const binaryTree &other)
    {
        if (this != &other)
        {
            eraseTree(root);             // First erase the current tree
            root = copyTree(other.root); // Then copy the new tree
        }
        return *this;
    }


    treenode *copyTree(treenode *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        treenode *newNode = new treenode(node->val);
        newNode->llink = copyTree(node->llink);
        newNode->rlink = copyTree(node->rlink);
        return newNode;
    }



void eraseTreemember(){
    eraseTree(root);
}
    void eraseTree(treenode *node)
    {
        if (node == nullptr)
        {
            return;
        }
        eraseTree(node->llink);
        eraseTree(node->rlink);
        delete node;
    }

    // Erase tree (non-recursive method)
  void eraseTreeNonRecursive() {
    if (root == nullptr) return;

    stack<treenode*> s;
    s.push(root);

    while (!s.empty()) {
        treenode* node = s.top();
        s.pop();

        if (node->llink)
            s.push(node->llink);
        if (node->rlink)
            s.push(node->rlink);

        delete node;
    }

    root = nullptr; // Very important!
}

    void leafcountmember()
    {
        leafc = 0;
        leafcount(root);
        cout << "Total NUmber of leaf are: " << leafc << endl;
//        internalnodes(root);
    }
    void internalnodes()
    {
        intnodes = 0;
        leafcount(root);
        cout << "Total Number of internal nodes are: " << intnodes << endl;
    }
void leafcountNonRecursive(treenode* root) {
    if (root == nullptr)
        return;

    stack<treenode*> s;
    s.push(root);

    while (!s.empty()) {
        treenode* node = s.top();
        s.pop();

        // If it's a leaf node
        if (node->llink == nullptr && node->rlink == nullptr) {
            leafc++;
        }
        else {
            intnodes++; // Internal node
            if (node->llink)
                s.push(node->llink);
            if (node->rlink)
                s.push(node->rlink);
        }
    }
}



    void leafcount(treenode *root)
    {
        if (root == nullptr)
            return;
        if (root->llink)
        {
            leafcount(root->llink);
        }
        if (root->rlink)
        {
            leafcount(root->rlink);
        }
        if (!root->llink && !root->rlink)
        {
            leafc++;
        }
        else
        {
            intnodes++;
        }
    }


    // Preorder Traversal
    void preordermember()
    {
        cout << "\nPreorder Traversal is: " << endl;
        preorder(root);
    }
    void preorder(treenode *root)
    {
        if (root == nullptr)
            return;
        cout << root->val << " ";
        preorder(root->llink);
        preorder(root->rlink);
    }
    void inorder(treenode *root)
    {
        if (root == nullptr)
            return;
        inorder(root->llink);
        cout << root->val << " ";
        inorder(root->rlink);
    }

    void postorder(treenode *root)
    {
        if (root == nullptr)
            return;
        postorder(root->llink);
        postorder(root->rlink);
        cout << root->val << " ";
    }
    // Inorder Traversal
    void inordermember()
    {
        cout << "\nInorder Traversal is: " << endl;
        inorder(root);
    }

    // Postorder Traversal
    void postordermember()
    {
        cout << "\nPostorder Traversal is: " << endl;
        postorder(root);
    }
    void iterativepreordermember()
    {
        cout << "\nIterative Preorder Traversal is: " << endl;
        iterativepreorder(root);
    }
    void iterativeinordermember()
    {
        cout << "\nIterative Inorder Traversal is: " << endl;
        iterativeinorder(root);
    }
    void iterativepreorder(treenode *t)
    {
        stack<treenode *> s;

        while (1)
        {

            while (t != nullptr)
            {
                cout << t->val << " ";
                if (t->rlink != nullptr)
                    s.push(t->rlink);
                t = t->llink;
            }
            if (s.empty())
                return;

            t = s.top();
            s.pop();
        }
    }
    void iterativeinorder(treenode *t)
    {
        stack<treenode *> s;

        while (1)
        {

            while (t != nullptr)
            {
                // cout<<t->val;
                s.push(t);
                t = t->llink;
            }
            if (s.empty())
                return;
            t = s.top();
            s.pop();
            cout << t->val << " ";
            t = t->rlink;
        }
    }

    void postOrderIterative(treenode *root)
    {
        if (root == nullptr)
            return;

        stack<treenode *> s1, s2;
        s1.push(root);

        // Traverse the tree
        while (!s1.empty())
        {
            treenode *node = s1.top();
            s1.pop();
            s2.push(node);

            // Push left and right children of the popped node
            if (node->llink != nullptr)
                s1.push(node->llink);
            if (node->llink != nullptr)
                s1.push(node->rlink);
        }

        // Print the nodes in post-order (right, left, root)
        while (!s2.empty())
        {
            cout << s2.top()->val << " ";
            s2.pop();
        }
    }

    // Function to create a new node
    treenode *newNode(int val)
    {
        return new treenode(val);
    }
    void createBinaryTree()
    {
        queue<treenode *> q;
        cout << "Enter Root Value: ";
        int value;
        cin >> value;
        treenode *newnode = new treenode(value);
        root = newnode;
        q.push(root);

        while (!q.empty())
        {
            treenode *parent = q.front();
            int value = parent->val;
            q.pop();

            int left, right;
            cout << "Enter Left child of " << value << " otherwise 0: ";
            cin >> left;
            if (left != 0)
            {
                treenode *leftchild = new treenode(left);
                parent->llink = leftchild;
                q.push(leftchild);
            }

            cout << "Enter Right child of " << value << " otherwise 0: ";
            cin >> right;
            if (right != 0)
            {
                treenode *rightchild = new treenode(right);
                parent->rlink = rightchild;
                q.push(rightchild);
            }
        }
    }
    void BT_height()
    {
        if (root == nullptr)
        {
            cout << "Height of binary tree is : 0 " << endl;
        }

        int temp = btheight(root);
        cout << "Height of binary tree is : " << temp << endl;
    }
    int btheight(treenode *root)
    {
        if (root == nullptr)
            return 1;
        int l = 1, r = 1;
        if (root->llink)
        {
            l += btheight(root->llink);
        }
        if (root->rlink)
        {
            r += btheight(root->rlink);
        }
        int hh = max(l, r);
        return hh;
    }

    void btheightiterative(){
    	if(root==nullptr){
    		return ;
    	}
    	int count=0;
    	queue<treenode*> q;
    	q.push(root);
    	q.push(nullptr);
    	while(!q.empty()){

    	if(q.front()!=nullptr)
    	{
    		treenode* temp=q.front();
    		q.pop();
    		if(temp->llink){
    			q.push(temp->llink);
    		}
    		if(temp->rlink){
    			q.push(temp->rlink);

    		}
    	}else{
    		q.pop();
    		count++;

    		if(!q.empty()){
    			q.push(nullptr);

    		}
    	}
    	}
    cout<<"Height of tree is: "<<count;

    }
    void SwapTreemember()
    {
        swaptree(this->root);
        cout << "\nSwapped Binary Tree is\n";
        printBinaryTree();
    }

    void swaptree(treenode *root) {
        if (root == nullptr)
            return;
        
        treenode *temp = root->llink;
        root->llink = root->rlink;
        root->rlink = temp;
    
        swaptree(root->llink);
        swaptree(root->rlink);
    }
    

    // Function to print the binary tree in level order
    void printBinaryTree()
    {
        queue<treenode *> q;
        q.push(root);
        q.push(nullptr);

        while (!q.empty())
        {
            if (q.front() != nullptr)
            {
                treenode *parent = q.front();
                int value = parent->val;
                q.pop();
                cout << value << " ";
                if (parent->llink)
                {
                    q.push(parent->llink);
                }
                if (parent->rlink)
                {
                    q.push(parent->rlink);
                }
            }
            else
            {
                q.pop();
                cout << endl;
                if (!q.empty())
                {
                    q.push(nullptr);
                }
            }
        }
    }
};

int main()
{
    cout << "!!! Hello World !!!" << endl; // Prints Hello World

    binaryTree b;
    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Create Binary Tree\n";
        cout << "2. Perform Inorder Traversal\n";
        cout << "3. Perform Preorder Traversal\n";
        cout << "4. Perform Postorder Traversal\n";
        cout << "5. Swap Left and Right Subtrees\n";
        cout << "6. Find Height of the Tree\n";
        cout << "7. Copy the Tree\n";
        cout << "8. Count Leaves and Internal Nodes\n";
        cout << "9. Erase Tree (Recursive)\n";
        cout << "10. Erase Tree (Non-Recursive)\n";
        cout << "11. Print Tree\n";
        cout << "12. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            b.createBinaryTree();
            b.printBinaryTree();
            break;
        case 2:
            cout << "Inorder Traversal: ";
            b.inordermember();
            cout << endl;
            break;
        case 3:
            cout << "Preorder Traversal: ";
            b.preordermember();
            cout << endl;
            break;
        case 4:
            cout << "Postorder Traversal: ";
            b.postordermember();
            cout << endl;
            break;
        case 5:
            b.SwapTreemember();
            cout << "Tree with swapped left and right children:\n";
            b.printBinaryTree();
            break;
        case 6:
            b.btheightiterative();
            break;
        case 7:
        {

            binaryTree b_copy = b;
            cout << "Copied tree in inorder: ";
            b.printBinaryTree();
            b_copy.inordermember();
            cout << endl;
            break;
        }
        case 8:
            b.leafcountmember();
            b.internalnodes();
            break;

        case 9:
            b.eraseTreemember();
            // b.root = nullptr;
            cout << "Tree erased recursively\n";
            break;

        case 10:
            b.eraseTreeNonRecursive();
            cout << "Tree erased non-recursively\n";
            break;
        case 11:
            cout << "Current tree structure:\n";
            b.printBinaryTree();
            break;
        case 12:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice, please try again.\n";
            break;
        }

    } while (choice != 12);

    return 0;
}