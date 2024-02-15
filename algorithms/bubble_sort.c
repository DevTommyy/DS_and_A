#include <stdio.h>
#include <time.h>

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

  int arr[] = {38, 27, 43, 3, 9, 82, 10};
  int size = sizeof(arr) / sizeof(arr[0]);

  printf("before: \n");
  for (int i = 0; i < size; i++) {
    printf("%d\n", arr[i]);
  }

  printf("after: \n");

  clock_t start = clock();
  bubble_sort(arr, size);
  clock_t end = clock();
  double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;

  for (int i = 0; i < size; i++) {
    printf("%d\n", arr[i]);
  }
  printf("time elapsed: %f\n", elapsed);
}
