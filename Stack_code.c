#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 1000

// Stack structure
typedef struct stack {
    int items[MAX_SIZE];
    int top;
} Stack;

// Helper function to initialize a stack
void initStack(Stack *stack) {
    stack->top = -1;
}

// Helper function to check if stack is full
bool isFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

// Helper function to check if stack is empty
bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Helper function to add an element to the stack
void push(Stack *stack, int item) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->top++;
    stack->items[stack->top] = item;
}

// Helper function to remove an element from the stack
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1;
    }
    int item = stack->items[stack->top];
    stack->top--;
    return item;
}

// Helper function to get the top element without removing it
int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->items[stack->top];
}

// Helper function to get the size of the stack
int size(Stack *stack) {
    return stack->top + 1;
}

// Example usage
int main() {
    Stack stack;
    initStack(&stack);
    
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    
    printf("Top element: %d\n", peek(&stack));
    printf("Stack size: %d\n", size(&stack));
    
    printf("Popped element: %d\n", pop(&stack));
    printf("Popped element: %d\n", pop(&stack));
    
    printf("Stack size after popping: %d\n", size(&stack));
    printf("Top element after popping: %d\n", peek(&stack));
    
    return 0;
}