#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Code Flow Overview:
  -------------------
  1. The program starts in main(), where dynamic memory is allocated to read the input expression.
  2. The input is read using getline(), ensuring we can handle expressions of any length.
  3. The trailing newline character is removed from the input.
  4. The checkBalanced() function is called to verify if the expression has balanced parentheses.
     a. Inside checkBalanced(), a dynamic stack is created using createStack().
     b. The expression is traversed character by character.
     c. For each opening bracket, the bracket is pushed onto the stack.
     d. For each closing bracket, the program pops the top of the stack and checks if the pair matches.
     e. If there is any mismatch or the stack is empty when a closing bracket appears, the function returns that the expression is not balanced.
  5. After processing the entire expression, if the stack is empty, it means all opening brackets had matching closing brackets.
  6. The result ("Balanced" or "Not Balanced") is printed.
  7. All dynamically allocated memory is freed before exiting.
*/

// -------------------------------------------------------------------------
// Definition of the Stack data structure:
// A structure that contains:
// - a dynamic array (char pointer) to store characters,
// - an integer 'top' representing the index of the top element,
// - an integer 'capacity' for the allocated size of the array.
// -------------------------------------------------------------------------
typedef struct Stack {
    char *array;   // Dynamic array for storing stack elements
    int top;       // Index of the top element (-1 indicates empty)
    int capacity;  // Current capacity of the stack
} Stack;

// -------------------------------------------------------------------------
// Function: createStack
// Purpose:  Allocate and initialize a new stack with a specified capacity.
// Returns:  A pointer to the newly created Stack.
// -------------------------------------------------------------------------
Stack* createStack(int capacity) {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for stack structure.\n");
        exit(EXIT_FAILURE);
    }
    stack->capacity = capacity;  // Set initial capacity
    stack->top = -1;             // Start with an empty stack

    // Allocate memory for the stack array
    stack->array = (char*)malloc(capacity * sizeof(char));
    if (stack->array == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for stack array.\n");
        free(stack);
        exit(EXIT_FAILURE);
    }
    return stack;
}

// -------------------------------------------------------------------------
// Function: push
// Purpose:  Add a new character to the top of the stack.
//          If the stack is full, double its capacity using realloc.
// -------------------------------------------------------------------------
void push(Stack *stack, char item) {
    // Check if the stack is full
    if (stack->top == stack->capacity - 1) {
        // Double the capacity if full
        stack->capacity *= 2;
        char *newArray = (char*)realloc(stack->array, stack->capacity * sizeof(char));
        if (newArray == NULL) {
            fprintf(stderr, "Error: Memory reallocation failed during push.\n");
            exit(EXIT_FAILURE);
        }
        stack->array = newArray;
    }
    // Increase the top index and store the item
    stack->array[++stack->top] = item;
}

// -------------------------------------------------------------------------
// Function: pop
// Purpose:  Remove and return the top element from the stack.
// Returns:  The popped character, or '\0' if the stack is empty (underflow).
// -------------------------------------------------------------------------
char pop(Stack *stack) {
    if (stack->top == -1) {
        return '\0';  // Underflow condition
    }
    return stack->array[stack->top--];
}

// -------------------------------------------------------------------------
// Function: isEmpty
// Purpose:  Check whether the stack is empty.
// Returns:  1 (true) if empty, 0 (false) otherwise.
// -------------------------------------------------------------------------
int isEmpty(Stack *stack) {
    return (stack->top == -1);
}

// -------------------------------------------------------------------------
// Function: isOpening
// Purpose:  Check if a character is an opening bracket: '(', '{', or '['.
// Returns:  1 if it is an opening bracket; otherwise, 0.
// -------------------------------------------------------------------------
int isOpening(char ch) {
    return (ch == '(' || ch == '{' || ch == '[');
}

// -------------------------------------------------------------------------
// Function: isMatchingPair
// Purpose:  Check if an opening and closing bracket form a matching pair.
// Returns:  1 if the pair matches; otherwise, 0.
// -------------------------------------------------------------------------
int isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

// -------------------------------------------------------------------------
// Function: checkBalanced
// Purpose:  Verify whether the given expression has balanced parentheses.
// Process:  Traverse the expression character by character, using a stack to store
//           opening brackets. For each closing bracket, pop from the stack and check
//           for a matching opening bracket. If any mismatch is found, return not balanced.
// Returns:  1 if balanced, 0 if not.
// -------------------------------------------------------------------------
int checkBalanced(const char *expr) {
    // Step 1: Create a dynamic stack with an initial capacity.
    Stack *stack = createStack(10);

    // Step 2: Traverse each character in the expression.
    for (int i = 0; expr[i] != '\0'; i++) {
        // If the character is an opening bracket, push it onto the stack.
        if (isOpening(expr[i])) {
            push(stack, expr[i]);
        } else {
            // For a closing bracket, first check if the stack is empty.
            if (isEmpty(stack)) {
                // No matching opening bracket found; free memory and return 0.
                free(stack->array);
                free(stack);
                return 0;
            }
            // Pop the top element (expected to be the matching opening bracket)
            char topChar = pop(stack);
            // If the popped bracket does not match the current closing bracket, expression is unbalanced.
            if (!isMatchingPair(topChar, expr[i])) {
                free(stack->array);
                free(stack);
                return 0;
            }
        }
    }
    // Step 3: After processing all characters, check if any unmatched brackets remain.
    int balanced = isEmpty(stack);

    // Free the dynamically allocated stack memory.
    free(stack->array);
    free(stack);

    // Return 1 if balanced, 0 otherwise.
    return balanced;
}

// -------------------------------------------------------------------------
// Function: main
// Purpose:  The entry point of the program.
// Process Flow:
//   a. Dynamically allocate memory for the input expression.
//   b. Prompt the user and read the entire input line.
//   c. Remove any trailing newline character.
//   d. Call checkBalanced() to determine if the expression is balanced.
//   e. Print the result ("Balanced" or "Not Balanced").
//   f. Free the allocated memory before exiting.
// -------------------------------------------------------------------------
int main() {
    char *expr = NULL; // Pointer to hold the input expression
    size_t size = 0;   // Variable to store the size allocated by getline()

    // Prompt the user for the expression
    printf("Enter an expression: ");
    // Read the input dynamically; getline() allocates enough memory for any input length.
    getline(&expr, &size, stdin);

    // Remove the newline character from the input if present
    expr[strcspn(expr, "\n")] = '\0';

    // Check if the expression is balanced by using the stack-based checkBalanced function.
    if (checkBalanced(expr))
        printf("Balanced\n");
    else
        printf("Not Balanced\n");

    // Free the dynamically allocated memory for the input expression.
    free(expr);

    return 0; // End of program execution.
}
