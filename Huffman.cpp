#include <iostream>
using namespace std;

// Node class for the Huffman Tree
class Node {
public:
    char data;
    unsigned freq;
    Node* left;
    Node* right;

    Node(char data, unsigned freq) {
        this->data = data;
        this->freq = freq;
        this->left = nullptr;
        this->right = nullptr;
    }
};

// MinHeap implementation using an array
class MinHeap {
private:
    Node** heapArray;
    int capacity;
    int heapSize;

    void heapifyDown(int idx) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < heapSize && heapArray[left]->freq < heapArray[smallest]->freq)
            smallest = left;
        if (right < heapSize && heapArray[right]->freq < heapArray[smallest]->freq)
            smallest = right;
        if (smallest != idx) {
            swap(heapArray[idx], heapArray[smallest]);
            heapifyDown(smallest);
        }
    }

    void heapifyUp(int idx) {
        int parent = (idx - 1) / 2;
        if (idx && heapArray[idx]->freq < heapArray[parent]->freq) {
            swap(heapArray[idx], heapArray[parent]);
            heapifyUp(parent);
        }
    }

public:
    MinHeap(int capacity) {
        this->capacity = capacity;
        this->heapSize = 0;
        this->heapArray = new Node*[capacity];
    }

    ~MinHeap() {
        delete[] heapArray;
    }

    void push(Node* node) {
        if (heapSize == capacity) {
            cout << "Heap overflow!" << endl;
            return;
        }
        heapArray[heapSize] = node;
        heapifyUp(heapSize);
        heapSize++;
    }

    Node* pop() {
        if (heapSize == 0) return nullptr;

        Node* top = heapArray[0];
        heapArray[0] = heapArray[--heapSize];
        heapifyDown(0);

        return top;
    }

    int size() const {
        return heapSize;
    }

    bool isEmpty() const {
        return heapSize == 0;
    }
};

// Function to print the Huffman Codes
void printCodes(Node* root, string str) {
    if (!root) return;

    if (!root->left && !root->right) {
        cout << root->data << ": " << str << endl;
    }

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// Function to build the Huffman Tree
Node* buildHuffmanTree(char data[], int freq[], int size) {
    MinHeap minHeap(size);

    for (int i = 0; i < size; ++i) {
        minHeap.push(new Node(data[i], freq[i]));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.pop();
        Node* right = minHeap.pop();

        Node* top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    return minHeap.pop();
}

// Main function to generate Huffman Codes
void HuffmanCodes(char data[], int freq[], int size) {
    Node* root = buildHuffmanTree(data, freq, size);
    printCodes(root, "");
}

// Driver code
int main() {
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(arr) / sizeof(arr[0]);

    HuffmanCodes(arr, freq, size);

    return 0;
}
