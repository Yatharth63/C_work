#include <iostream>
using namespace std;

struct Node {
    int value;
        Node* parent; // Pointer to parent node
    Node* left; Node* right; 

    Node(int n) : value(n), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BSTree {
    Node* root; // Root node of the tree


    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current; // Returns the leftmost node
    }

    Node* maxValueNode(Node* node) {
        Node* current = node;
        while (current && current->right != nullptr) {
            current = current->right;
        }
        return current; // Returns the rightmost node
    }

    /*
    helper function for recursive delete
    1. Node with no children: Simply remove the node
    2. Node with one child: Replace node with its child
    3. Node with two children: Find inorder successor, copy its data, then delete the successor
    */
    
    Node* deleter(Node* node, int to_delte) {
        // Base case: if the node is null, return null
        if (node == nullptr) {
            return node;
        }
        // recursively find the node to delete
        if (to_delte < node -> value) {
            node -> left = deleter(node -> left, to_delte);
        } 
        else if (to_delte > node -> value) {
            node -> right = deleter(node -> right, to_delte);
        }
        else {
            // Case 1: Node with only one child or no child
            if (node -> right == nullptr) {
                Node* temp = node -> left;
                delete node; // Free the memory of the deleted node
                return temp; // Return the left child to be connected to the parent
            }

            else if (node -> left == nullptr) {
                Node* temp = node -> right;
                delete node; // Free the memory of the deleted node
                return temp; // Return the right child to be connected to the parent
            } 
           
            // Case 2: Node with two children
            // Get the inorder successor (smallest node in right subtree)
            Node* temp = (node -> right);
            
            // Copy the inorder successor's data to this node
            node -> value = temp -> value;
            
            // Delete the inorder successor
            node -> right = deleter(node -> right, temp -> value);


        }
        return node; // Return the updated node pointer

    }

    bool searcher(Node* node, int key) {
        // Base case: reached a leaf without finding the key
        if (node == nullptr) {
            return false;
        }

        // If key matches current node's data, we found it
        if (node->value == key) {
            return true;
        }

        // If key is less than current node's data, search in left subtree
        if (key < node->value) {
            return searcher(node->left, key);
        }

        // If key is greater than current node's data, search in right subtree
        return searcher(node->right, key);
    }
    void inOrderHelper(Node* node) {
        if (node == nullptr) return;
        inOrderHelper(node->left);
        cout << node->value << " ";
        inOrderHelper(node->right);
    }

    void postOrderHelper(Node* node) {
        if (node == nullptr) return;
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        cout << node->value << " ";
    }
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
    
    Node* searcher(Node* node, int key) {
        // Base case: reached a leaf without finding the key
        if (node == nullptr) {
            return false;
        }

        // If key matches current node's data, we found it
        if (node->data == key) {
            return true;
        }

        // If key is less than current node's data, search in left subtree
        if (key < node->data) {
            return searcher(node->left, key);
        }

        // If key is greater than current node's data, search in right subtree
        return searcher(node->right, key);
    }


    BSTree(int data) {
        root = new Node(data);
    }

    void insert(int data) {
        root = inserter(root, data);
    }

    void deleteNode(int key) {
        root = deleter(root, key);
    }

    bool search(int key) {
        return searcher(root, key);
    }

    void printInOrder() {
        inOrderHelper(root);
        cout << endl;
    }

    void printPostOrder() {
        postOrderHelper(root);
        cout << endl;
    }

    Node* successor(Node* node) {
        if (node->right != nullptr) {
            return minValueNode(node->right);
        }
        Node* parent = node->parent;
        while (parent != nullptr && node == parent->right) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    Node* predecessor(Node* node) {
        if (node->left != nullptr) {
            return maxValueNode(node->left);
        }
        Node* parent = node->parent;
        while (parent != nullptr && node == parent->left) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    Node* getRoot() {
        return root;
    }
};
};


int main() {
    BSTree tree(5);
    tree.insert(2);
    tree.insert(3);
    cout << "InOrder traversal: ";
    tree.printInOrder();
    cout << "PostOrder traversal: ";
    tree.printPostOrder();
    tree.deleteNode(3);
    cout << "Search for 3: " << (tree.search(3) ? "Found" : "Not Found") << endl;
    tree.insert(4);
    tree.insert(6);
    tree.insert(9);
    tree.insert(7);
    cout << "InOrder traversal: ";
    tree.printInOrder();
    cout << "PostOrder traversal: ";
    tree.printPostOrder();
    tree.deleteNode(6);
    tree.deleteNode(5);
    cout << "Search for 9: " << (tree.search(9) ? "Found" : "Not Found") << endl;
    cout << "InOrder traversal: ";
    tree.printInOrder();
    cout << "PostOrder traversal: ";
    tree.printPostOrder();
    return 0;
}
