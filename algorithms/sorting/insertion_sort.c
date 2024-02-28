#include <stdio.h>
#include <time.h>

void insertion_sort(int arr[], int size) {
    int j = 0;
    for (int i = 1; i < size; i++) {
        int temp = arr[i];
        j = i - 1;
        // traverse backwards till it finds the right place for the
        // current element and in the meantime shifts the element traversed
        // to the right
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        // insert the element in the spot found
        arr[j + 1] = temp;
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
    insertion_sort(arr, size);
    clock_t end = clock();
    double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;

    for (int i = 0; i < size; i++) {
        printf("%d\n", arr[i]);
    }
    printf("time elapsed: %f\n", elapsed);
}
