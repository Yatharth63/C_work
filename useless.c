/*
 * String Shift and Hash Table Implementation
 * 
 * This program implements a hash table to store and search for strings
 * after applying a character shift transformation. The implementation
 * uses linear probing to handle hash collisions.
 * 
 * Overall process:
 * 1. Read N strings, apply a character shift to each, and store in hash table
 * 2. Process Q queries to check if shifted versions of strings exist in the table
 */

#include <stdio.h>  // for printf, scanf
#include <string.h> // for strcpy, strcmp, strlen
#include <stdbool.h> // for bool type

/* Constants for the program configuration */
static const int MAX_STR_LEN = 100; // Maximum length for any input string
static const int TABLE_SIZE = 101; // A prime-sized table for hashing (prime helps with distribution)
static const int SHIFT = 1; // Character shift value for string transformation

/* Hash table entry structure */
struct HashEntry {
    char str[MAX_STR_LEN]; // Stores the shifted string
    bool occupied;         // Flag indicating if the slot contains valid data
};

/* Global hash table */
struct HashEntry hashTable[TABLE_SIZE];

/**
 * SHIFT TRANSFORMATION
 * Applies a constant character shift to each character in the source string.
 * 
 * @param src  Source string to transform
 * @param dest Destination buffer for the transformed string
 */
void shiftString(const char* src, char* dest) {
    int len = strlen(src);
    for (int i = 0; i < len; i++) {
        dest[i] = src[i] + SHIFT; // Shift each character by adding SHIFT value
    }
    dest[len] = '\0'; // Ensure null-termination of the result
}

/**
 * HASH FUNCTION
 * Computes a hash value for a string using sum of ASCII values.
 * This is a simple but reasonably effective hash for strings.
 * 
 * @param maskedStr The string to hash (after character shifting)
 * @return Hash value modulo TABLE_SIZE
 */
unsigned int hashFunc(const char* maskedStr) {
    unsigned int hash = 0;
    for (int i = 0; maskedStr[i] != '\0'; i++) {
        hash += (unsigned char)maskedStr[i]; // Sum ASCII values of characters
    }
    return hash % TABLE_SIZE; // Keep the hash within table bounds
}

/**
 * INITIALIZE TABLE
 * Prepares the hash table for use by marking all slots as empty.
 */
void initTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].occupied = false;
    }
}

/**
 * INSERT USING LINEAR PROBING
 * Inserts a string into the hash table. If the target slot is occupied,
 * it searches linearly for the next available slot or stops if the string
 * is already present in the table.
 * 
 * @param masked The (already shifted) string to insert
 */
void insertIntoTable(const char* masked) {
    unsigned int index = hashFunc(masked); // Get initial position
    
    // Keep searching until an empty slot or the string itself is found
    while (hashTable[index].occupied) {
        // If string already exists in table, we're done
        if (strcmp(hashTable[index].str, masked) == 0) {
            return;
        }
        // Linear probing: move to next slot (with wrap-around)
        index = (index + 1) % TABLE_SIZE;
    }
    
    // Found an empty slot, insert the string
    strcpy(hashTable[index].str, masked);
    hashTable[index].occupied = true;
}

/**
 * SEARCH USING LINEAR PROBING
 * Searches for a string in the hash table using the same probing
 * strategy used for insertion.
 * 
 * @param masked The (already shifted) string to search for
 * @return true if found, false otherwise
 */
bool searchTable(const char* masked) {
    unsigned int index = hashFunc(masked); // Get initial position
    unsigned int startIndex = index; // Remember where we started
    
    // Keep searching until we find an empty slot or complete a full cycle
    do {
        // If slot is occupied and string matches, we found it
        if (hashTable[index].occupied && strcmp(hashTable[index].str, masked) == 0) {
            return true;
        }
        
        // If slot is empty, the string doesn't exist in the table
        if (!hashTable[index].occupied) {
            return false;
        }
        
        // Move to next slot (linear probing)
        index = (index + 1) % TABLE_SIZE;
    } while (index != startIndex); // Stop if we've examined the entire table
    
    return false; // Not found after checking all relevant slots
}

/**
 * MAIN PROGRAM
 * Handles input/output and coordinates the string processing flow.
 */
int main() {
    // Initialize the hash table
    initTable();
    
    // Read number of strings to insert
    int N;
    scanf("%d", &N);
    
    // Process each string: read, shift, and insert into hash table
    for (int i = 0; i < N; i++) {
        char original[MAX_STR_LEN];
        char masked[MAX_STR_LEN];
        
        scanf("%s", original);
        shiftString(original, masked); // Apply the shift transformation
        insertIntoTable(masked);       // Store in hash table
    }

    // Read number of query strings
    int Q;
    scanf("%d", &Q);
    
    // Process each query: read, shift, and check for existence
    for (int i = 0; i < Q; i++) {
        char query[MAX_STR_LEN];
        scanf("%s", query);
        
        char maskedQuery[MAX_STR_LEN];
        shiftString(query, maskedQuery); // Apply the same shift transformation
        
        // Check if the transformed string exists in the table
        if (searchTable(maskedQuery)) {
            printf("YES\n"); // String exists in the shifted form
        } else {
            printf("NO\n");  // String doesn't exist in the shifted form
        }
    }
    
    return 0;
}