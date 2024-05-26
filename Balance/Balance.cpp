#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// Node struct
struct Node {
    int data;
    int height;
    Node* left;
    Node* right;
};

// Binary tree class
class Bintree {
public:
    // Constructor
    Bintree() : root(nullptr) {}

    void insert(int data) { root = insert_node(root, data); }

    void print() { print_tree(root); }

private:
    Node* root;

    // Create new node method
    Node* create_node(int data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->height = 1;
        newNode->left = newNode->right = nullptr;
        return newNode;
    }

    // insert node into the tree
    Node* insert_node(Node* root, int data) {
        if (root == nullptr)
            return create_node(data);

        if (data < root->data)
            root->left = insert_node(root->left, data);
        else if (data > root->data)
            root->right = insert_node(root->right, data);

        root->height = 1 + max(get_height(root->left), get_height(root->right));

        return balance_node(root);
    }

    // Calculate height method
    int get_height(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // Calculate steps for balance node method
    Node* balance_node(Node* node) {
        int balance = get_balance(node);

        // Left Case
        if (balance > 1 and get_balance(node->left) >= 0) {
            cout << "Right rotate for node " << node->data << endl;
            return rot_r(node);
        }

        // Right Case
        if (balance < -1 and get_balance(node->right) <= 0) {
            cout << "Left rotate for node " << node->data << endl;
            return rot_l(node);
        }

        // Left Right Case
        if (balance > 1 and get_balance(node->left) < 0) {
            cout << "Left rotate for node " << node->data << endl;
            node->left = rot_l(node->left);
            cout << "Right rotate for node " << node->data << endl;
            return rot_r(node);
        }

        // Right Left Case
        if (balance < -1 and get_balance(node->right) > 0) {
            cout << "Right rotate for node " << node->data << endl;
            node->right = rot_r(node->right);
            cout << "Left rotate for node " << node->data << endl;
            return rot_l(node);
        }

        return node;
    }

    // Right rotate method
    Node* rot_r(Node* node) {
        Node* newRoot = node->left;
        Node* temp = newRoot->right;

        newRoot->right = node;
        node->left = temp;

        node->height = 1 + max(get_height(node->left), get_height(node->right));
        newRoot->height = 1 + max(get_height(newRoot->left), get_height(newRoot->right));

        return newRoot;
    }

    // Left rotate method
    Node* rot_l(Node* node) {
        Node* new_root = node->right;
        Node* tmp = new_root->left;

        new_root->left = node;
        node->right = tmp;

        node->height = 1 + max(get_height(node->left), get_height(node->right));
        new_root->height = 1 + max(get_height(new_root->left), get_height(new_root->right));

        return new_root;
    }

    // balance node method
    int get_balance(Node* node) {
        if (node == nullptr)
            return 0;
        return get_height(node->left) - get_height(node->right);
    }

    // print method
    void print_tree(Node* node) {
        if (node == nullptr)
            return;

        cout << node->data << " ";
        print_tree(node->left);
        print_tree(node->right);
    }
};

int main() {
    cout << "The file must contain sequentially arranged nodes of the binary tree! (like: 54 21 33 11 ...)\n\n";
    ifstream file("input.txt");
    if (!file) {
        cerr << "Error while opening file." << endl;
        return 1;
    }

    Bintree bst;
    int data;

    while (file >> data) {
        bst.insert(data);
    }
    file.close();

    cout << "\nBalanced tree ";
    bst.print();
    cout << '\n';

    return 0;
}
