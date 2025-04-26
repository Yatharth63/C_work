#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int value;
    struct Node *next_pointer;
}Node;

typedef struct Stack{
    Node *top;
    int size;
}Stack;

Stack *createStack(){
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    if ( stack != NULL ) {
        stack -> top = NULL;
        stack -> size = 0;
    }
    return stack;
}

bool isempty(Stack *stack){
    return stack -> top == NULL;
}

void push(Stack *stack, int item){
    Node *newnode = (Node*)malloc(sizeof(Node));

    newnode -> value = item;
    newnode -> next_pointer = stack -> top;

    stack -> top = newnode;
    stack -> size += 1;
}

int peek(Stack *stack){
    if (isempty(stack)){
        printf("Stack is empty but as error ");
        return -1;
    }
    return stack -> top -> value;
}

int pop(Stack *stack){

    if (isempty(stack)){
        printf("stack is empty nothing to pop but as error ");
        return -1;
    }

    Node *temp = stack -> top;
    int item = temp -> value;

    stack -> top = temp -> next_pointer;
    free(temp);
    stack -> size--;

    return item;
}

int size(Stack *stack){
    return stack -> size;
}

void destroyStack(Stack *stack) {
    if (!stack){
        return;
    }
    while(!isempty){
        pop(stack);
    }
    free(stack);
}

void popWithoutReturn(Stack *stack){

    if (isempty(stack)){
        printf("stack is empty nothing to pop but as error ");
        return ;
    }

    Node *temp = stack -> top;

    stack -> top = temp -> next_pointer;
    free(temp);
    stack -> size--;
    return;
}

int main(){
    Stack *stack = createStack();

    push(stack, -1);
    push(stack, 20);

    printf("the top element is %d\n", peek(stack));
    printf("the top element is %d\n", pop(stack));
    popWithoutReturn(stack);
    printf("the top element is %d\n", peek(stack));
    
    return 0;
}