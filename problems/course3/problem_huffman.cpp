#include <iostream>
#include <queue>

using namespace std;

// Structure for a node in the Huffman tree
struct Node {
    char letter;
    double weight;
    Node* left;
    Node* right;
    
    Node(char l, double w, Node* left, Node* right) : 
        letter(l), weight(w), left(left), right(right)
    {}
    
    Node(char l, double w) :
        letter(l), weight(w), left(nullptr), right(nullptr)
    {}
};

// Comparison function to use with the priority queue
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->weight > r->weight;
    }
};

int main() {
    // Alphabet and frequencies
    char alphabet[5] = {'a', 'b', 'c', 'd', 'e'};
    double frequencies[5] = {0.28, 0.27, 0.20, 0.15, 0.10};
    
    // Create the leaf nodes for the Huffman tree
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (int i = 0; i < 5; i++) {
        pq.push(new Node(alphabet[i], frequencies[i]));
    }
    
    // Construct the Huffman tree
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        pq.push(new Node('*', left->weight + right->weight, left, right));
    }
    
    // Root node of the Huffman tree
    Node* root = pq.top();
    
    // Calculate the expected number of bits
    double expected_bits = 0;
    for (int i = 0; i < 5; i++) {
        // Find the length of the Huffman code for the current letter
        Node* curr = root;
        int code_length = 0;
        while (curr->letter != alphabet[i]) {
            
        }
        // Add the expected number of bits for the current letter to the total
        expected_bits += frequencies[i] * code_length;
    }
    
    // Multiply the expected number of bits by the number of letters in the document
    expected_bits *= 1000;
    
    cout << "Expected number of bits: " << expected_bits << endl;
    
    return 0;
}




