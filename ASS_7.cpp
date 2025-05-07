#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

const int INF = 1e9;

struct Edge {
    int u, v, cost;
};

class Graph {
    int V;
    vector<vector<pair<int,int>>> adj;    // adjacency list: (neighbor, cost)
    vector<Edge> edgeList;                // list of added edges

public:
    Graph(int n) : V(n), adj(n) {}

    void addEdge(int u, int v, int cost) {
        if (u < 0 || u >= V || v < 0 || v >= V) {
            cout << "Invalid office IDs. Must be between 0 and " << V-1 << ".\n";
            return;
        }
        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost});
        edgeList.push_back({u, v, cost});
    }

    void displayConnections() {
        if (edgeList.empty()) {
            cout << "No connections added yet.\n";
            return;
        }
        cout << "\nAll connections:\n";
        for (auto &e : edgeList) {
            cout << "  " << e.u << " - " << e.v << " : " << e.cost << "\n";
        }
    }

    void primMST() {
        vector<int> parent(V, -1), key(V, INF);
        vector<bool> inMST(V, false);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

        key[0] = 0;
        pq.push({0, 0}); // (cost, vertex)
        // int ans=0;

        while (!pq.empty()) {
            auto top    = pq.top();
            int cost_u  = top.first;
            int u       = top.second;
            pq.pop();
        
            if (inMST[u]) continue;
            inMST[u] = true;
            // ans=cost_u;
            for (auto &edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;
                if (!inMST[v] && w < key[v]) {
                    key[v] = w;
                    parent[v] = u;
                    pq.push({ key[v], v });
                }
            }
        }

        // cout<<ans<<endl;

        // Check if all vertices were included
        for (int i = 0; i < V; ++i) {
            if (!inMST[i]) {
                cout << "Graph is disconnected; no spanning tree exists.\n";
                return;
            }
        }

        // Print MST
        cout << "\nPrim's Minimum Spanning Tree:\n";
        int totalCost = 0;
        for (int v = 1; v < V; ++v) {
            cout << "  " << parent[v] << " - " << v << " : " << key[v] << "\n";
            totalCost += key[v];
        }
        cout << "Total Cost = " << totalCost << "\n";
    }
};

int main() {
    int V;
    cout << "Enter number of offices (vertices): ";
    cin >> V;
    Graph g(V);

    while (true) {
        cout << "\n----- MENU -----\n";
        cout << "1. Add Connection (u, v, cost)\n";
        cout << "2. Display All Connections\n";
        cout << "3. Compute MST via Prim's Algorithm\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            int u, v, cost;
            cout << "Enter u v cost: ";
            cin >> u >> v >> cost;
            g.addEdge(u, v, cost);
        }
        else if (choice == 2) {
            g.displayConnections();
        }
        else if (choice == 3) {
            g.primMST();
        }
        else if (choice == 4) {
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice—please try again.\n";
        }
    }

    return 0;
}