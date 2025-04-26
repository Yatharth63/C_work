#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vectors {
    int x;
    int y;
} vector;

int main() {
    printf("enter the number of rows: ");
    int rows;
    scanf("%d", &rows);
    
    printf("enter the number of columns: ");
    int columns;
    scanf("%d", &columns);

    int **arr = (int **)malloc(rows * sizeof(int *));

    for (int i = 0; i < rows; i++) {
        arr[i] = (int *)malloc(columns * sizeof(int));
    }
    // Fill the array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            arr[i][j] = (i + 1) * (j + 1);
        }
    }
    
    // Print the array
    printf("the array is:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    // Free allocated memory
    free(arr);

    
    return 0;
}