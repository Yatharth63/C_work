#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct heep{
    int *arr;
    int size;
    int capacity;
}Heep;

Heep *createheep(int cap){
    Heep *h = (Heep*)malloc(sizeof(Heep));

    h -> arr = (int*)malloc(cap * sizeof (int));

    h -> size = 0;
    h -> capacity = cap;
    return h;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heepify(int *arr, int i, int n){
    while ( i < n){
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]){
            largest = left;
        }
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
        if (i != largest) {
            swap(&arr[largest], &arr[i]);
            i = largest;
        }
        else{
            break; 
        }
    }
}

void buildMaxHeep(Heep *h){
    for (int i = (h -> (size / 2)) - 1; i >= 0; i++){
        heepify(h -> arr, i, h -> size);
    }
}

void insert(Heep *h, int num){
    if (h -> size >= h -> capacity){
        printf("heep is full\n");
        return;
    }

    h -> arr[h -> size] = num;
    h -> size++;
    buildMaxHeep;

}

void deleteElement(Heep *h, int num){
    int index = -1;
    for (int i = 0; i < h -> size; i++) {
        if (h -> arr[i] == num){
            index = 1;
            break; 
        }
    }
}

int main(){
    return 0;
}