#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Function to compare two edges based on their weight
bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Disjoint Set Union-Find structure
class DisjointSet {
public:
    vector<int> parent, rank;

    // Constructor to initialize parent and rank arrays
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // Find function with path compression
    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    }

    // Union function with rank optimization
    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

// Function to find the MST using Kruskal's algorithm
vector<Edge> kruskalMST(vector<Edge>& edges, int V) {
    sort(edges.begin(), edges.end(), compareEdges); // Sort edges by weight
    DisjointSet ds(V);

    vector<Edge> mst; // Store the resulting MST

    for (Edge& edge : edges) {
        int rootSrc = ds.find(edge.src);
        int rootDest = ds.find(edge.dest);

        // If adding this edge does not form a cycle
        if (rootSrc != rootDest) {
            mst.push_back(edge);
            ds.unionSets(rootSrc, rootDest);
        }
    }

    return mst;
}

// Main function for testing
int main() {
    int V = 4; // Number of vertices
    vector<Edge> edges = {
        {0, 1, 1}, {1, 2, 2}, {0, 2, 3}, {2, 3, 4}, {1, 3, 5}
    };

    vector<Edge> mst = kruskalMST(edges, V);

    cout << "Edges in the MST:" << endl;
    for (Edge& edge : mst) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
    }

    return 0;
}
