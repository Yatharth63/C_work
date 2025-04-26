#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *reverse_Array( int array[], int n) {

    int *new_array = (int *)malloc(n * sizeof(int));
    for ( int i = n-1; i >= 0; i--){
        new_array[n-i-1] = array[i];
    }

    return new_array;
}




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
    int *reversed_arr = reverse_Array(arr, n);
    

    printf("Reversed array: ");

    free(arr);
    for (int i = 0; i < n; i++) 
    {
        printf("%d ", reversed_arr[i]);
    }
    free(reversed_arr);

    printf("\n");
    return 0;
}