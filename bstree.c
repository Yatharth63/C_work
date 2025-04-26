#include <stdio.h>
#include <stdlib.h>

/**
 * TreeNode structure represents a node in the Binary Search Tree
 * Each node contains an integer value and pointers to left and right children
 */
typedef struct TreeNode {
    int value;              /* Data stored in the node */
    struct TreeNode *left;  /* Pointer to left child (smaller values) */
    struct TreeNode *right; /* Pointer to right child (larger values) */
} TreeNode;

/**
 * Creates a new tree node with the given value
 * 
 * @param value The integer value to store in the node
 * @return Pointer to the newly created node
 */
TreeNode* createNode(int value) {
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->value = value;
    return newNode;
}

/**
 * Inserts a new value into the binary search tree
 * 
 * @param root Pointer to the root node of the tree
 * @param value Value to be inserted
 */
void insertNode(TreeNode *root, int value) {
    TreeNode *newNode = createNode(value);
    TreeNode *current = root;
    
    /* Traverse the tree to find the appropriate position for insertion */
    while (1) {
        if (current->value > value) {
            /* Insert to the left for smaller values */
            if (current->left == NULL) {
                current->left = newNode;
                break;
            } else {
                current = current->left;
            }
        } else {
            /* Insert to the right for larger or equal values */
            if (current->right == NULL) {
                current->right = newNode;
                break;
            } else {
                current = current->right;
            }
        }
    }
}

/**
 * Performs a pre-order traversal of the tree (Root-Left-Right)
 * 
 * @param root Pointer to the root of the tree/subtree
 */
void traversePreOrder(TreeNode *root) {
    if (root != NULL) {
        printf("%d ", root->value);     /* Visit root first */
        traversePreOrder(root->left);   /* Then left subtree */
        traversePreOrder(root->right);  /* Then right subtree */
    }
}

/**
 * Performs an in-order traversal of the tree (Left-Root-Right)
 * This outputs the values in sorted (ascending) order
 * 
 * @param root Pointer to the root of the tree/subtree
 */
void traverseInOrder(TreeNode *root) {
    if (root != NULL) {
        traverseInOrder(root->left);    /* Visit left subtree first */
        printf("%d ", root->value);     /* Then the root */
        traverseInOrder(root->right);   /* Then right subtree */
    }
}

/**
 * Performs a post-order traversal of the tree (Left-Right-Root)
 * 
 * @param root Pointer to the root of the tree/subtree
 */
void traversePostOrder(TreeNode *root) {
    if (root != NULL) {
        traversePostOrder(root->left);  /* Visit left subtree first */
        traversePostOrder(root->right); /* Then right subtree */
        printf("%d ", root->value);     /* Visit root last */
    }
}

/**
 * Checks if a value exists in the binary search tree
 * 
 * @param root Pointer to the root of the tree
 * @param value Value to search for
 * @return 1 if found, 0 if not found
 */
int containsValue(TreeNode *root, int value) {
    while (root != NULL) {
        if (root->value == value) {
            return 1; /* Value found */
        } else if (root->value > value) {
            root = root->left; /* Search in left subtree */
        } else {
            root = root->right; /* Search in right subtree */
        }
    }
    return 0; /* Value not found */
}

/**
 * Finds and returns the node containing the specified value
 * 
 * @param root Pointer to the root of the tree
 * @param value Value to search for
 * @return Pointer to the node containing the value, or NULL if not found
 */
TreeNode* findNode(TreeNode *root, int value) {
    while (root != NULL) {
        if (root->value == value) {
            return root; /* Node found */
        } else if (root->value > value) {
            root = root->left; /* Search in left subtree */
        } else {
            root = root->right; /* Search in right subtree */
        }
    }
    return NULL; /* Node not found */
}

/**
 * Finds the parent node of the node containing the specified value
 * 
 * @param root Pointer to the root of the tree
 * @param value Value to find the parent for
 * @return Pointer to the parent node
 */
TreeNode* findParent(TreeNode *root, int value) {
    TreeNode *current = root;
    TreeNode *parent = root;
    TreeNode *temp;
    
    while (current != NULL) {
        temp = current;
        if (current->value == value) {
            return parent; /* Found the node, return its parent */
        } else if (current->value > value) {
            current = current->left; /* Fixed: was root->left */
        } else {
            current = current->right;
        }
        parent = temp;
    }
    return NULL; /* Node not found */
}

/**
 * Finds the largest value in the tree/subtree
 * 
 * @param root Pointer to the root of the tree/subtree
 * @return The maximum value in the tree
 */
int findMaxValue(TreeNode *root) {
    if (root->right == NULL) {
        return root->value; /* Rightmost node has the largest value */
    } else {
        return findMaxValue(root->right); /* Continue traversing right */
    }
}

/**
 * Finds the smallest value in the tree/subtree
 * 
 * @param root Pointer to the root of the tree/subtree
 * @return The minimum value in the tree
 */
int findMinValue(TreeNode *root) {
    if (root->left == NULL) {
        return root->value; /* Leftmost node has the smallest value */
    } else {
        return findMinValue(root->left); /* Continue traversing left */
    }
}

/**
 * Finds the successor of a node with the given value
 * Successor is the smallest value larger than the given value
 * 
 * @param root Pointer to the root of the tree
 * @param value Value to find the successor for
 * @return The successor value
 */
int findSuccessor(TreeNode *root, int value) {
    /* Successor is the minimum value in the right subtree */
    return findMinValue(findNode(root, value)->right);
}

/**
 * Finds the predecessor of a node with the given value
 * Predecessor is the largest value smaller than the given value
 * 
 * @param root Pointer to the root of the tree
 * @param value Value to find the predecessor for
 * @return The predecessor value
 */
int findPredecessor(TreeNode *root, int value) {
    /* Predecessor is the maximum value in the left subtree */
    return findMaxValue(findNode(root, value)->left);
}

/**
 * Finds the node containing the successor of the given value
 * 
 * @param root Pointer to the root of the tree
 * @param value Value to find the successor node for
 * @return Pointer to the successor node
 */
TreeNode* findSuccessorNode(TreeNode *root, int value) {
    return findNode(root, findSuccessor(root, value));
}

/**
 * Finds the node containing the predecessor of the given value
 * 
 * @param root Pointer to the root of the tree
 * @param value Value to find the predecessor node for
 * @return Pointer to the predecessor node
 */
TreeNode* findPredecessorNode(TreeNode *root, int value) {
    return findNode(root, findPredecessor(root, value));
}

/**
 * Deletes a node with the specified value from the tree
 * Handles four cases:
 * 1. Node is a leaf (no children)
 * 2. Node has only a left child
 * 3. Node has only a right child
 * 4. Node has both left and right children
 * 
 * @param root Pointer to the root of the tree
 * @param value Value to be deleted
 */
void deleteNode(TreeNode *root, int value) {
    TreeNode *nodeToDelete = findNode(root, value);       
    TreeNode *rightChild = nodeToDelete->right;
    TreeNode *leftChild = nodeToDelete->left;
    TreeNode *parentNode = findParent(root, value);

    /* Case 1: Node is a leaf (no children) */
    if (nodeToDelete->right == NULL && nodeToDelete->left == NULL) {
        if (parentNode->left == nodeToDelete) {
            parentNode->left = NULL;
        } else {
            parentNode->right = NULL;
        }
        free(nodeToDelete);
    }
    /* Case 2: Node has only a left child */
    else if (nodeToDelete->left != NULL && nodeToDelete->right == NULL) {
        if (parentNode->left == nodeToDelete) {
            parentNode->left = leftChild;
        } else {
            parentNode->right = leftChild;
        }
        free(nodeToDelete);
    }
    /* Case 3: Node has only a right child */
    else if (nodeToDelete->left == NULL && nodeToDelete->right != NULL) {
        if (parentNode->left == nodeToDelete) {
            parentNode->left = rightChild;
        } else {
            parentNode->right = rightChild;
        }
        free(nodeToDelete);
    }
    /* Case 4: Node has both left and right children */
    else {
        /* Find the successor node (minimum value in right subtree) */
        TreeNode *successorN = findSuccessorNode(root, value); 
        int successorValue = successorN->value;
        
        /* Recursively delete the successor node */
        deleteNode(root, successorValue);
        
        /* Replace the node to delete's value with the successor's value */
        nodeToDelete->value = successorValue;
    }
}

int main() {
    /* Create the root node with value 50 */
    TreeNode *root = createNode(50);
    
    /* Insert various values to build the binary search tree */
    insertNode(root, 10);
    insertNode(root, 15);
    insertNode(root, 100);
    insertNode(root, 40);
    insertNode(root, 70);
    insertNode(root, 36);
    insertNode(root, 38);
    insertNode(root, 56);
    insertNode(root, 90);
    insertNode(root, 1100);
    insertNode(root, 85);
    insertNode(root, 64);
    insertNode(root, 5);
    insertNode(root, 4);
    
    /* Demonstrate tree traversals */
    traversePostOrder(root);
    printf("\n");
    traversePreOrder(root);
    printf("\n");
    traverseInOrder(root);
    printf("\n");
    
    /* Test value search functionality */
    printf("%d %d %d %d %d %d %d\n", 
           containsValue(root, 15), 
           containsValue(root, 10), 
           containsValue(root, 1),  
           containsValue(root, 5), 
           containsValue(root, 4),
           containsValue(root, 69), 
           containsValue(root, 18));
    
    /* Print various tree properties */
    printf("%d\n", findMaxValue(root));
    printf("%d\n", findMinValue(root));
    printf("%d\n", findSuccessor(root, 10));
    printf("%d\n", findPredecessor(root, 50));
    printf("%d\n", findPredecessorNode(root, 50)->value);
    printf("%d\n", findSuccessor(root, 56));
    printf("%d\n", findSuccessorNode(root, 50)->value);
    printf("%d\n", findParent(root, 50)->value);
    printf("%d\n", findParent(root, 85)->value);
    printf("%d\n", findParent(root, 50)->value);
    
    /* Demonstrate node deletion */
    deleteNode(root, 90);
    traverseInOrder(root);
    printf("\n");
    deleteNode(root, 38);
    traverseInOrder(root);
    
    return 0;
}