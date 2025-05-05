#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// Graph represented as adjacency list: node name -> list of adjacent node names
typedef map<string, vector<string>> Graph;
Graph graph;
map<string, bool> visited;

// Add an edge to the graph (bidirectional by default)
void addEdge(const string &u, const string &v, bool bidir = true) {
    graph[u].push_back(v);
    if (bidir) {
        graph[v].push_back(u);
    }
}

// Display the adjacency list of the graph
void displayGraph() {
    cout << "\nAdjacency List of the College Area Map:\n";
    for (auto &node : graph) {
        cout << node.first << " -> ";
        for (auto &nbr : node.second) {
            cout << nbr << ", ";
        }
        cout << "\n";
    }
}

// Utility for recursive DFS
void dfsUtil(const string &node) {
    visited[node] = true;
    cout << node << " ";
    for (auto &nbr : graph[node]) {
        if (!visited[nbr]) {
            dfsUtil(nbr);
        }
    }
}

// Perform DFS from a given start node
void DFS(const string &start) {
    visited.clear();
    cout << "DFS starting from " << start << ": ";
    dfsUtil(start);
    cout << "\n";
}

// Perform BFS from a given start node
void BFS(const string &start) {
    visited.clear();
    queue<string> q;
    visited[start] = true;
    q.push(start);

    cout << "BFS starting from " << start << ": ";
    while (!q.empty()) {
        string curr = q.front(); q.pop();
        cout << curr << " ";
        for (auto &nbr : graph[curr]) {
            if (!visited[nbr]) {
                visited[nbr] = true;
                q.push(nbr);
            }
        }
    }
    cout << "\n";
}

int main() {
    // Predefined landmarks around the college as graph nodes
    addEdge("MainGate", "LectureHall");
    addEdge("LectureHall", "Laboratory");
    addEdge("LectureHall", "Library");
    addEdge("Library", "AdminBuilding");
    addEdge("AdminBuilding", "Canteen");
    addEdge("Canteen", "Playground");
    addEdge("Playground", "Hostel");
    addEdge("Hostel", "BusStop");
    addEdge("BusStop", "MainGate");
    addEdge("Laboratory", "Playground");
    addEdge("Library", "Canteen");

    int choice;
    string startNode;
    do {
        cout << "\nMenu:\n";
        cout << "1. Display Graph\n";
        cout << "2. DFS Traversal\n";
        cout << "3. BFS Traversal\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                displayGraph();
                break;
            case 2:
                cout << "Enter start node for DFS: ";
                cin >> ws;
                getline(cin, startNode);
                if (graph.count(startNode)) DFS(startNode);
                else cout << "Node '" << startNode << "' not found.\n";
                break;
            case 3:
                cout << "Enter start node for BFS: ";
                cin >> ws;
                getline(cin, startNode);
                if (graph.count(startNode)) BFS(startNode);
                else cout << "Node '" << startNode << "' not found.\n";
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
