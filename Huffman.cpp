#include <iostream>
using namespace std;

// Node class for the Huffman Tree
class TreeNode {
public:
    char character;
    unsigned frequency;
    TreeNode* leftChild;
    TreeNode* rightChild;

    TreeNode(char character, unsigned frequency) {
        this->character = character;
        this->frequency = frequency;
        this->leftChild = nullptr;
        this->rightChild = nullptr;
    }
};

// MinHeap implementation using arrays (without using `std::vector` or `std::queue`)
class MinPriorityQueue {
private:
    TreeNode** nodesArray;
    int maxSize;
    int currentSize;

    void heapifyDown(int index) {
        int smallest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;

        if (leftChild < currentSize && nodesArray[leftChild]->frequency < nodesArray[smallest]->frequency)
            smallest = leftChild;
        if (rightChild < currentSize && nodesArray[rightChild]->frequency < nodesArray[smallest]->frequency)
            smallest = rightChild;
        if (smallest != index) {
            swap(nodesArray[index], nodesArray[smallest]);
            heapifyDown(smallest);
        }
    }

    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        if (index && nodesArray[index]->frequency < nodesArray[parent]->frequency) {
            swap(nodesArray[index], nodesArray[parent]);
            heapifyUp(parent);
        }
    }

public:
    MinPriorityQueue(int maxSize) {
        this->maxSize = maxSize;
        this->currentSize = 0;
        this->nodesArray = new TreeNode*[maxSize];
    }

    ~MinPriorityQueue() {
        delete[] nodesArray;
    }

    void insert(TreeNode* node) {
        if (currentSize == maxSize) {
            cout << "Heap overflow!" << endl;
            return;
        }
        nodesArray[currentSize] = node;
        heapifyUp(currentSize);
        currentSize++;
    }

    TreeNode* extractMin() {
        if (currentSize == 0) return nullptr;

        TreeNode* minNode = nodesArray[0];
        nodesArray[0] = nodesArray[--currentSize];
        heapifyDown(0);

        return minNode;
    }

    int size() const {
        return currentSize;
    }

    bool isEmpty() const {
        return currentSize == 0;
    }
};

// Function to print the Huffman Codes
void displayHuffmanCodes(TreeNode* root, string code) {
    if (!root) return;

    // If it's a leaf node, print the character and its corresponding Huffman code
    if (!root->leftChild && !root->rightChild) {
        cout << root->character << ": " << code << endl;
    }

    displayHuffmanCodes(root->leftChild, code + "0");
    displayHuffmanCodes(root->rightChild, code + "1");
}

// Function to build the Huffman Tree
TreeNode* createHuffmanTree(char characters[], int frequencies[], int count) {
    MinPriorityQueue minHeap(count);

    // Step 1: Create a leaf node for each character and add it to the min heap
    for (int i = 0; i < count; ++i) {
        minHeap.insert(new TreeNode(characters[i], frequencies[i]));
    }

    // Step 2: Build the tree by repeatedly extracting the two nodes with the lowest frequency
    while (minHeap.size() > 1) {
        // Extract two nodes with the lowest frequency
        TreeNode* left = minHeap.extractMin();
        TreeNode* right = minHeap.extractMin();

        // Create a new internal node with the combined frequency of the two nodes
        TreeNode* internalNode = new TreeNode('$', left->frequency + right->frequency);
        internalNode->leftChild = left;
        internalNode->rightChild = right;

        // Add the internal node back to the min heap
        minHeap.insert(internalNode);
    }

    // The root node of the Huffman tree
    return minHeap.extractMin();
}

// Main function to generate Huffman Codes
void generateHuffmanCodes(char characters[], int frequencies[], int count) {
    TreeNode* root = createHuffmanTree(characters, frequencies, count);
    displayHuffmanCodes(root, "");
}

// Driver code
int main() {
    char characters[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int frequencies[] = { 5, 9, 12, 13, 16, 45 };
    int count = sizeof(characters) / sizeof(characters[0]);

    generateHuffmanCodes(characters, frequencies, count);

    return 0;
}
