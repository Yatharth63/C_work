#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashNode{
    char *key;
    int value;
    struct Node *pointerToNext;
}Node;

typedef struct Hashing {
    Node **buckets;
    int size;
    int count;
    float load;
} Hash;

int hash(char *key, int size){
    int hashVal = 0; 
    
    for (int i = 0; key[i] != '\0'; i++){
        hashVal += key[i];
    }
    return hashVal % size;
}

int main() {

    printf("%d", 3%2);
    
}
