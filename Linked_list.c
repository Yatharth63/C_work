#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
typedef struct Node {
    int value;
    struct Node* pointer_to_next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = data;
    newNode->pointer_to_next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the list
Node* insertAtBeginning(Node* head, int data) {
    Node* newNode = createNode(data);
    newNode->pointer_to_next = head;
    return newNode;
}

// Function to insert a node at the end of the list
Node* insertAtEnd(Node* head, int data) {
    Node* newNode = createNode(data);
    
    // If the list is empty, return the new node as head
    if (head == NULL) {
        return newNode;
    }
    
    // Traverse to the last node
    Node* current = head;
    while (current->pointer_to_next != NULL) {
        current = current->pointer_to_next;
    }
    
    // Insert the new node at the end
    current->pointer_to_next = newNode;
    return head;
}

// Function to insert a node after a given position
Node* insertAfterPos(Node* head, int data, int position) {
    // If position is 0, insert at beginning
    if (position == 0) {
        return insertAtBeginning(head, data);
    }
    
    // Traverse to the node at position
    Node* current = head;
    int i = 0;
    while (current != NULL && i < position) {
        current = current->pointer_to_next;
        i++;
    }
    
    // If position is beyond the end of the list
    if (current == NULL) {
        printf("Position out of range!\n");
        return head;
    }
    
    // Create a new node and insert it after the current node
    Node* newNode = createNode(data);
    newNode->pointer_to_next = current->pointer_to_next;
    current->pointer_to_next = newNode;
    
    return head;
}

// Function to delete a node with given value
Node* deleteNode(Node* head, int value) {
    // If list is empty
    if (head == NULL) {
        printf("List is empty, nothing to delete!\n");
        return NULL;
    }
    
    // If the head node itself holds the value to be deleted
    if (head->value == value) {
        Node* temp = head;
        head = head->pointer_to_next;
        free(temp);
        return head;
    }
    
    // Search for the node to be deleted
    Node* current = head;
    Node* prev = NULL;
    
    while (current != NULL && current->value != value) {
        prev = current;
        current = current->pointer_to_next;
    }
    
    // If value not found
    if (current == NULL) {
        printf("Value %d not found in the list!\n", value);
        return head;
    }
    
    // Unlink the node from the list
    prev->pointer_to_next = current->pointer_to_next;
    free(current);
    
    return head;
}

// Function to search for a node with given value
Node* searchNode(Node* head, int value) {
    Node* current = head;
    
    while (current != NULL) {
        if (current->value == value) {
            return current;
        }
        current = current->pointer_to_next;
    }
    
    return NULL; // Node not found
}

// Function to display the linked list
void displayList(Node* head) {
    Node* current = head;
    
    if (current == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    printf("Linked List: ");
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->pointer_to_next;
    }
    printf("NULL\n");
}

// Function to free the entire linked list
void freeList(Node* head) {
    Node* current = head;
    Node* next = NULL;
    
    while (current != NULL) {
        next = current->pointer_to_next;
        free(current);
        current = next;
    }
}

// Main function to test the linked list implementation
int main() {
    Node* head = NULL;
    
    // Insert some elements
    head = insertAtEnd(head, 10);
    head = insertAtEnd(head, 20);
    head = insertAtEnd(head, 30);
    head = insertAtBeginning(head, 5);
    head = insertAfterPos(head, 15, 1);
    
    // Display the list
    displayList(head);
    
    // Search for an element
    int searchValue = 20;
    Node* foundNode = searchNode(head, searchValue);
    if (foundNode != NULL) {
        printf("Value %d found in the list!\n", searchValue);
    } else {
        printf("Value %d not found in the list!\n", searchValue);
    }
    
    // Delete an element
    head = deleteNode(head, 15);
    printf("After deleting 15:\n");
    displayList(head);
    
    // Free the list
    freeList(head);
    
    return 0;
}