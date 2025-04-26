#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node *node_pointer;
}Node;

Node *createnode(int val) {
    Node *newnode = (Node*)malloc(sizeof(Node));
    newnode->value = val;
    newnode -> node_pointer = NULL;
    return newnode;
}



Node *insertAtBeginning(Node *head, int val){
    Node *newnode = createnode(val);
    newnode-> node_pointer = head;
    return newnode;
}

Node *insertAtEnd(Node *head, int val) {
    Node *newnode = createnode(val);
    if (head == NULL){
        return newnode;
    }
    else {
        Node *current = head;
        while (current -> node_pointer != NULL){
            current = current -> node_pointer;
        }
        current -> node_pointer = newnode;
    }
    return head;
}

Node *inserAfterSpecific(Node *head, int val, int specific) {
    // specific is 0 its just the start, insert at beginning
    if (specific == 0) {
        return insertAtBeginning(head, val);
    }
    else {
        int count = 0;
        Node *current = head;
        while (count < specific && current != NULL){
            count++;
            current = current -> node_pointer;
        }

        if (current == NULL) {
            printf("Position out of range, does not exist for now");
            return head;
        }
        Node *newnode = createnode(val);
        newnode -> node_pointer = current -> node_pointer;
        current -> node_pointer = newnode; 
        return head;
    }
}

Node *deleteNode(Node *head,int val ){
    if (head == NULL){
        printf("the list is empty");
        return NULL;
    }

    else if (head -> value == val){
        Node *temp = head;
        head = head -> node_pointer;
        free(temp);
        return head;
    }

    // Search for the Node
    Node *current = head;
    Node *prev = NULL; // keep track of the previous pointer
    while ( current != NULL && current -> value != val) {
        prev = current;
        current = current -> node_pointer;
    }

    // if value is still not found 
    if (current == NULL) {
        printf("Value of %d does not exist", val);
        return head;
    }
    prev -> node_pointer = current -> node_pointer;
    free(current);

    return head;
}

Node *SearchNode(Node *head, int val){
    Node *current = head;

    while (current != NULL) {
        if (current->value == val){
            return current;
        }
        current = current -> node_pointer;
    }
    return NULL;
}

void display_list(Node *head) {
    Node *current = head;

    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    printf("linked list: ");
    while (current != NULL) {
        printf("%d -> ",current->value );
        current = current -> node_pointer;
    }
    printf("NULL\n");
}

void freelist(Node *head) {
    Node *current = head;
    Node *next = NULL;
    
    while (current != NULL) {
        next = current -> node_pointer;
        free(current);
        current = next;
    }
}

Node *reverse_list(Node *head) {
    Node *prev = NULL;
    Node *current = head;
    Node *next = NULL;
    
    while (current != NULL){
        next = current -> node_pointer;
        current -> node_pointer = prev;
        prev = current ;
        current = next;
    }
    return prev;
}

int main(){
    Node *head = NULL;
    
    printf("enter the numbers to be entered into list ");
    int n;
    scanf("%d", &n);
    // Create a list of 10 numbers
    

    int *arr = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < n; i++){
        head = insertAtEnd(head, arr[i]);
    }

    printf("Original list:\n");
    display_list(head);
    
    // Test reverse function
    head = reverse_list(head);
    printf("Reversed list:\n");
    display_list(head);
    
    // Free the list to prevent memory leak
    freelist(head);

    return 0;
}