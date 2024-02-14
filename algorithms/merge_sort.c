#include <stdio.h>

void merge(int arr[], int left, int mid, int right) {
  int left_arr_size = mid - left + 1;
  int right_arr_size = right - mid;

  // Create temporary arrays
  int left_arr[left_arr_size], right_arr[right_arr_size];

  // Copy data to temporary arrays left_arr[] and right_arr[]
  for (int i = 0; i < left_arr_size; i++)
    left_arr[i] = arr[left + i];
  for (int j = 0; j < right_arr_size; j++)
    right_arr[j] = arr[mid + 1 + j];

  // Merge the temporary arrays back into arr[left..right]
  int i = 0;
  int j = 0;
  int k = left; // Initial index of merged subarray

  while (i < left_arr_size && j < right_arr_size) {
    if (left_arr[i] <= right_arr[j]) {
      arr[k] = left_arr[i];
      i++;
    } else {
      arr[k] = right_arr[j];
      j++;
    }
    k++;
  }

  // Copy the remaining elements of left_arr[], if any
  while (i < left_arr_size) {
    arr[k] = left_arr[i];
    i++;
    k++;
  }

  // Copy the remaining elements of right_arr[], if any
  while (j < right_arr_size) {
    arr[k] = right_arr[j];
    j++;
    k++;
  }
}

void merge_sort(int arr[], int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    // split the array till they have only one element
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);

    // Merge the sorted halves
    merge(arr, left, mid, right);
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
  merge_sort(arr, 0, size - 1);

  for (int i = 0; i < size; i++) {
    printf("%d\n", arr[i]);
  }
}
