/* Purpose: Finds a maximum and minimum value from a set of 20 integers and then prints the 
 * value of the expression x * max + y * min where x and y are two additional integers added
 * after the 20 integers.
 * Author: Christopher Vander Veen
 * Date: Sept 27 2023
 * Persons discussed w/: None
 * References: None
 */

#include <stdio.h>

int main(void) {
    int integer_list[22];
    int x, y;
    int max, min;

    printf("Enter 22 integers: ");

    if (scanf("%d", &integer_list[0]) != 1) { // Returns 1 if the first input is not an integer.``
        return 1;
    }
    max = min = integer_list[0]; // Sets max and min to be the value of the first integer input

    for (int i = 1; i < 22; i++) {
        if (scanf("%d", &integer_list[i]) != 1) { // scanf's the remaining 21 integers and returns 1 if not an integer.
            return 1;
        }
        if (i < 20) {
            if (integer_list[i] > max) { // Logic for setting min and max values
                max = integer_list[i];
            }
            if (integer_list[i] < min) {
                min = integer_list[i];
            }
        }
    }

    x = integer_list[20];
    y = integer_list[21];

    printf("x * max + y * min: %d\n", x * max + y * min);

    return 0;
}
