/*
 * Valid Parenthesis Checker
 * 
 * This program checks if a string of parentheses is valid.
 * A string is valid if:
 * 1. Open brackets must be closed by the same type of brackets.
 * 2. Open brackets must be closed in the correct order.
 * 
 * Implementation uses a stack with linked list for efficient push/pop operations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Define stack node structure
typedef struct StackNode {
    char data;                // Character data stored in the node
    struct StackNode* next;   // Pointer to the next node in the stack
} StackNode;

// Define stack structure
typedef struct {
    StackNode* top;   // Pointer to the top node of the stack
    int size;         // Current number of elements in the stack
} Stack;

// Function prototypes
Stack* createStack();
void push(Stack* stack, char data);
char pop(Stack* stack);
char peek(Stack* stack);
bool isEmpty(Stack* stack);
void freeStack(Stack* stack);
bool isValidParentheses(const char* s);
bool isMatchingPair(char opening, char closing);

/**
 * Create a new empty stack
 * 
 * @return Pointer to the newly created stack
 */
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) return NULL;
    
    stack->top = NULL;
    stack->size = 0;
    
    return stack;
}

/**
 * Push a character onto the stack
 * 
 * @param stack The stack to push onto
 * @param data  The character to push
 */
void push(Stack* stack, char data) {
    // Create a new node
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) return; // Memory allocation failed
    
    // Set node data and put it on top of the stack
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

/**
 * Pop a character from the stack
 * 
 * @param stack The stack to pop from
 * @return      The popped character, or '\0' if stack is empty
 */
char pop(Stack* stack) {
    if (isEmpty(stack)) return '\0'; // Return null character if stack is empty
    
    // Save the top node and its data
    StackNode* temp = stack->top;
    char data = temp->data;
    
    // Update top pointer and free the old top node
    stack->top = temp->next;
    free(temp);
    stack->size--;
    
    return data;
}

/**
 * Peek at the top character of the stack without removing it
 * 
 * @param stack The stack to peek at
 * @return      The top character, or '\0' if stack is empty
 */
char peek(Stack* stack) {
    if (isEmpty(stack)) return '\0';
    return stack->top->data;
}

/**
 * Check if the stack is empty
 * 
 * @param stack The stack to check
 * @return      true if stack is empty, false otherwise
 */
bool isEmpty(Stack* stack) {
    return stack->top == NULL;
}

/**
 * Free all memory used by the stack
 * 
 * @param stack The stack to free
 */
void freeStack(Stack* stack) {
    // Pop all nodes to free them
    while (!isEmpty(stack)) {
        pop(stack);
    }
    
    // Free the stack structure itself
    free(stack);
}

/**
 * Check if two parentheses characters form a matching pair
 * 
 * @param opening The opening parenthesis character
 * @param closing The closing parenthesis character
 * @return        true if they form a matching pair, false otherwise
 */
bool isMatchingPair(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '{' && closing == '}') ||
           (opening == '[' && closing == ']');
}

/**
 * Check if a string of parentheses is valid
 * 
 * @param s The string to check
 * @return  true if the string is valid, false otherwise
 */
bool isValidParentheses(const char* s) {
    // Create a stack
    Stack* stack = createStack();
    if (!stack) return false; // Memory allocation failed
    
    // Process each character in the string
    for (int i = 0; s[i] != '\0'; i++) {
        // If it's an opening bracket, push to stack
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            push(stack, s[i]);
        } 
        // If it's a closing bracket
        else if (s[i] == ')' || s[i] == '}' || s[i] == ']') {
            // Stack shouldn't be empty (there should be a matching opening bracket)
            if (isEmpty(stack)) {
                freeStack(stack);
                return false;
            }
            
            // Pop the top element and check if it matches
            char top = pop(stack);
            if (!isMatchingPair(top, s[i])) {
                freeStack(stack);
                return false;
            }
        }
    }
    
    // Stack should be empty at the end (all brackets should be matched)
    bool result = isEmpty(stack);
    freeStack(stack);
    
    return result;
}

/**
 * Main function with example test cases
 */
int main() {
    // Test cases
    const char* testCases[] = {
        "()",               // Valid
        "()[]{}",           // Valid
        "(]",               // Invalid
        "([)]",             // Invalid
        "{[]}",             // Valid
        "(",                // Invalid
        "]",                // Invalid
        "((()))",           // Valid
        "{[()]}",           // Valid
        "{[(])}",           // Invalid
        NULL
    };  
    
    // Test each case
    for (int i = 0; testCases[i] != NULL; i++) {
        printf("String: \"%s\" is %s\n", 
               testCases[i], 
               isValidParentheses(testCases[i]) ? "Valid" : "Invalid");
    }
    
    // Interactive testing
    char input[1000];
    printf("\nEnter a string of parentheses to check (or 'exit' to quit): ");
    while (scanf("%s", input) == 1 && strcmp(input, "exit") != 0) {
        printf("String: \"%s\" is %s\n", 
               input, 
               isValidParentheses(input) ? "Valid" : "Invalid");
        printf("\nEnter a string of parentheses to check (or 'exit' to quit): ");
    }
    
    return 0;
} 