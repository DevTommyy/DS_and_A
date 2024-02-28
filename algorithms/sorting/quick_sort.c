#include <stdio.h>
#include <time.h>

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

int main(int argc, char *argv[]) {

    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("before: \n");
    for (int i = 0; i < size; i++) {
        printf("%d\n", arr[i]);
    }

    printf("after: \n");

    clock_t start = clock();
    quicksort(arr, 0, size - 1);
    clock_t end = clock();
    double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;

    for (int i = 0; i < size; i++) {
        printf("%d\n", arr[i]);
    }
    printf("time elapsed: %f\n", elapsed);
}
