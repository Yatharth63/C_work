/**
 * Implementation of a max heap data structure
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * Heap structure definition
 */
typedef struct {
    int* arr;      // Array to store heap elements
    int size;      // Current number of elements in the heap
    int capacity;  // Maximum capacity of the heap
} Heap;

/**
 * Creates a new heap with the specified capacity
 * 
 * @param capacity Maximum number of elements the heap can hold
 * @return Pointer to the newly created heap
 */
Heap* createHeap(int capacity) {
    Heap* h = (Heap*)malloc(sizeof(Heap));

    h->arr = (int*)malloc(sizeof(int) * capacity);
    
    h->size = 0;
    h->capacity = capacity;
    return h;
}

/**
 * Swaps two integers
 * 
 * @param a Pointer to the first integer
 * @param b Pointer to the second integer
 */
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Maintains the max heap property starting from index i
 * 
 * @param arr Array representing the heap
 * @param i Starting index for heapify operation
 * @param n Size of the heap
 */
void heapify(int* arr, int i, int n) {
    while (i < n) {
        int largest = i;
        int left = 2 * i + 1;   // Left child index
        int right = 2 * i + 2;  // Right child index
        
        // Check if left child is larger than current node
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        
        // Check if right child is larger than current largest
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
        
        // If largest is not the current node, swap and continue heapifying
        if (i != largest) {
            swap(&arr[largest], &arr[i]);
            i = largest;
        } else {
            break;  // Heap property satisfied
        }
    }
}

/**
 * Builds a max heap from the given array
 * 
 * @param h Pointer to the heap
 */
void buildMaxHeap(Heap* h) {
    // Start from the last non-leaf node and heapify each
    for (int i = (h->size / 2) - 1; i >= 0; i--) {
        heapify(h->arr, i, h->size);
    }
}

/**
 * Inserts a new element into the heap
 * 
 * @param h Pointer to the heap
 * @param num Element to be inserted
 */
void insertElement(Heap* h, int num) {
    if (h->size >= h->capacity) {
        printf("Heap is full\n");
        return;
    }
    
    // Add the new element at the end
    h->arr[h->size] = num;
    h->size++;
    
    // Rebuild the heap to maintain the max heap property
    buildMaxHeap(h);
}

/**
 * Deletes an element from the heap
 * 
 * @param h Pointer to the heap
 * @param num Element to be deleted
 */
void deleteElement(Heap* h, int num) {
    // Find the element to delete
    int index = -1;
    for (int i = 0; i < h->size; i++) {
        if (h->arr[i] == num) {
            index = i;
            break;
        }
    }

    
    
    if (index == -1) {
        printf("Element %d not found in the heap\n", num);
        return;
    }
    
    // Replace with the last element and reduce size
    h->arr[index] = h->arr[h->size - 1];
    h->size--;
    
    // Rebuild the heap
    buildMaxHeap(h);
}

/**
 * Frees the memory allocated for the heap
 * 
 * @param h Pointer to the heap
 */
void destroyHeap(Heap* h) {
    if (h != NULL) {
        if (h->arr != NULL) {
            free(h->arr);
        }
        free(h);
    }
}

/**
 * Prints all elements in the heap
 * 
 * @param h Pointer to the heap
 */
void printHeap(Heap* h) {
    for (int i = 0; i < h->size; i++) {
        printf("%d ", h->arr[i]);
    }
    printf("\n");
}

int main() {
    // Create a heap with capacity 100
    Heap* h = createHeap(100);
    if (h == NULL) {
        return 1;
    }
    
    // Insert elements into the heap
    insertElement(h, 50);
    insertElement(h, 40);
    insertElement(h, 69);
    insertElement(h, 60);
    insertElement(h, 20);
    insertElement(h, 45);
    insertElement(h, 55);
    insertElement(h, 70);
    
    // Print the heap elements
    printf("Heap after insertions: ");
    printHeap(h);
    
    // Delete elements from the heap
    deleteElement(h, 45);
    deleteElement(h, 20);
    
    // Print the heap after deletions
    printf("Heap after deletions: ");
    printHeap(h);
    
    // Clean up
    destroyHeap(h);
    
    return 0;
}