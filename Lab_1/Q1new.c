#include <stdlib.h>
#include <stdio.h>

typedef struct vector {
    int x;
    int y;
} vector_t;

void bubbleSort(vector_t *arr, int n) {
    vector_t temp;
    int swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = 0; // Flag to detect any swap
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].x > arr[j + 1].x) {
                // Swap adjacent elements if they are in the wrong order
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        // If no two elements were swapped in the inner loop, array is sorted
        if (!swapped)
            break;
    }
}


int main() {
    printf("Enter the number of intervals: ");
    int n;
    scanf("%d", &n);

    printf("enter the intervals, start end separated by space:\n");
    vector_t *intervals = malloc(n * sizeof(vector_t));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].x, &intervals[i].y);
    }
    bubbleSort(intervals, n);
    printf("Sorted intervals:\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", intervals[i].x, intervals[i].y);
    }

    return 0;
}