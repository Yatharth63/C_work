#include <stdio.h>
// basic binary search
int binary_search(int arr[], int n, int target) {
    int low = 0;               
    int high = n - 1;         

    while (low <= high) {     
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;        
        }
        else if (arr[mid] > target) {
            high = mid - 1;    
        }
        else {
            low = mid + 1;     
        }
    }
    return -1;                
}

void find_first_and_last(int arr[], int n, int target, int result[2]) {
    int pos = binary_search(arr, n, target); // Find the first occurence of the target element

    if (pos == -1) { // If the target not found
        result[0] = result[1] = -1; // indicate not found
        return; 
    }

    result[0] = pos; // Set first occurence index
    while (result[0] > 0 && arr[result[0] - 1] == target) { // gp backward first occurence
        result[0]--; // 
    }

    result[1] = pos; // Set the initial last occurence index
    while (result[1] < n - 1 && arr[result[1] + 1] == target) { // Iterate forwards until finding the last occurence
        result[1]++; 
    }
}

int main() {
    int n, target;
    printf("Enter array size: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter sorted array elements:\n");
    scanf("%d", &arr[0]);

    for(int i = 1; i < n; i++) {
        scanf("%d", &arr[i]);
        if(arr[i] < arr[i-1]) {
            printf("Error: Array must be sorted. Exiting.\n");
            return 1;
        }
    }

    printf("Enter target: ");
    scanf("%d", &target);

    int result[2];
    find_first_and_last(arr, n, target, result);

    if (result[0] == -1) {
        printf("Target %d not found\n", target);
    } else {
        printf("First: %d\nLast: %d\n", result[0], result[1]);
    }
    return 0;
}