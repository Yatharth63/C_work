int* delete_every_kth_element(int arr[], int size, int k, int* new_size) {
    if (k <= 0) {
        printf("k must be greater than 0\n");
        exit(1);
    }

    // Calculate the new size
    *new_size = size - (size / k) + 1;
    int* result = (int*)malloc(*new_size * sizeof(int));

    if (result == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Copy elements, skipping every k-th element
    for (int i = 0, j = 0; i < size; i++) {
        if ((i + 1) % k != 0) { // Check if the current index is not k-th
            result[j++] = arr[i];
        }
    }

    return result;
}