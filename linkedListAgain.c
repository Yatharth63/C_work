#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node{
    int value;
    struct Node *node_pointer;
}Node;

Node *Createnode(int val){
    Node *newnode = (Node*)malloc(sizeof(Node));
    newnode -> value = val;
    newnode -> node_pointer = NULL;
    return newnode;
}

Node *AddAtEnd(Node *head, int val) {
    Node *newnode = Createnode(val);

    if (head == NULL){
        return newnode;
    }
    Node *current = head;
    while ( current -> node_pointer != NULL){
        current = current -> node_pointer;
    }
    current -> node_pointer = newnode;

    return head;
}

void printList(Node *head){
    Node *current = head;

    if (head == NULL){
        printf("List is empty");
        return;
    }

    printf("linked list: ");
    while (current != NULL){
        printf("%d -> ", current -> value);
        current = current -> node_pointer;
    }
    printf("NULL");
    return;
}

int main(){

    printf("enter the number of elements in array: ");
    int n;
    scanf("%d",&n);

    int *arr = (int*)malloc(n * sizeof(int));

    printf("enter the elememts of array as space seperated integer");
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }

    Node *head = NULL;

    for (int i = 0; i < n; i++){
        head = AddAtEnd(head, arr[i]);
    }
    printList(head);
}
