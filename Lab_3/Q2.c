#include <stdio.h>
#include <stdlib.h>

// Function to generate an array of n numbers
int* generateArray(int n) {
    int *array = (int *)malloc(n * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        array[i] = i + 1; // Filling with sequential numbers
    }
    return array;
}

// Function to print the array
void printArray(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int* reverseArray(int* arr, int size) {
    int* reversed = (int*)malloc(size * sizeof(int));
    
    if (reversed == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        reversed[i] = arr[size - 1 - i];
    }

    return reversed;
}

int* delete_every_kth_element(int arr[], int size, int k, int* new_size) {
    if (k <= 0) {
        printf("k must be greater than 0\n");
        exit(1);
    }

    // Calculate the new size
    *new_size = size - (size / k) + 1;
    int* result = (int*)malloc(*new_size * sizeof(int));

    if (result == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Copy elements, skipping every k-th element
    for (int i = 0, j = 0; i < size; i++) {
        if ((i + 1) % k != 0) { // Check if the current index is not k-th
            result[j++] = arr[i];
        }
    }

    return result;
}

int main() {
    int n = 10;

    printf("Enter the number of elements in the array: ");
//    scanf("%d", &n);

    int *array = generateArray(n);

    while (n > 1) {
        int new_size;
        int *result = delete_every_kth_element(array, n, 4, &new_size);
        free(array); // Free the old array
        array = result; // Update the array pointer

        n = new_size; // Update n to the new size

        int *reversed = reverseArray(array, n);

        free(array); // Free the array before the next iteration
        array = reversed; // Update the array pointer to the reversed array
    }
    printf("final: ");
    printArray(array, n);
    
    free(array); // Free the last remaining array
    
    return 0;
}