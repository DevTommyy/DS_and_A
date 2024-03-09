#include <stdio.h>

// for binary search to work the array needs to be sorted
// but it has a logarithmic time complexity `O(log n)`
int binary_search(int arr[], int size, int item) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (arr[mid] == item) {
            return mid;
        }

        if (arr[mid] < item) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1; // Return -1 if item is not found
}

int main() {
    int arr[] = {3, 9, 11, 15, 30, 56, 88, 101};
    int size = sizeof(arr) / sizeof(arr[0]);

    int position = binary_search(arr, size, 11);
    printf("%s, searching returned %d\n",
           position == -1 ? "Not Fount" : "Found", position);
}
