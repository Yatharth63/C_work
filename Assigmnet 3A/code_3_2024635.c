#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// defining the structure for binary tree nodes
struct nodals {
    int keynode;
    struct nodals *left; struct nodals *right;
};

// function for the creation of a new node
struct nodals *node_create(int val){
    struct nodals *newnode = (struct nodals *)malloc(sizeof(struct nodals));
    if (newnode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newnode->keynode = val;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode; 
}

struct nodals *insert(struct nodals *root, int val) {
    if (root == NULL) {
        return node_create(val); // Create a new node if the tree is empty
    }
    if (val < root->keynode) {
        root->left = insert(root->left, val); // Insert into the left subtree
    } else if (val > root->keynode) {
        root->right = insert(root->right, val); // Insert into the right subtree
    }
    return root; // Return the unchanged node pointer
}

void traversal_inorder(struct nodals *root, int *sum) {
    if (root == NULL) return;
    
    // Traverse right subtree first (reverse in-order)
    traversal_inorder(root->right, sum);
    
    // Update the current node's value (add current sum to original value)
    int original_val = root->keynode;
    root->keynode = original_val + *sum;  // Original value + sum of greater values
    *sum += original_val;                 // Add original value to running sum
    
    // Traverse left subtree
    traversal_inorder(root->left, sum);
}

void printer(struct nodals *root) {
    if (root == NULL) return;
    printer(root->left);
    printf("%d ", root->keynode);
    printer(root->right);
}

void freeTree(struct nodals* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct nodals *root = NULL;
    int number, i;
    printf("Enter the number of nodes ;|");
    scanf("%d", &number);
    
    for (i = 0; i < number; i++) {
        int val;
        printf("Enter the value of node %d: ", i + 1);
        scanf("%d", &val);
        root = insert(root, val);
    }
    
    printf("Original BST ): ");
    printer(root);
    printf("\n");
    
    // Transform the tree
    int sum = 0;
    traversal_inorder(root, &sum);
    
    printf("Prosperity Tree :) ");
    printer(root);
    printf("\n");
    
    freeTree(root);
    return 0;
}