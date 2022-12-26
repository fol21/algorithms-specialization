#include <iostream>
#include <queue>
#include <map>

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

struct HuffmanCodePair
{
    char letter;
    string code;
};


void _getCodes(Node* root, vector<HuffmanCodePair>* codes, string buffer)
{
    if(root->left != nullptr)
    {
        _getCodes(root->left, codes, buffer + "0");
    }
    if(root->right != nullptr)
    {
        _getCodes(root->right, codes, buffer + "1");
    }
    if(!(root->left != nullptr || root->right != nullptr))
        codes->push_back({root->letter, buffer}); 
}

void getCodes(Node* root, vector<HuffmanCodePair>* codes)
{
    string _empty = "";
    _getCodes(root, codes, _empty);
}

int main() {
    // Alphabet and frequencies
    map<char, double> frequencies = map<char, double>({
        {'a', 0.25}, {'b', 0.25}, {'c', 0.20}, {'d', 0.15}, {'e', 0.10}, {'f', 0.05}
    });
    
    // Create the leaf nodes for the Huffman tree
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto pair : frequencies) {
        pq.push(new Node(pair.first, pair.second));
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
    vector<HuffmanCodePair> codes = vector<HuffmanCodePair>();
    getCodes(root, &codes);
    for(int i = 0; i < codes.size(); i++)
    {
        expected_bits += codes[i].code.length() * frequencies[codes[i].letter];
    }
    
    // Multiply the expected number of bits by the number of letters in the document
    expected_bits *= 1000;
    
    cout << "Expected number of bits: " << expected_bits << endl;
    
    return 0;
}




