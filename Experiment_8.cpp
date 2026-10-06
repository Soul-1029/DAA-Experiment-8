//Write a program to find the Minimum Spanning Tree of a weighted graph using Prims and Kruskal's algorithm.
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Edge {
    int u, v, w;
};

int findParent(int parent[], int x) {
    if (parent[x] == x)
        return x;
    return parent[x] = findParent(parent, parent[x]);
}

void unionSet(int parent[], int rank[], int a, int b) {
    a = findParent(parent, a);
    b = findParent(parent, b);

    if (a != b) {
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

void prims(vector<vector<int>>& graph, int n) {
    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    key[0] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = -1;

        for (int i = 0; i < n; i++)
            if (!visited[i] && (u == -1 || key[i] < key[u]))
                u = i;

        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !visited[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    int total = 0;

    cout << "\nPrim's MST:\n";
    cout << "Edge\tWeight\n";

    for (int i = 1; i < n; i++) {
        cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << "\n";
        total += graph[i][parent[i]];
    }

    cout << "Total Weight: " << total << "\n";
}

void kruskals(vector<Edge>& edges, int n) {
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.w < b.w;
    });

    int parent[n], rank[n];

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int total = 0;
    int count = 0;

    cout << "\nKruskal's MST:\n";
    cout << "Edge\tWeight\n";

    for (auto edge : edges) {
        int u = findParent(parent, edge.u);
        int v = findParent(parent, edge.v);

        if (u != v) {
            cout << edge.u << " - " << edge.v << "\t" << edge.w << "\n";
            total += edge.w;
            unionSet(parent, rank, u, v);
            count++;

            if (count == n - 1)
                break;
        }
    }

    cout << "Total Weight: " << total << "\n";
}

int main() {
    int n, e;

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    vector<vector<int>> graph(n, vector<int>(n, 0));
    vector<Edge> edges;

    cout << "Enter edges (u v weight):\n";

    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        graph[u][v] = w;
        graph[v][u] = w;

        edges.push_back({u, v, w});
    }

    prims(graph, n);
    kruskals(edges, n);

    return 0;
}

//Name- Hari krishna k
//Roll no. - 25/DA/028