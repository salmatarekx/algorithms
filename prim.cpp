#include <iostream>
#include <climits>
using namespace std;

#define NUM_VERTICES 5 // Number of vertices in the graph

// Function to find the vertex with the minimum key value from the set of vertices not yet included in MST
int findMinKey(int keyValues[], bool includedMST[]) {
    int minValue = INT_MAX, minIndex;

    for (int vertex = 0; vertex < NUM_VERTICES; vertex++)
        if (!includedMST[vertex] && keyValues[vertex] < minValue)
            minValue = keyValues[vertex], minIndex = vertex;

    return minIndex;
}

// Function to print the constructed MST stored in parentVertices[]
void displayMST(int parentVertices[], int graph[NUM_VERTICES][NUM_VERTICES]) {
    cout << "Edge \tWeight\n";
    for (int i = 1; i < NUM_VERTICES; i++)
        cout << parentVertices[i] << " - " << i << "\t" << graph[i][parentVertices[i]] << "\n";
}

// Function to construct and print MST for a graph represented using adjacency matrix representation
void generateMST(int graph[NUM_VERTICES][NUM_VERTICES]) {
    int parentVertices[NUM_VERTICES];   // Array to store constructed MST
    int keyValues[NUM_VERTICES];        // Key values used to pick minimum weight edge in cut
    bool includedMST[NUM_VERTICES];     // To represent set of vertices included in MST

    // Initialize all keyValues as INFINITE and includedMST[] as false
    for (int i = 0; i < NUM_VERTICES; i++)
        keyValues[i] = INT_MAX, includedMST[i] = false;

    // Always include the first vertex in MST.
    keyValues[0] = 0;      // Make key 0 so that this vertex is picked as first vertex
    parentVertices[0] = -1;  // First node is always root of MST

    // The MST will have NUM_VERTICES vertices
    for (int count = 0; count < NUM_VERTICES - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int selectedVertex = findMinKey(keyValues, includedMST);

        // Add the picked vertex to the MST Set
        includedMST[selectedVertex] = true;

        // Update key value and parent index of the adjacent vertices of the picked vertex
        for (int vertex = 0; vertex < NUM_VERTICES; vertex++) {
            if (graph[selectedVertex][vertex] && !includedMST[vertex] && graph[selectedVertex][vertex] < keyValues[vertex])
                parentVertices[vertex] = selectedVertex, keyValues[vertex] = graph[selectedVertex][vertex];
        }
    }

    // Print the constructed MST
    displayMST(parentVertices, graph);
}

int startProgram() {
    int graph[NUM_VERTICES][NUM_VERTICES] = {
        { 0, 2, 0, 6, 0 },
        { 2, 0, 3, 8, 5 },
        { 0, 3, 0, 0, 7 },
        { 6, 8, 0, 0, 9 },
        { 0, 5, 7, 9, 0 },
    };

    generateMST(graph);

    return 0;
}
