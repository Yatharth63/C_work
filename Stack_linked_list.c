/*
 * Stack implementation using a singly linked list
 * This file implements a basic stack data structure using a linked list approach
 * Operations include: create, push, pop, peek, isEmpty, size, and destroy
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for linked list
// Each node contains a value and a pointer to the next node in the list
typedef struct Node {
    int value;              // Data stored in the node
    struct Node *pointer_to_next;  // Pointer to the next node in the list
} Node;

// Stack structure
// Contains a pointer to the top node and tracks the current size
typedef struct stack {
    Node *top;              // Pointer to the topmost element of the stack
    int size;               // Number of elements currently in the stack
} Stack;

// Create a new stack
// Allocates memory for a new stack and initializes its values
Stack *createStack() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    if (stack != NULL) {
        stack->top = NULL;   // Initialize with no elements (empty stack)
        stack->size = 0;     // Start with size 0
    }
    return stack;
}

// Check if stack is empty
// Returns true if stack is empty, false otherwise
bool isEmpty(Stack *stack) {
    return stack->top == NULL;
}

// Push an element onto the stack
// Adds a new element to the top of the stack (O(1) operation)
void push(Stack *stack, int item) {
    // Create a new node
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    
    // Set data and link the node
    newNode->value = item;
    newNode->pointer_to_next = stack->top;  // New node points to current top
    
    // Update top pointer and size
    stack->top = newNode;    // New node becomes the top
    stack->size++;           // Increment size counter
}

// Pop an element from the stack
// Removes and returns the top element (O(1) operation)
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");  // Error when trying to pop from empty stack
        return -1;  // Return error value
    }
    
    // Get the top node
    Node *temp = stack->top;
    int item = temp->value;  // Save the value to return
    
    // Update top pointer
    stack->top = temp->pointer_to_next;  // Move top to the next node
    
    // Free memory and update size
    free(temp);  // Release memory of the removed node
    stack->size--;  // Decrement size counter
    
    return item;  // Return the value that was popped
}

// Get the top element without removing it
// Returns the value at the top of the stack (O(1) operation)
int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;  // Return error value when stack is empty
    }
    
    return stack->top->value;  // Return the value at the top
}

// Get the size of the stack
// Returns the current number of elements (O(1) operation)
int size(Stack *stack) {
    return stack->size;
}

// Free all memory used by the stack
// Deallocates all nodes and the stack structure itself
void destroyStack(Stack *stack) {
    if (!stack) return;  // Handle NULL stack pointer
    
    while (!isEmpty(stack)) {
        pop(stack);  // Pop and free each node one by one
    }
    
    free(stack);  // Finally free the stack structure
}

// Example usage
int main() {
    // Create a new stack
    Stack *stack = createStack();
    
    // Push some initial values
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    
    // Inspect the stack
    printf("Top element: %d\n", peek(stack));
    printf("Stack size: %d\n", size(stack));
    
    // Remove elements
    printf("Popped element: %d\n", pop(stack));  // Should pop 30
    printf("Popped element: %d\n", pop(stack));  // Should pop 20
    
    // Check stack status after operations
    printf("Stack size after popping: %d\n", size(stack));
    printf("Top element after popping: %d\n", peek(stack));  // Should be 10
    
    // Adding many elements to test stack handling of multiple values
    for (int i = 0; i < 20; i++) {
        push(stack, i * 100);
    }
    
    // Verify that all elements were added correctly
    printf("Stack size after adding 20 elements: %d\n", size(stack));
    printf("Top element after adding 20 elements: %d\n", peek(stack));  // Should be 1900
    
    // Clean up all memory
    destroyStack(stack);
    return 0;
}