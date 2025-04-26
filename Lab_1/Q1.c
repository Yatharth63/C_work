#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

#define MAX_INTERVALS 100  // Maximum number of intervals

int main() 
{
    int n;


    printf("Enter the number of intervals (max %d): ", MAX_INTERVALS);
    scanf("%d", &n);


    if (n <= 0 || n > MAX_INTERVALS) 
    {
        printf("Invalid number of intervals.\n");
        return 1;
    }

 
    int intervals[MAX_INTERVALS][2];
    int merged[MAX_INTERVALS][2];
    int index = 0;


    printf("Enter the intervals (start and end) separated by space:\n");
    for (int i = 0; i < n; i++) 
    {
        printf("Interval %d: ", i + 1);
        scanf("%d %d", &intervals[i][0], &intervals[i][1]);


        if (intervals[i][0] > intervals[i][1])
        {
            printf("Invalid interval. Start should be <= End.\n");
            return 1;
        }
    }


    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (intervals[j][0] > intervals[j + 1][0]) 
            {
                
                int tempStart = intervals[j][0];
                int tempEnd = intervals[j][1];
                intervals[j][0] = intervals[j + 1][0];
                intervals[j][1] = intervals[j + 1][1];
                intervals[j + 1][0] = tempStart;
                intervals[j + 1][1] = tempEnd;
            }
        }
    }


    merged[0][0] = intervals[0][0];
    merged[0][1] = intervals[0][1];

    for (int i = 1; i < n; i++) 
    {
        if (merged[index][1] >= intervals[i][0]) 
        {
           
            if (merged[index][1] < intervals[i][1]) 
            {
                merged[index][1] = intervals[i][1];
            }
        } else 
        {
         
            index++;
            merged[index][0] = intervals[i][0];
            merged[index][1] = intervals[i][1];
        }
    }


    printf("Merged Intervals: [");
    for (int i = 0; i <= index; i++) 
    {
        printf("[%d, %d]", merged[i][0], merged[i][1]);
        if (i < index) {
            printf(", ");
        }
    }
    printf("]\n");

    return 0;
}