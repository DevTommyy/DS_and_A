#include <stdio.h>
#include <time.h>

void shell_sort(int arr[], int size) {
  int increment = size / 2;
  // if the increment is 0 it means that the gap
  // that shell sort creates between the elements
  // to sort is 0 which means the array is sorted
  while (increment != 0) {
    int current = increment;
    // same as insertion sort, swap all the elements
    // in the right place if needed then swap the one
    // currently inspected
    while (current < size) {
      int tmp = arr[current];
      int i = current - increment;
      while (i >= 0 && tmp < arr[i]) {
        arr[i + increment] = arr[i];
        i -= increment;
      }
      arr[i + increment] = tmp;
      current = current + 1;
    }
    // change the gap
    increment /= 2;
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
  shell_sort(arr, size);
  clock_t end = clock();
  double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;

  for (int i = 0; i < size; i++) {
    printf("%d\n", arr[i]);
  }
  printf("time elapsed: %f\n", elapsed);
}
