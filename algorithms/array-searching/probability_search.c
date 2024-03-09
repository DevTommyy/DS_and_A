#include <stdio.h>

// this searching algorithm is intresting cause it's useful if
// you need the array only for searching and constatating if an item is there
// it reorders the array each time swapping the one found with the the one
// previous making the most searched item the first reducing time to search in
// the long run.
// obviously this is `O(n)`
int probability_search(int arr[], int size, int item) {
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == item) {
            // swap with previous
            int tmp = arr[i];
            arr[i] = arr[i - 1];
            arr[i - 1] = tmp;
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    int position = probability_search(arr, size, 10);
    printf("%s, searching returned %d\n",
           position == -1 ? "Not Fount" : "Found", position);

    for (int i = 0; i < size; i++) {
        printf("%d\n", arr[i]);
    }
}
