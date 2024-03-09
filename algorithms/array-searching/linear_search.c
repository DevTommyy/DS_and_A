#include <stdio.h>

// obviously this is `O(n)`
int linear_search(int arr[], int size, int item) {
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == item)
            return i;
    }
    return -1;
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    int position = linear_search(arr, size, 11);
    printf("%s, searching returned %d\n",
           position == -1 ? "Not Fount" : "Found", position);
}
