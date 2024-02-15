#include <stdio.h>

// Function to sort an array using quicksort algorithm
void quicksort(int arr[], int low, int high) {
    int i, j, pivot, temp;
    
    // If the low index is less than the high index, continue sorting
    if (low < high) {
        // Set the pivot element to the low index
        pivot = low;
        i = low;
        j = high;
        
        // Continue partitioning until i and j cross each other
        while (i < j) {
            // Move i to the right until it finds an element greater than pivot
            while (arr[i] <= arr[pivot] && i < high)
                i++;
            
            // Move j to the left until it finds an element less than pivot
            while (arr[j] > arr[pivot])
                j--;
            
            // If i is less than j, swap the elements at i and j
            if (i < j) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        
        // Swap the pivot element with the element at index j
        temp = arr[pivot];
        arr[pivot] = arr[j];
        arr[j] = temp;
        
        // Recursively sort the sub-arrays to the left and right of the pivot
        quicksort(arr, low, j - 1);
        quicksort(arr, j + 1, high);
    }
}

int main() {
    int arr[] = {9, -3, 5, 2, 6, 8, -6, 1, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    quicksort(arr, 0, n - 1);
    
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}
