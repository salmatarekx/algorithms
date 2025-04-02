#include <iostream>
#include <limits>
using namespace std;

struct Edge {
    int source, destination, weight;
};

void bellmanFord(int vertices, int edges, Edge edgeList[], int source) {
    const int INF = numeric_limits<int>::max();
    int distance[vertices];
    
    for (int i = 0; i < vertices; ++i) {
        distance[i] = INF;
    }
    distance[source] = 0;

    // Relax all edges (vertices - 1) times
    for (int i = 0; i < vertices - 1; ++i) {
        for (int j = 0; j < edges; ++j) {
            int u = edgeList[j].source;
            int v = edgeList[j].destination;
            int weight = edgeList[j].weight;
            if (distance[u] != INF && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    // Check for negative weight cycles
    for (int j = 0; j < edges; ++j) {
        int u = edgeList[j].source;
        int v = edgeList[j].destination;
        int weight = edgeList[j].weight;
        if (distance[u] != INF && distance[u] + weight < distance[v]) {
            cout << "Graph contains negative weight cycle" << endl;
            return;
        }
    }

    // Print the shortest distances
    for (int i = 0; i < vertices; ++i) {
        cout << "Node " << i << ": " << (distance[i] == INF ? "INF" : to_string(distance[i])) << endl;
    }
}

int main() {
    const int vertices = 4;
    const int edges = 5;
    Edge edgeList[edges] = {
        {0, 1, 2}, {0, 2, 3}, {1, 2, -1}, {1, 3, 1}, {2, 3, 2}
    };

    int source = 0;
    bellmanFord(vertices, edges, edgeList, source);
    return 0;
}
