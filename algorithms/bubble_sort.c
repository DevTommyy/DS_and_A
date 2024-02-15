#include <stdio.h>

void bubble_sort(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (arr[i] > arr[j]) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
      }
    }
  }
}

int main(int argc, char *argv[]) {

  int arr[] = {9, -3, 5, 2, 6, 8, -6, 1, 3};
  int n = sizeof(arr) / sizeof(arr[0]);
  bubble_sort(arr, n);

  for (int i = 0; i < n; i++) {
    printf("%d\n", arr[i]);
  }
}
