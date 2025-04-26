#include <stdio.h>    // For input/output functions like printf
#include <stdlib.h>   // For memory management functions like malloc and free

typedef struct Stack {
    char *array;   
    int top;      
    int capacity;
} Stack;

Stack *createStack(int capacity) {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for stack structure.\n");
        exit(EXIT_FAILURE);
    }
    stack->capacity = capacity;
    stack->top = -1;

    stack->array = (char*)malloc(capacity * sizeof(char));
    if (stack->array == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for stack array.\n");
        free(stack);
        exit(EXIT_FAILURE);
    }
    return stack;
}

void push(Stack *stack, char item) {
    if (stack->top == stack->capacity - 1) {
        stack->capacity *= 2;
        char *newArray = (char*)realloc(stack->array, stack->capacity * sizeof(char));
        if (newArray == NULL) {
            fprintf(stderr, "Error: Memory reallocation failed during push.\n");
            exit(EXIT_FAILURE);
        }
        stack->array = newArray;
    }
    stack->array[++stack->top] = item;
}

char pop(Stack *stack) {
    if (stack->top == -1) {
        return '\0';
    }
    return stack->array[stack->top--];
}

int isEmpty(Stack *stack) {
    return (stack->top == -1);
}

//starting of actual stuff 

int Balanced(const char *expr) {
    Stack *stack = createStack(10);

    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(' || expr[i] == '{' || expr[i] == '[') {
            push(stack, expr[i]);
        } 
        else if (expr[i] == ')' || expr[i] == '}' || expr[i] == ']') {
            if (isEmpty(stack)) {
                free(stack->array);
                free(stack);
                return 0;
            }
            char topChar = pop(stack);
            if (!((topChar == '(' && expr[i] == ')') ||
                (topChar == '{' && expr[i] == '}') ||
                (topChar == '[' && expr[i] == ']'))) {
                free(stack->array);
                free(stack);
                return 0;
            }
        }
    }
    int balanced = isEmpty(stack);

    free(stack->array);
    free(stack);

    return balanced;
}



int main() {
    
    size_t size = 0;
    char *expr = NULL;

    printf("Enter your expression: ");
    getline(&expr, &size, stdin);

    expr[strcspn(expr, "\n")] = '\0';
    if (Balanced(expr)) {

        printf("Balanced\n");

    } 
    else {
        printf("Not Balanced\n");
    }

    free(expr);


    return 0;
}