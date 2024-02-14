#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = i; j < size; j++) {
      if (arr[i] > arr[j]) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  int *size = (int *)malloc(sizeof(int));
  printf("insert array size: \n");
  scanf("%d", size);

  int *arr = (int *)malloc(sizeof(int) * *size);
  for (int i = 0; i < *size; i++) {
    arr[i] = rand() % 100;
    printf("%d\n", arr[i]);
  }

  printf("after: \n");
  bubble_sort(arr, *size);

  for (int i = 0; i < *size; i++) {
    printf("%d\n", arr[i]);
  }
}
