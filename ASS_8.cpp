#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class node{
public:
    node *left;
    node *right;
    int cost;
    int value;
    int root;
    node(int c,int v,int r){
        cost = c;
        value = v;
        root = r;
        left = NULL;
        right = NULL;
    }
};

vector<vector<int>> c;
vector<vector<int>> r;
vector<vector<int>> w;

class OBST{
public:
    
    node* root;
    OBST(){
        root = NULL;
    }

    int weight(int i, int j,vector<int> &p,vector<int> &q,vector<vector<int>> &w){
        if(w[i][j] != -1){
            return w[i][j];
        }
        if(i == j){
            w[i][j] = q[j];
            return w[i][j];
        }
        w[i][j]  = weight(i,j-1,p,q,w) + p[j] + q[j];
        return w[i][j];
    }

    int cost(int i, int j,vector<int> &p,vector<int> &q,vector<vector<int>> &c,vector<vector<int>> &r){
        if(i == j){
            c[i][j] = 0;
            return 0;
        }
        if(c[i][j] != -1){
            return c[i][j];
        }

        int m = 9999999;
        int mr = -1;
        for(int k = i+1;k<=j;k++){
            int ti = cost(i,k-1,p,q,c,r);
            int tk = cost(k,j,p,q,c,r);
            int t = ti + tk;
            if (t < m) {
                m = t;
                mr = k;
            }
        }
        r[i][j] = mr;
        c[i][j] = m + weight(i,j,p,q,w);
        return m + weight(i,j,p,q,w);
    }

    node* ins(int i,int j,vector<int> key,vector<int> &p,vector<int> &q){
        if(i>=j) return NULL;
        int ct = c[i][j];
        int rt = r[i][j];
        int v = key[rt-1];
        node* temp = new node(ct,v,rt);
        temp->left = ins(i, rt - 1, key, p, q);
        temp->right = ins(rt, j, key, p, q);
        
        return temp;
    }

    void tree(vector<int> &key,vector<int> &p,vector<int> &q){
        int n = key.size();
        
        w = vector<vector<int>>(n + 1, vector<int>(n + 1, -1));
        c = vector<vector<int>>(n + 1, vector<int>(n + 1, -1));
        r = vector<vector<int>>(n + 1, vector<int>(n + 1, -1));

        int wt = weight(0,n,p,q,w);
        int ct = cost(0,n,p,q,c,r);
        for(int i = 0;i<c.size();i++){
            for(int j = 0;j<c[i].size();j++){
                cout<<c[i][j]<<" ";
            }
            cout<<endl;
        }
        int rt = r[0][n];
        cout<<"Cost is "<<ct<<" Root is "<<rt<<endl;
        root = ins(0, n, key, p, q);
    }
    void inOrder(node* t){
        if(!t){
            return;
        }
        inOrder(t->left);
        cout<<t->value<<" ";
        inOrder(t->right);
    }
};

int main(){
    vector<int> keys = {10,20, 30, 40};
    vector<int> p = {0,3, 3, 1, 1};
    vector<int> q = {2,3,1,1,1}; 

    OBST obst;
    obst.tree(keys, p, q);

    cout << "Inorder Traversal of OBST: " << endl;
    
    obst.inOrder(obst.root);
    cout<<endl;

    return 0;
}