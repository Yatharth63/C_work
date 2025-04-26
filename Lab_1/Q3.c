#include <stdio.h>

int main() {
    int n;

    printf("Enter the number of books: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the book IDs separated by spaces: ");
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n; i++) 
    {
        if (i % 2 == 0)  
        {
            for (int j = 0; j < n - 2; j++) 
            {
                if (arr[j] > arr[j + 2]) 
                {
                    int temp = arr[j];
                    arr[j] = arr[j + 2];
                    arr[j + 2] = temp;
                }
            }
        }
    }

    for (int i = 1; i < n; i++) 
    {
        if (i % 2 != 0) 
        {
            for (int j = 1; j < n - 2; j++) 
            {
                if (arr[j] > arr[j + 2]) 
                {
                    int temp = arr[j];
                    arr[j] = arr[j + 2];
                    arr[j + 2] = temp;
                }
            }
        }
    }

    printf("Sorted catalog: ");
    for (int i = 0; i < n; i++) 
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}