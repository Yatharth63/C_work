#include <iostream>
using namespace std;

struct Node {
    int value;
        Node* parent; // Pointer to parent node
    Node* left; Node* right; 

    // Constructor initializes a node with a value and null pointers
    Node(int n) : value(n), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BSTree {
    Node* root; // Root node of the tree


    Node* minValueNode(Node* node) {
        Node* current = node;
        // Keep moving to the left child until we reach a node with no left child
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current; // Returns the leftmost node
    }

    Node* maxValueNode(Node* node) {
        Node* current = node;
        // Keep moving to the right child until we reach a node with no right child
        while (current && current->right != nullptr) {
            current = current->right;
        }
        return current; // Returns the rightmost node
    }


    // Helper function to insert a value into the BST
    Node* inserter(Node* node, int data) {
        // If the tree is empty, create a new node and return it
        if (node == nullptr) {
            return new Node(data);
        }

        // Otherwise, recur down the tree
        if (data < node->value) {
            node->left = inserter(node->left, data);
            node->left->parent = node; // Set parent pointer
        } else if (data > node->value) {
            node->right = inserter(node->right, data);
            node->right->parent = node; // Set parent pointer
        }

        // Return the unchanged node pointer
        return node;
    }
        /*
        Helper function for recursive delete
        Cases to handle:
        1. Node with no children: Simply remove the node
        2. Node with one child: Replace node with its child
        3. Node with two children: Find inorder successor, copy its data, then delete the successor
        */
       Node* deleter(Node* node, int to_delete) {
            // Base case: if tree is empty or key not found
            if (node == nullptr) {
                return node;
            }
            // search for the node to delete
            if (to_delete < node->value) {
                node->left = deleter(node->left, to_delete)
            }
            else if (to_delete > node->value) {
                node->right = deleter(node->right, to_delete);
            }
            else {

            }
       }
}