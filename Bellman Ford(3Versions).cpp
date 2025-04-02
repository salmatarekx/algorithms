#include <iostream>
#include <vector>
#include <limits>
#include <utility>
using namespace std;



//using 2D array space o(n*n)
void bellman_ford_2d(const vector<vector<pair<int, int>>>& graph, int source) {
    const int n = graph.size();
    const int INF = numeric_limits<int>::max();
    
    // Full 2D array: D[k][a] = shortest distance to node 'a' after exactly 'k' steps
    vector<vector<int>> D(n, vector<int>(n, INF));
    D[0][source] = 0; // Base case: 0 steps to reach source

    // Iterate for k=1 to k=n-1 steps
    for (int k = 1; k < n; ++k) {
        // Copy previous step's values as initial state
        D[k] = D[k-1];

        // Relax all edges to find shorter paths
        for (int u = 0; u < n; ++u) {
            if (D[k-1][u] != INF) {
                for (const auto& edge : graph[u]) {
                    int v = edge.first;
                    int weight = edge.second;
                    if (D[k-1][u] + weight < D[k][v]) {
                        D[k][v] = D[k-1][u] + weight;
                    }
                }
            }
        }
    }









//using 2 rows 


void bellman_ford_2rows(const vector<vector<pair<int, int>>>& graph, int source) {
    const int n = graph.size();
    const int INF = numeric_limits<int>::max();
    
    // 2D array with 2 rows (alternated using k%2)
    vector<vector<int>> D(2, vector<int>(n, INF));
    D[0][source] = 0; // Initialize source

    // Relax edges (n-1) times using k%2 to alternate rows
    for (int k = 0; k < n - 1; ++k) {
        ;       // Previous row (k mod 2)
        ; // Current row ((k+1) mod 2)

        // Reset current row to INF
        fill(D[(k + 1) % 2].begin(), D[(k + 1) % 2].end(), INF);

        // Update curr_row based on prev_row
        for (int u = 0; u < n; ++u) {
            if (D[ k % 2][u] != INF) {
                for (const auto& edge : graph[u]) {
                    int v = edge.first;
                    int weight = edge.second;
                    if (D[ k % 2][u] + weight < D[(k + 1) % 2][v]) {
                        D[(k + 1) % 2][v] = D[ k % 2][u] + weight;
                    }
                }
            }
        }
    }














//using only one row !

void bellman_ford(const vector<vector<pair<int, int>>>& graph, int source) {
    const int n = graph.size();
    const int INF = numeric_limits<int>::max();
    vector<int> D(n, INF);
    D[source] = 0;

    // Relax edges n-1 times
    for (int k = 0; i < n - 1; ++k) {
        for (int u = 0; u < n; ++u) {
            for (auto& edge : graph[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (D[u] != INF && D[u] + weight < D[v]) {
                    D[v] = D[u] + weight;
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int u = 0; u < n; ++u) {
        for (auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (D[u] != INF && D[u] + weight < D[v]) {
                cout << "Graph contains negative weight cycle" << endl;
                return;
            }
        }
    }

    // Print the distances
    for (int i = 0; i < n; ++i) {
        cout << "Node " << i << ": " << (D[i] == INF ? "INF" : to_string(D[i])) << endl;
    }
}

int main() {
    // Define the graph
    vector<vector<pair<int, int>>> graph = {
        {{1, 2}, {2, 3}},    // Node 0
        {{2, -1}, {3, 1}},   // Node 1
        {{3, 2}},            // Node 2
        {}                   // Node 3
    };
    int source_node = 0;
    bellman_ford(graph, source_node);
    return 0;
}
