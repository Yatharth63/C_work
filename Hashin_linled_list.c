/*
 * Hash Table Implementation using Linked Lists for Collision Resolution
 * This file implements a hash table with chaining (linked lists) to handle collisions
 * Features include: dynamic resizing, insertion, deletion, and searching operations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Node for linked list to handle collisions
typedef struct Node {
    char* key;         // String key for the hash table entry
    int value;         // Integer value associated with the key
    struct Node* next; // Pointer to the next node in the linked list (for collision handling)
} Node;

// Hash table structure
typedef struct {
    Node** buckets;    // Array of linked list heads (buckets)
    int size;          // Current size of bucket array
    int count;         // Number of key-value pairs stored
    float load_factor; // Threshold for resizing (ratio of count/size)
} HashTable;

// Function prototypes
unsigned int hash(char* key, int size);
HashTable* create_table(int size);
void resize_table(HashTable* table);
bool insert(HashTable* table, char* key, int value);
int search(HashTable* table, char* key);
bool delete(HashTable* table, char* key);
void free_table(HashTable* table);

/**
 * Hash function to convert a string key into an integer index
 * Uses a simple multiplicative method with prime number 31
 * 
 * @param key  The string key to hash
 * @param size The size of the hash table
 * @return     The index in the hash table where the key should be placed
 */
unsigned int hash(char* key, int size) {
    unsigned int hash_value = 0;
    
    // Iterate through each character of the key
    for (int i = 0; key[i] != '\0'; i++) {
        // Multiply by 31 (a common prime number for string hashing)
        // and add the current character's ASCII value
        hash_value = hash_value * 31 + key[i];
    }
    
    // Return the hash value modulo the table size to get an index within bounds
    return hash_value % size;
}

/**
 * Create a new hash table with the specified initial size
 * 
 * @param size The initial number of buckets in the hash table
 * @return     Pointer to the newly created hash table, or NULL if allocation fails
 */
HashTable* create_table(int size) {
    // Allocate memory for the hash table structure
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) return NULL;
    
    // Allocate and initialize the bucket array with NULL pointers
    table->buckets = (Node**)calloc(size, sizeof(Node*));
    if (!table->buckets) {
        free(table);
        return NULL;
    }
    
    // Initialize the hash table properties
    table->size = size;
    table->count = 0;
    table->load_factor = 0.75; // 75% load factor before resizing (common practice)
    
    return table;
}

/**
 * Resize the hash table when load factor is exceeded
 * This doubles the table size and rehashes all existing entries
 * 
 * @param table The hash table to resize
 */
void resize_table(HashTable* table) {
    // Double the size for the new bucket array
    int new_size = table->size * 2;
    Node** new_buckets = (Node**)calloc(new_size, sizeof(Node*));
    if (!new_buckets) return; // If allocation fails, return without resizing
    
    // Rehash all existing entries
    for (int i = 0; i < table->size; i++) {
        Node* current = table->buckets[i];
        while (current) {
            // Save the next pointer before we change it
            Node* next = current->next;
            
            // Calculate the new index using the hash function
            unsigned int new_index = hash(current->key, new_size);
            
            // Insert the node at the beginning of the new bucket's linked list
            current->next = new_buckets[new_index];
            new_buckets[new_index] = current;
            
            // Move to the next node in the original list
            current = next;
        }
    }
    
    // Free old bucket array but not the nodes (they've been moved to the new array)
    free(table->buckets);
    
    // Update table with new bucket array and size
    table->buckets = new_buckets;
    table->size = new_size;
}

/**
 * Insert a key-value pair into the hash table
 * If the key already exists, its value is updated
 * 
 * @param table The hash table to insert into
 * @param key   The key for the new entry
 * @param value The value associated with the key
 * @return      true if insertion succeeded, false otherwise
 */
bool insert(HashTable* table, char* key, int value) {
    // Check if resizing is needed before insertion
    if ((float)table->count / table->size >= table->load_factor) {
        resize_table(table);
    }
    
    // Calculate the bucket index using the hash function
    unsigned int index = hash(key, table->size);
    
    // Check if key already exists
    Node* current = table->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            // Key exists, update value and return
            current->value = value;
            return true;
        }
        current = current->next;
    }
    
    // Key doesn't exist, create new node
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return false;
    
    // Duplicate the key string (deep copy)
    new_node->key = strdup(key);
    if (!new_node->key) {
        free(new_node);
        return false;
    }
    
    // Set the value
    new_node->value = value;
    
    // Insert at the beginning of the linked list (O(1) operation)
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
    table->count++;
    
    return true;
}

/**
 * Search for a key in the hash table
 * 
 * @param table The hash table to search in
 * @param key   The key to search for
 * @return      The value associated with the key, or -1 if not found
 */
int search(HashTable* table, char* key) {
    // Calculate the bucket index using the hash function
    unsigned int index = hash(key, table->size);
    
    // Search through the linked list at the calculated index
    Node* current = table->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            // Key found, return its value
            return current->value;
        }
        current = current->next;
    }
    
    // Key not found
    return -1;
}

/**
 * Delete a key-value pair from the hash table
 * 
 * @param table The hash table to delete from
 * @param key   The key to delete
 * @return      true if deletion succeeded, false if key not found
 */
bool delete(HashTable* table, char* key) {
    // Calculate the bucket index using the hash function
    unsigned int index = hash(key, table->size);
    
    Node* current = table->buckets[index];
    Node* prev = NULL;
    
    // Search for the key in the linked list
    while (current) {
        if (strcmp(current->key, key) == 0) {
            // Found the key, remove the node from the linked list
            if (prev) {
                // If not the first node, update previous node's next pointer
                prev->next = current->next;
            } else {
                // If first node, update the bucket's head pointer
                table->buckets[index] = current->next;
            }
            
            // Free the memory used by the node
            free(current->key);
            free(current);
            table->count--;
            return true;
        }
        
        // Move to the next node
        prev = current;
        current = current->next;
    }
    
    // Key not found
    return false;
}

/**
 * Free all memory used by the hash table
 * 
 * @param table The hash table to free
 */
void free_table(HashTable* table) {
    // Iterate through all buckets
    for (int i = 0; i < table->size; i++) {
        Node* current = table->buckets[i];
        // Free all nodes in each bucket's linked list
        while (current) {
            Node* next = current->next;
            free(current->key);  // Free the duplicated key string
            free(current);       // Free the node itself
            current = next;
        }
    }
    
    // Free the bucket array and the table structure
    free(table->buckets);
    free(table);
}

/**
 * Main function demonstrating the usage of the hash table
 */
int main() {
    // Create a hash table with initial size 10
    HashTable* table = create_table(10);
    
    // Insert some key-value pairs
    insert(table, "apple", 5);
    insert(table, "banana", 10);
    insert(table, "cherry", 15);
    insert(table, "date", 20);
    insert(table, "elderberry", 25);
    
    // Print some values to demonstrate search functionality
    printf("apple: %d\n", search(table, "apple"));
    printf("banana: %d\n", search(table, "banana"));
    printf("grape: %d\n", search(table, "grape"));  // Not in table, should return -1
    
    // Delete a key and verify deletion
    delete(table, "banana");
    printf("banana after deletion: %d\n", search(table, "banana"));
    
    // Add more key-value pairs to trigger resizing
    for (int i = 0; i < 20; i++) {
        char key[20];
        sprintf(key, "key%d", i);
        insert(table, key, i * 100);
    }
    
    // Print current table statistics
    printf("Current size of table: %d\n", table->size);
    printf("Current count of elements: %d\n", table->count);
    
    // Free the hash table to prevent memory leaks
    free_table(table);
    
    return 0;
}

/*HashTable {
    buckets: ----+
    size: 10     |
    count: 5     |
    load_factor: 0.75
}                |
                 v
               +-----+    +-----+    +-----+    +-----+
 buckets[0] -> | Key1|--->| Key2|--->| NULL|    |     |
               | Val1|    | Val2|    |     |    |     |
               +-----+    +-----+    +-----+    +-----+

               +-----+
 buckets[1] -> | NULL|
               |     |
               +-----+

               +-----+    +-----+
 buckets[2] -> | Key3|--->| NULL|
               | Val3|    |     |
               +-----+    +-----+

  ...

               +-----+
 buckets[9] -> | Key4|---> NULL
               | Val4|
               +-----+
*/