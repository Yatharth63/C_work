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
    if (size <= 0) {
        *new_size = 0;
        return NULL;
    }

    *new_size = (size ) / 2; // Correctly calculate the new size
    int* result = (int*)malloc(*new_size * sizeof(int));

    if (result == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0, j = 0; i < size; i++) {
        if (i % 2 != 0) { // Include only elements at odd indices
            result[j++] = arr[i];
        }
    }

    return result; // Return the new array
}

int* recursiveDelete(int* array, int size) {
    if (size <= 1) {
        return array; // Base case: return the array if size is 1 or less
    }

    int new_size;
    int* result = delete_every_second_element(array, size, &new_size);
    free(array); // Free the old array

    // Reverse the new array
    int* reversed = reverseArray(result, new_size);
    free(result); // Free the result array

    // Recur with the reversed array
    return recursiveDelete(reversed, new_size);
}

int main() {
    int n;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int *array = generateArray(n);
    array = recursiveDelete(array, n); // Start the recursive deletion process

    printf("final: ");
    printArray(array, 1); // Print the final remaining element

    free(array); // Free the last remaining array

    return 0;
}