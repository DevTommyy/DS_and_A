#include <stdio.h>
#include <time.h>

int get_max(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[]
// according to the digit
// represented by exp.
// see https://www.geeksforgeeks.org/counting-sort/
void count_sort(int arr[], int n, int exp) {

    // Output array
    int output[n];
    int i, count[10] = {0};

    // Store count of occurrences
    // in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i]
    // now contains actual position
    // of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[],
    // so that arr[] now contains sorted
    // numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radix_sort(int arr[], int n) {

    // Find the maximum number to
    // know number of digits
    int max = get_max(arr, n);

    // Do counting sort for every digit.
    // Note that instead of passing digit
    // number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; max / exp > 0; exp *= 10)
        count_sort(arr, n, exp);
}
int main(int argc, char *argv[]) {

    int arr[] = {388, 27, 431, 3, 99, 82, 100};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("before: \n");
    for (int i = 0; i < size; i++) {
        printf("%d\n", arr[i]);
    }

    printf("after: \n");

    clock_t start = clock();
    radix_sort(arr, size);
    clock_t end = clock();
    double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;

    for (int i = 0; i < size; i++) {
        printf("%d\n", arr[i]);
    }
    printf("time elapsed: %f\n", elapsed);
}
