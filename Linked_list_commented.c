#include <stdio.h>    // Include standard input/output library for functions like printf
#include <stdlib.h>   // Include standard library for functions like malloc and free

// Define the structure for a node in the linked list
typedef struct Node {
    int value;         // The value stored in this node
    struct Node *pointer_to_next; // Pointer to the next node in the list (NULL if this is the last node)
} Node;               // Define a shorthand "Node" instead of having to write "struct Node" every time

// Function to create a new node with the given data
Node *createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // Allocate memory for the new node on the heap
    newNode->value = value;                         // Set the data field of the new node
    newNode->pointer_to_next = NULL;                         // Initialize the next pointer to NULL (no next node yet)
    return newNode;                               // Return the newly created node so it can be used by other functions
}

// Function to insert a node at the beginning of the list
Node *insertAtBeginning(Node* head, int data) {
    Node* newNode = createNode(data);             // Create a new node with the given data
    newNode->pointer_to_next = head;                         // Make the new node point to the current head
    return newNode;                               // Return the new node as the new head of the list
}

// Function to insert a node at the end of the list
Node* insertAtEnd(Node* head, int data) {
    Node* newNode = createNode(data);             // Create a new node with the given data
    
    // If the list is empty, return the new node as head
    if (head == NULL) {                          // Check if the list is empty
        return newNode;                           // If empty, the new node becomes the head
    }
    
    // Traverse to the last node
    Node* current = head;                         // Start from the head of the list
    while (current->pointer_to_next != NULL) {              // Continue until we reach the last node
        current = current->pointer_to_next;                  // Move to the next node
    }
    
    // Insert the new node at the end
    current->pointer_to_next = newNode;                      // Make the last node point to the new node
    return head;                                  // Return the unchanged head of the list
}

// Function to insert a node after a given position
Node* insertAfterPos(Node* head, int data, int position) {
    // If position is 0, insert at beginning
    if (position == 0) {                         // Check if we want to insert at the beginning
        return insertAtBeginning(head, data);     // Use the insertAtBeginning function instead
    }
    
    // Traverse to the node at position
    Node* current = head;                         // Start from the head of the list
    int i = 0;                                    // Initialize a counter to track positions
    while (current != NULL && i < position) {    // Continue until we reach the desired position or end of list
        current = current->pointer_to_next;                  // Move to the next node
        i++;                                      // Increment the position counter
    }
    
    // If position is beyond the end of the list
    if (current == NULL) {                       // Check if we've reached the end of the list
        printf("Position out of range!\n");       // Print error message if position is invalid
        return head;                              // Return the unchanged head
    }
    
    // Create a new node and insert it after the current node
    Node* newNode = createNode(data);             // Create a new node with the given data
    newNode->pointer_to_next = current->pointer_to_next;               // Make the new node point to the node after current
    current->pointer_to_next = newNode;                     // Make the current node point to the new node
    
    return head;                                  // Return the unchanged head of the list
}

// Function to delete a node with given value
Node* deleteNode(Node* head, int value) {
    // If list is empty
    if (head == NULL) {                          // Check if the list is empty
        printf("List is empty, nothing to delete!\n"); // Print error message
        return NULL;                              // Return NULL as the head (empty list)
    }
    
    // If the head node itself holds the value to be deleted
    if (head->value == value) {                   // Check if the head node contains the value to delete
        Node* temp = head;                        // Store the head node in a temporary variable
        head = head->pointer_to_next;                       // Update the head to the second node
        free(temp);                               // Free the memory of the old head node
        return head;                              // Return the new head of the list
    }
    
    // Search for the node to be deleted
    Node* current = head;                         // Start from the head of the list
    Node* prev = NULL;                            // Keep track of the previous node
    
    while (current != NULL && current->value != value) { // Continue until we find the value or reach the end
        prev = current;                           // Update the previous node pointer
        current = current->pointer_to_next;                 // Move to the next node
    }
    
    // If value not found
    if (current == NULL) {                       // Check if we've reached the end without finding the value
        printf("Value %d not found in the list!\n", value); // Print error message
        return head;                              // Return the unchanged head
    }
    
    // Unlink the node from the list
    prev->pointer_to_next = current->pointer_to_next;                 // Make the previous node point to the node after current
    free(current);                                // Free the memory of the node to be deleted
    
    return head;                                  // Return the head of the list (may or may not have changed)
}

// Function to search for a node with given value
Node* searchNode(Node* head, int value) {
    Node* current = head;                         // Start from the head of the list
    
    while (current != NULL) {                    // Continue until we reach the end of the list
        if (current->value == value) {            // Check if the current node contains the value
            return current;                        // Return the node if found
        }
        current = current->pointer_to_next;                 // Move to the next node
    }
    
    return NULL;                                  // Return NULL if the value is not found
}

// Function to display the linked list
void displayList(Node* head) {
    Node* current = head;                         // Start from the head of the list
    
    if (current == NULL) {                       // Check if the list is empty
        printf("List is empty!\n");               // Print message if list is empty
        return;                                   // Exit the function
    }
    
    printf("Linked List: ");                      // Print header for the list display
    while (current != NULL) {                    // Continue until we reach the end of the list
        printf("%d -> ", current->value);          // Print the current node's data
        current = current->pointer_to_next;                 // Move to the next node
    }
    printf("NULL\n");                             // Print NULL to indicate the end of the list
}

// Function to reverse the linked list
Node* reverseList(Node* head) {
    Node* prev = NULL;                           // Initialize previous node as NULL
    Node* current = head;                         // Start from the head of the list
    Node* next = NULL;                            // Variable to temporarily store the next node
    
    while (current != NULL) {                    // Continue until we reach the end of the list
        next = current->pointer_to_next;                    // Store the next node before changing links
        current->pointer_to_next = prev;                    // Reverse the link (point to previous node)
        prev = current;                           // Move prev one step forward
        current = next;                           // Move current one step forward
    }
    
    return prev;                                  // prev is the new head of the reversed list
}

// Function to free the entire linked list
void freeList(Node* head) {
    Node* current = head;                         // Start from the head of the list
    Node* next = NULL;                            // Variable to store the next node
    
    while (current != NULL) {                    // Continue until we reach the end of the list
        next = current->pointer_to_next;                    // Store the next node before freeing the current one
        free(current);                            // Free the memory of the current node
        current = next;                           // Move to the next node
    }

}

// Main function to test the linked list implementation
int main() {
    Node* head = NULL;                            // Initialize the head of the list to NULL (empty list)
    
    // Insert some elements
    head = insertAtEnd(head, 10);                // Insert 10 at the end (first element)
    head = insertAtEnd(head, 20);                // Insert 20 at the end
    head = insertAtEnd(head, 30);                // Insert 30 at the end
    head = insertAtBeginning(head, 5);           // Insert 5 at the beginning
    head = insertAfterPos(head, 15, 1);          // Insert 15 after position 1 (after the first element)
    
    // Display the list
    displayList(head);                            // Display the current state of the list
    
    // Search for an element
    int searchValue = 20;                         // Value to search for
    Node* foundNode = searchNode(head, searchValue); // Search for the value in the list
    if (foundNode != NULL) {                     // Check if the value was found
        printf("Value %d found in the list!\n", searchValue); // Print success message
    } else {
        printf("Value %d not found in the list!\n", searchValue); // Print failure message
    }
    
    // Delete an element
    head = deleteNode(head, 15);                  // Delete the node with value 15
    printf("After deleting 15:\n");               // Print message about the deletion
    displayList(head);                            // Display the list after deletion
    
    // Reverse the list
    head = reverseList(head);                     // Reverse the linked list
    printf("After reversing the list:\n");         // Print message about the reversal
    displayList(head);                            // Display the list after reversal
    
    // Free the list
    freeList(head);                               // Free all the nodes in the list
    
    return 0;                                     // Exit the program with success code
}