#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// initialize the heap structure
typedef struct heap {
    int size;
    int capacity;
    int *arr;
} Heap;

// heap creation function
Heap* create_heap(int capacity) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap -> size = 0;
    heap -> capacity = capacity;
    heap -> arr = (int *)malloc(capacity * sizeof( int ));
    return heap;  
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
} 

// heapify function to maintain the heap property
// for max heap, the parent is greater than the children
void heapify (Heap *heap, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap -> size 
        && heap -> arr[left] > heap -> arr[largest]) {
        largest = left;
    }

    if (right < heap -> size 
        && heap -> arr[right] > heap -> arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&heap -> arr[i], &heap -> arr[largest]);
        heapify(heap, largest);
    }
}

// increase the key of a node in the heap
// this is done by replacing the value with a new value and then heapifying the node
// to maintain the heap property
void increasekey(Heap *heap, int index, int newvalue) {
    if (index >= heap -> size 
        || heap -> arr[index] >= newvalue) {
        printf("Invalid operation\n");
        return;
        }
    heap -> arr[index] = newvalue;
    while (index != 0
           && heap -> arr[(index - 1) / 2]
                  < heap -> arr[index]) {
        swap(&heap -> arr[index],
             &heap -> arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// insert a new element into the heap
// this is done by increasing the key of the last element in the heap
void insertHeap(Heap *heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Heap is full\n");
        return;
    }
    
    // Insert at end
    int i = heap -> size;
    heap -> size++;
    heap -> arr[i] = INT_MIN;  // Set to minimum initially
    
    // Then increase key
    increasekey(heap, i, value);
}

// extract the maximum element from the heap
// this is done by replacing the root with the last element in the heap and then heapifying the root
int extractMap(Heap *heap){
    if (heap -> size <= 0 ){
        return INT_MIN;
    }
    if (heap -> size == 1) {
        heap -> size--;
        return heap -> arr[0];
    }

    // Store the maximum value, and remove it from heap
    int root = heap -> arr[0];
    heap -> arr[0] = heap -> arr[heap -> size - 1];
    heap -> size--;
    heapify(heap, 0);

    return root;
}


void printHeap(Heap* heap)
{
    for (int i = 0; i < heap->size; ++i)
        printf("%d ", heap -> arr[i]);
    printf("\n");
}

// get the maximum element from the heap
int getMax(Heap *heap) {
    if (heap -> size == 0) return INT_MIN;
    return heap->arr[0];
}

void freeHeap(Heap *heap) {
    free(heap -> arr);
    free(heap);
}

int main(){

    printf("Enter the number of towers: ");
    int n;
    scanf("%d", &n);

    printf("Enter the number of towers drone can see at a time: ");
    int k;
    scanf("%d", &k);

    int *heights = (int *)malloc(n * sizeof(int));
    if (heights == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    
    for (int i = 0; i < n; i++) {
        printf("Enter the heights of the towers %d: ", i + 1);
        scanf("%d", &heights[i]);
    }

    int resultSize = n - k + 1;
    int *result = (int *)malloc(resultSize * sizeof(int));

    // double loop to create the heap for each k elements
    // and get the maximum element from the heap
    for ( int r = 0; r < resultSize; r++) {
        Heap *heap = create_heap(k);
        for ( int j = 0; j < k; j++) {
            insertHeap(heap, heights[j + r]);
        }
        result[r] = getMax(heap);
        freeHeap(heap);
    }
    printf("The maximum heights of the towers are in every %d are : ", k);
    printf("[");
    for (int i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);

    }
    printf("]");
    // free the allocated memory
    free(result);
    free(heights);
    printf("\n");
    return 0;
}