/* Purpose: Calculates the profit of a farmers crop after a hail storm. If the crop is too damaged for sale, 
 * the cost of the seeds is deducted from the profit. Else the net sale price is added to the profit.
 * Author: Christopher Vander Veen
 * Date: Oct 7 2023
 * Persons discussed w/: None
 * References: None
 */

#include <stdio.h>

int main(void) {
  float profit = 0;
  int damaged = 0;
  char ch;

  while ((ch = getchar()) != EOF) {
        switch(ch) {
          case '/':
            damaged = 0;
            break;
          case '#':
            damaged = 1;
            break;
          case 'C':
            if (!damaged){
              profit += 0.45;
            }
            else {
              profit -= 0.05;
            }
            break;
          case 'T':
            if (!damaged){
              profit += 1.00;
            }
            else {
              profit -= 0.25;
            }
            break;
          case 'P':
            if (!damaged){
              profit += 2.30;
            }
            else{
              profit -= 0.70;
            }
            break;
          case 'L':
            if(!damaged){
              profit += 0.70;
            }
            else{
              profit -= 0.30;
            }
            break;
        }
  }
  if (profit < 0) {
    printf("Net profit: -$%.2f\n", -profit);
  } else {
    printf("Net profit: $%.2f\n", profit);
  }
  return 0;
}
