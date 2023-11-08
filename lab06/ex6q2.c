/* Purpose: Implementations of bubble sort, gnome sort, insertion sort, and comb sort. 
 * Author: Christopher Vander Veen
 * Date: Oct 23, 2023
 * Persons discussed w/: None
 * References: https://www.geeksforgeeks.org/insertion-sort/,
 *             https://en.wikipedia.org/wiki/Comb_sort
 */

#include "ex6q2.h"

// Please don't change anything in this main function!
int main(void) {
    if (!test_bubble(bubble_sort))
        fprintf(stderr, "Bubble sorting failed\n");
    if (!test_gnome(gnome_sort))
        fprintf(stderr, "Gnome sorting failed\n");
    if (!test_insertion(insertion_sort))
        fprintf(stderr, "Insertion sorting failed\n");
    if (!test_custom(custom_sort)) {
        fprintf(stderr, "Custom sorting failed\n");
	}
	return 0;
}

void bubble_sort(int n, int arr[n]) {
  int temp;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n-i-1; j++) {
      if (arr[j] > arr[j+1]) {
        temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;
      }
    } 
  }
}

// Not very well known, but very easy!
// Check out the description on here https://en.wikipedia.org/wiki/Gnome_sort
void gnome_sort(int n, int arr[n]) {
  int pos = 0, temp;
  
  while (pos < n){
    if (pos == 0 || arr[pos] >= arr[pos-1]) {
      pos++;
    } else {
      temp = arr[pos];
      arr[pos] = arr[pos-1];
      arr[pos-1] = temp;
      pos--;
    }
  }
}

void insertion_sort(int n, int arr[n]) {
  int key, j;

  for (int i = 1; i < n; i++) {
    key = arr[i];
    j = i - 1;

    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + i] = key;
  }
}


// The sort you found! (See lab description for details)
void custom_sort(int n, int arr[n]) {
  int gap = n, sorted = 0, temp;
  float shrink = 1.3;

  while (!sorted) {
    gap = (int)(gap/shrink);

    if (gap <= 1) {
      gap = 1;
      sorted = 1;
    }
  
    int i = 0;
    while (i + gap < n) {
      if (arr[i] > arr[i+gap]) {
        temp = arr[i];
        arr[i] = arr[i+gap];
        arr[i+gap] = temp;
        sorted = 0;
      }
      i++;
    }
  }
}
