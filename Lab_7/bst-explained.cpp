#include <iostream>
using namespace std;

/**
 * Node structure for BST
 * Each node contains:
 * - data: The value stored in the node
 * - left: Pointer to left child (stores smaller values)
 * - right: Pointer to right child (stores larger values)
 * - parent: Pointer to parent node (helps with successor/predecessor operations)
 */
struct Node {
    int value;
    Node* left;
    Node* right;
    Node* parent;

    // Constructor initializes a node with a value and null pointers
    Node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
};

/**
 * Binary Search Tree class
 * Implements a BST with the following properties:
 * - For any node N, all values in its left subtree are less than N's value
 * - For any node N, all values in its right subtree are greater than N's value
 * - Each subtree is also a valid BST
 */
class BSTree {
private:
    Node* root; // Root node of the tree

    /**
     * Helper function to find minimum value node in a subtree
     * In a BST, the minimum value is found by following left children until reaching a leaf
     * Time complexity: O(h) where h is the height of the tree
     */
    Node* minValueNode(Node* node) {
        Node* current = node;
        // Keep moving to the left child until we reach a node with no left child
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current; // Returns the leftmost node
    }

    /**
     * Helper function to find maximum value node in a subtree
     * In a BST, the maximum value is found by following right children until reaching a leaf
     * Time complexity: O(h) where h is the height of the tree
     */
    Node* maxValueNode(Node* node) {
        Node* current = node;
        // Keep moving to the right child until we reach a node with no right child
        while (current && current->right != nullptr) {
            current = current->right;
        }
        return current; // Returns the rightmost node
    }

    /**
     * Helper function for recursive insert
     * Recursively traverses the tree to find the appropriate position for the new node
     * Time complexity: O(h) where h is the height of the tree
     * 
     * @param node Current node in the recursion
     * @param data Value to be inserted
     * @return Updated node after insertion
     */
    Node* inserter(Node* node, int data) {
        // Base case: if node is null, create a new node with the data
        if (node == nullptr) {
            return new Node(data);
        }

        // If data is less than current node's data, insert into left subtree
        if (data < node->value) {
            node->left = inserter(node->left, data);
            node->left->parent = node; // Update parent pointer of the new node
        } 
        // If data is greater than current node's data, insert into right subtree
        else if (data > node->value) {
            node->right = inserter(node->right, data);
            node->right->parent = node; // Update parent pointer of the new node
        }
        // If data equals node's data, we don't insert (assuming no duplicates)

        // Return the (unchanged) node pointer
        return node;
    }

    /**
     * Helper function for recursive delete
     * Cases to handle:
     * 1. Node with no children: Simply remove the node
     * 2. Node with one child: Replace node with its child
     * 3. Node with two children: Find inorder successor, copy its data, then delete the successor
     * 
     * Time complexity: O(h) where h is the height of the tree
     * 
     * @param node Current node in the recursion
     * @param key Value to be deleted
     * @return Updated node after deletion
     */
    Node* deleteHelper(Node* node, int key) {
        // Base case: if tree is empty or key not found
        if (node == nullptr) {
            return node;
        }

        // Recursively search for the node to delete
        if (key < node->value) {
            node->left = deleteHelper(node->left, key);
        } else if (key > node->value) {
            node->right = deleteHelper(node->right, key);
        } 
        // Found the node to delete
        else {
            // Case 1 & 2: Node with only one child or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node; // Free the memory of the deleted node
                return temp; // Return the right child to be connected to the parent
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node; // Free the memory of the deleted node
                return temp; // Return the left child to be connected to the parent
            }

            // Case 3: Node with two children
            // Get the inorder successor (smallest node in right subtree)
            Node* temp = minValueNode(node->right);
            
            // Copy the inorder successor's data to this node
            node->value = temp->value;
            
            // Delete the inorder successor
            // This reduces the problem to deleting a node with at most one child
            node->right = deleteHelper(node->right, temp->value);
        }
        return node;
    }

    /**
     * Helper function for recursive search
     * Time complexity: O(h) where h is the height of the tree
     * 
     * @param node Current node in the recursion
     * @param key Value to search for
     * @return true if key is found, false otherwise
     */
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

    /**
     * Helper function for recursive inorder traversal
     * Visits nodes in ascending order: left subtree -> current node -> right subtree
     * Time complexity: O(n) where n is the number of nodes
     * 
     * @param node Current node in the recursion
     */
    void inOrderHelper(Node* node) {
        // Base case: if node is null, return
        if (node != nullptr) {
            // First, visit the left subtree
            inOrderHelper(node->left);
            // Then, visit the current node
            cout << node->value << " ";
            // Finally, visit the right subtree
            inOrderHelper(node->right);
        }
    }

    /**
     * Helper function for recursive postorder traversal
     * Visits nodes in the order: left subtree -> right subtree -> current node
     * Time complexity: O(n) where n is the number of nodes
     * 
     * @param node Current node in the recursion
     */
    void postOrderHelper(Node* node) {
        // Base case: if node is null, return
        if (node != nullptr) {
            // First, visit the left subtree
            postOrderHelper(node->left);
            // Then, visit the right subtree
            postOrderHelper(node->right);
            // Finally, visit the current node
            cout << node->value << " ";
        }
    }

public:
    /**
     * Constructor creates a BST with a single root node
     * @param data Value for the root node
     */
    BSTree(int data) {
        root = new Node(data);
    }

    /**
     * Public method to insert a value into the BST
     * @param data Value to be inserted
     */
    void insert(int data) {
        root = inserter(root, data);
    }

    /**
     * Public method to delete a value from the BST
     * @param key Value to be deleted
     */
    void deleteNode(int key) {
        root = deleteHelper(root, key);
    }

    /**
     * Public method to search for a value in the BST
     * @param key Value to search for
     * @return true if key is found, false otherwise
     */
    bool search(int key) {
        return searcher(root, key);
    }

    /**
     * Public method to print the BST using inorder traversal
     * InOrder traversal of a BST gives nodes in ascending order
     */
    void printInOrder() {
        inOrderHelper(root);
        cout << endl;
    }

    /**
     * Public method to print the BST using postorder traversal
     * PostOrder is useful for safely deleting a tree (visit children before parent)
     */
    void printPostOrder() {
        postOrderHelper(root);
        cout << endl;
    }

    /**
     * Finds the successor of a given node
     * The successor is the node with the smallest value greater than the given node's value
     * Cases:
     * 1. If node has a right subtree, successor is the minimum value in that subtree
     * 2. Otherwise, successor is the nearest ancestor where given node is in left subtree
     * 
     * Time complexity: O(h) where h is the height of the tree
     * 
     * @param node Node whose successor we need to find
     * @return Pointer to the successor node, or nullptr if no successor exists
     */
    Node* successor(Node* node) {
        // Case 1: Node has a right child
        // Successor is the leftmost node in the right subtree
        if (node->right != nullptr) {
            return minValueNode(node->right);
        }

        // Case 2: No right subtree
        // Travel up using parent pointers until we find a node that is
        // a left child of its parent. The parent of such a node is the successor
        Node* parent = node->parent;
        while (parent != nullptr && node == parent->right) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    /**
     * Finds the predecessor of a given node
     * The predecessor is the node with the largest value less than the given node's value
     * Cases:
     * 1. If node has a left subtree, predecessor is the maximum value in that subtree
     * 2. Otherwise, predecessor is the nearest ancestor where given node is in right subtree
     * 
     * Time complexity: O(h) where h is the height of the tree
     * 
     * @param node Node whose predecessor we need to find
     * @return Pointer to the predecessor node, or nullptr if no predecessor exists
     */
    Node* predecessor(Node* node) {
        // Case 1: Node has a left child
        // Predecessor is the rightmost node in the left subtree
        if (node->left != nullptr) {
            return maxValueNode(node->left);
        }

        // Case 2: No left subtree
        // Travel up using parent pointers until we find a node that is
        // a right child of its parent. The parent of such a node is the predecessor
        Node* parent = node->parent;
        while (parent != nullptr && node == parent->left) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    /**
     * Getter method for the root node
     * @return Pointer to the root node
     */
    Node* getRoot() {
        return root;
    }
};

/**
 * Main function demonstrating the use of the BST
 */
int main() {
    // Create a Tree with root value 5
    BSTree tree(5);
    
    // Insert values 2 and 3
    // Tree structure will be:
    //      5
    //     /
    //    2
    //     \
    //      3
    tree.insert(2);
    tree.insert(3);
    
    // Print traversals to verify tree structure
    cout << "InOrder traversal: ";
    tree.printInOrder();  // Expected output: 2 3 5
    
    cout << "PostOrder traversal: ";
    tree.printPostOrder();  // Expected output: 3 2 5
    
    // Delete value 3
    // Tree structure will be:
    //      5
    //     /
    //    2
    tree.deleteNode(3);
    
    // Search for key 3 (should not be found)
    cout << "Search for 3: " << (tree.search(3) ? "Found" : "Not Found") << endl;
    
    // Insert more values 4, 6, 9, 7
    // Tree structure will be:
    //        5
    //       / \
    //      2   6
    //       \   \
    //        4   9
    //           /
    //          7
    tree.insert(4);
    tree.insert(6);
    tree.insert(9);
    tree.insert(7);
    
    // Print traversals to verify updated tree structure
    cout << "InOrder traversal: ";
    tree.printInOrder();  // Expected output: 2 4 5 6 7 9
    
    cout << "PostOrder traversal: ";
    tree.printPostOrder();  // Expected output: 4 2 7 9 6 5
    
    // Delete values 6 and 5
    // When deleting 6, it has one child (9) which replaces it
    // When deleting 5 (root), it has two children, so inorder successor (7) replaces it
    // Tree structure will be:
    //        7
    //       / \
    //      2   9
    //       \
    //        4
    tree.deleteNode(6);
    tree.deleteNode(5);
    
    // Search for value 9 (should be found)
    cout << "Search for 9: " << (tree.search(9) ? "Found" : "Not Found") << endl;
    
    // Print final traversals
    cout << "InOrder traversal: ";
    tree.printInOrder();  // Expected output: 2 4 7 9
    
    cout << "PostOrder traversal: ";
    tree.printPostOrder();  // Expected output: 4 2 9 7
    
    return 0;
}
