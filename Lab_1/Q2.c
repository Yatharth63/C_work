#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;


    printf("Enter the number of participants: ");
    scanf("%d", &n);

    if (n <= 0) 
    {
        printf("Invalid number of participants.\n");
        return 0;
    }

    int nums[n]; 
    int originalIndices[n];


    printf("Enter the scores of the participants: ");
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &nums[i]);
        originalIndices[i] = i; 
    }

   
    for (int i = 1; i < n; i++) 
    {
        int key = nums[i];
        int keyIndex = originalIndices[i];
        int j = i - 1;

        
        while (j >= 0 && nums[j] > key) 
        {
            nums[j + 1] = nums[j];
            originalIndices[j + 1] = originalIndices[j];
            j--;
        }


        nums[j + 1] = key;
        originalIndices[j + 1] = keyIndex;
    }

  
    int largestShift = 0;
    for (int i = 0; i < n; i++) 
    {
        int shift = abs(originalIndices[i] - i);
        if (shift > largestShift) 
        {
            largestShift = shift;
        }
    }


    printf("Largest index shift: %d\n", largestShift);

    return 0;
}