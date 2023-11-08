/* Purpose: Finds a maximum and minimum value from a set of 20 integers and then prints the 
 * value of the expression x * max + y * min where x and y are two additional integers added
 * after the 20 integers.
 * Author: Christopher Vander Veen
 * Date: Sept 27 2023
 * Persons discussed w/: None
 * References: None
 */

#include <stdio.h>

void swap(float* a, float* b) {
  float temp = *a;
  *a = *b;
  *b = temp;
}

int partition(float arr[], int low, int high) {
  // Set pivot to last element in array
  float pivot = arr[high];

  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (arr[j] < pivot) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}

void quicksort(float arr[], int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);

    quicksort(arr, low, pi -1);
    quicksort(arr, pi + 1, high);
  }
}

int main(void) {
  int loaded_boxes = 0, num_boxes;
  float truck_capacity = 0, current_weight = 0;

  scanf("%d", &num_boxes);
   // Dynamically assign size of box_weights array to num_boxes.
  float box_weights[num_boxes]; 
 
  // Populate the box_weights array.
  for (int i = 0; i < num_boxes; i++){
    scanf("%f", &box_weights[i]);
  }
  
  // Sort box_weights array
  quicksort(box_weights, 0, num_boxes - 1);

  while (scanf("%f", &truck_capacity) == 1) {
    for (int i = 0; i < num_boxes; i++) {
      if (current_weight + box_weights[i] <= truck_capacity) {
        current_weight += box_weights[i];
        loaded_boxes++;
      } else {
        break;
      }
    }
    printf("%d\n", loaded_boxes);
    current_weight = 0;
    loaded_boxes = 0;
  }
}
