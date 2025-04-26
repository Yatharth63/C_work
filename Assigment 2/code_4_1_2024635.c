#include <stdio.h>
#include <stdlib.h>

#define SIZE_TABLEU 10 

typedef struct Node {
    int x, y;            // Coordinates stored in this node
    struct Node* pointer_to_next;
} Node;

Node* hashTable[SIZE_TABLEU];

int hash(int x, int y) {
    return (x  + y ) % SIZE_TABLEU;
}


void insert(int x, int y) {
    // Compute hash index using the hash function
    int index = hash(x, y);

    // Allocate memory for a new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    // Initialize the new node's values
    newNode->x = x;
    newNode->y = y;

    // Link the new node to the current head of the chain (if any)
    newNode->pointer_to_next = hashTable[index];

    // Update the hash table to point to the new head
    hashTable[index] = newNode;

    // Inform the user
    printf("Inserted (%d, %d) at index %d\n", x, y, index);
}


// Searches the hash table for a given coordinate pair (x, y).
int search(int x, int y) {
    // Compute the index where this coordinate would be stored
    int index = hash(x, y);

    Node* temp = hashTable[index];

    while (temp) {
        // Check if current node matches the (x, y) pair
        if (temp->x == x && temp->y == y) {
            printf("Found (%d, %d) at index %d\n", x, y, index);
            printf("Tressure found at (%d, %d)\n", x, y);
            return 1; // Found
        }
        temp = temp->pointer_to_next; // Move to next node
    }

    printf("Coordinate (%d, %d) not found.\n", x, y);
    return 0; // Not found
}

void display() {
    printf("\nHash Table:\n");

    for (int i = 0; i < SIZE_TABLEU; i++) {
        printf("Bucket [%d]: ", i);

        // Start from the head of the linked list at this index
        Node* temp = hashTable[i];

        // Traverse the list and print all (x, y) values
        while (temp) {
            printf("(%d,%d) -> ", temp->x, temp->y);
            temp = temp->pointer_to_next;
        }

        // Indicate the end of the list
        printf("NULL\n");
    }
}

void freeTable() {
    for (int i = 0; i < SIZE_TABLEU; i++) {
        Node* temp = hashTable[i];

        while (temp) {
            Node* toDelete = temp;
            temp = temp->pointer_to_next;
            free(toDelete); // Free memory of the current node
        }

        // Reset the head of the list to NULL
        hashTable[i] = NULL;
    }
}

// It allows the user to enter coordinate pairs and performs hash table operations.
int main() {
    int n;

    // Ask user how many coordinates they want to insert
    printf("Enter the number of coordinates: ");
    scanf("%d", &n);

    // Read each coordinate pair from the user and insert into hash table
    for (int i = 0; i < n; i++) {
        int x, y;
        printf("Enter coordinate %d (x y): ", i + 1);
        scanf("%d %d", &x, &y);
        insert(x, y);
    }

    // Display the complete hash table
    display();

    // Demonstrate search functionality
    int sx, sy;
    printf("\nEnter coordinate to search (x y): ");
    scanf("%d %d", &sx, &sy);
    search(sx, sy);

    // Clean up dynamically allocated memory
    freeTable();

    return 0;
}