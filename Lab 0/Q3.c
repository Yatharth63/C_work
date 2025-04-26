#include <stdio.h>
#include <stdlib.h>

int main() 
{
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &arr[i]);
    }

    for (int r = 0; r < n; r++) 
    {
        // Check if we've already counted this element
        int alreadyChecked = 0;
        for (int k = 0; k < r; k++) 
        {
            if (arr[k] == arr[r]) 
            {
                alreadyChecked = 1;
                break;
            }
        }

        if (alreadyChecked)
            continue;

        // Count occurrences of arr[r]
        int count = 0;
        for (int u = 0; u < n; u++) 
        {
            if (arr[u] == arr[r]) 
            {
                count++;
            }
        }

        if (count > n / 2) 
        {
            printf("%d\n", arr[r]);
            free(arr);
            return 0;
        }
    }

    printf("-1\n");
    free(arr);
    return 0;
}
