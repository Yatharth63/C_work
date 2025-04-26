#include <iostream> // for cin, cout
#include <cstring> // for strcpy, strcmp, strlen
using namespace std;


static const int MAX_STR_LEN = 100; // Maximum length for any input string
static const int TABLE_SIZE = 101; // A prime-sized table for hashing

int SHIFT;


struct HashEntry {
    char str[MAX_STR_LEN];
    bool occupodo;
}; HashEntry hashTable[TABLE_SIZE];


// 1) SHIFT TRANSFORMATION
void shiftString(const char* src, char* dest) {
    int len = strlen(src);
    for (int i = 0; i < len; i++) {
        // Shift each character by SHIFT positions
        // If it goes beyond 'z', wrap around to 'a'
        if (src[i] >= 'a' && src[i] <= 'z') {
            dest[i] = 'a' + ((src[i] - 'a' + SHIFT) % 26);
        } else {
            dest[i] = src[i]; // Keep non-lowercase characters unchanged
        }
    }
    dest[len] = '\0'; // Null terminate the string
}


// 2) HASH FUNCTION
// We'll use a simple sum-of-ASCII approach, then mod by TABLE_SIZE.
unsigned int hashFunc(const char* maskedStr) {
    unsigned int hash = 0;
    for (int i = 0; i < strlen(maskedStr); i++) {
        hash += maskedStr[i];
    }
    return hash % TABLE_SIZE;
}


// 3) INITIALIZE TABLE
// Marks all slots as empty.
void initTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].occupodo = false;
        hashTable[i].str[0] = '\0';
    }
}


// 4) INSERT using LINEAR PROBING
// We insert the masked string 'masked' into the hash table.
// If there's a collision, we probe linearly until we find an empty slot
// or confirm the string is already in the table.
void insertIntoTable(const char* masked) {
    unsigned int index = hashFunc(masked);
    
    // Linear probing until we find an empty slot or the same string
    while (hashTable[index].occupodo) {
        if (strcmp(hashTable[index].str, masked) == 0) {
            return; // String already exists, no need to insert
        }
        index = (index + 1) % TABLE_SIZE;
    }
    
    // Found an empty slot, insert the string
    strcpy(hashTable[index].str, masked);
    hashTable[index].occupodo = true;
}


// 5) SEARCH using LINEAR PROBING
// Return true if found, false if not.
bool searchTable(const char* masked) {
    unsigned int index = hashFunc(masked);
    unsigned int startIndex = index;
    
    // Linear probing until we find the string or hit an empty slot
    while (hashTable[index].occupodo) {
        if (strcmp(hashTable[index].str, masked) == 0) {
            return true; // Found the string
        }
        index = (index + 1) % TABLE_SIZE;
        
        // If we've searched the entire table without finding it
        if (index == startIndex) {
            return false;
        }
    }
    
    return false; // String not found
}


int main() {
    initTable();

    cout << "Enter shift value: ";
    cin >> SHIFT;
    
    // First line: Enter the number of strings you want to store
    cout << "Enter the number of strings to store: ";
    int N;
    cin >> N;
    
    // Next N lines: Enter each string you want to store
    cout << "Enter " << N << " strings (one per line):\n";
    for (int i = 0; i < N; i++) {
        char original[MAX_STR_LEN];
        cin >> original;
        char masked[MAX_STR_LEN];
        shiftString(original, masked);
        insertIntoTable(masked);
    }

    // Next line: Enter the number of queries you want to check
    cout << "Enter the number of queries: ";
    int Q;
    cin >> Q;
    
    // Next Q lines: Enter each string you want to check
    cout << "Enter " << Q << " strings to check (one per line):\n";
    for (int i = 0; i < Q; i++) {
        char query[MAX_STR_LEN];
        cin >> query;
        char maskedQuery[MAX_STR_LEN];
        shiftString(query, maskedQuery);
        // Check membership
        if (searchTable(maskedQuery)) {
            cout << "YES\n";
        } 
        else {
            cout << "NO\n";
        }
    }
    return 0;
}