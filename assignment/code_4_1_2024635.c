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

int* delete_every_second_element(int arr[], int size, int* new_size) {
    *new_size = (size) / 2; // Correctly calculate the new size
    int* result = (int*)malloc(*new_size * sizeof(int));

    if (result == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    int j = 0; // Index for the result array
    for (int i = 0; i < size; i++) {
        if (i % 2 != 0) { // Include only elements at odd indices
            result[j] = arr[i];
            j++;
        }
    }

    return result; // Return the new array
}

int main() {
    int n;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int *array = generateArray(n);

    while (n > 1) {
        int new_size;
        int *result = delete_every_second_element(array, n, &new_size);
        free(array); // Free the old array for memory reduction and to not get errors
        array = result; // Update the array pointer

        n = new_size; // Update n to the new size

        int *reversed = reverseArray(array, n);

        free(array); // Free the array before the next iteration and to g=nit get errors
        array = reversed; // Update the array pointer to the reversed array
    }
    printf("final: ");
    printArray(array, n);
    
    free(array); // Free the last remaining array cause why not 
    
    return 0;
}