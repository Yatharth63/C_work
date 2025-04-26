# Linked List Implementation in C

A simple linked list implementation in C that demonstrates basic operations on a singly linked list.

## Features

- Create a new linked list node
- Insert nodes at the beginning of the list
- Insert nodes at the end of the list
- Insert nodes after a specific position
- Delete nodes with a specific value
- Search for nodes with a specific value
- Display the entire linked list
- Free all memory used by the list

## Functions

- `createNode(int value)`: Creates a new node with the given value
- `insertAtBeginning(Node* head, int data)`: Inserts a new node at the beginning
- `insertAtEnd(Node* head, int data)`: Inserts a new node at the end
- `insertAfterPos(Node* head, int data, int position)`: Inserts a new node after a specific position
- `deleteNode(Node* head, int value)`: Deletes the first node containing the given value
- `searchNode(Node* head, int value)`: Searches for a node with the given value
- `displayList(Node* head)`: Displays all values in the linked list
- `freeList(Node* head)`: Frees all memory allocated for the list

## Usage

Compile the program with a C compiler:

```
gcc Linked_list_commented.c -o linked_list
```

Run the executable:

```
./linked_list
```

The program demonstrates creating a linked list, adding elements, searching for values, and deleting nodes.

## Memory Management

This implementation properly manages memory by:
- Allocating memory for new nodes using `malloc()`
- Freeing memory when nodes are deleted
- Providing a function to free the entire list when it's no longer needed 