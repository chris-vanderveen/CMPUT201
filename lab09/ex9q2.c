/* Purpose: This program performs arithmetic operations on large numbers represented as strings. 
 * It supports addition and a custom "rotation" operation. The addition operation adds two large numbers,
 * and the rotation operation rotates the digits of the first number by a number specified by the second number.
 * Author: Christopher Vander Veen
 * Date: Nov 11, 2023
 * Persons discussed w/: None
 * References: None
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void add(char* num1, char* num2, char* result);
void rot(char* num1, char* num2);

int main(void) {
    int num_lines;
    char num1[102], operator[4], num2[102];
    char *result;

    scanf("%d", &num_lines);

    for (int i = 0; i < num_lines; i++) {
        scanf("%s %s %s", num1, operator, num2);

        if (strcmp(operator, "+") == 0) {
            result = (char *)malloc(strlen(num1) + strlen(num2) + 1);
            add(num1, num2, result);
            printf("%s\n", result);
            free(result);
        }
        else if (strcmp(operator, "@") == 0) {
            result = (char *)malloc(strlen(num1) + strlen(num2) + 1);
            strcpy(result, num1);
            strcat(result, num2);
            printf("%s\n", result);
            free(result);
        }
        else if (strcmp(operator, "rot") == 0) {
            rot(num1, num2);
            printf("%s\n", num1);
        }
    }

    return 0;
}

void add(char* num1, char* num2, char* result) {
    int len, carry = 0;
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    if (len1 > len2)
        len = len1;
    else
        len = len2;

    // Initialize result with '0's
    for (int i = 0; i < len; i++) {
        result[i] = '0';
    }

    // Add digits of num1 and num2
    for (int i = len1 - 1, j = len2 -1; i >= 0 || j >= 0; i--, j--) {
        int sum = carry;
        if (i >= 0) {
            sum += num1[i] - '0';
        }
        if (j >= 0) {
            sum += num2[j] - '0';
        }
        result[len - 1] = sum % 10 + '0'; // Store least significant digit of sum in result
        len--;
        carry = sum / 10;
    }

    // Handle the carry from the last addition 
    if (carry > 0) {
        // Shift to the right and insert carry at beginning
        for (int i = len; i >=0; i--) {
            result[i + 1] = result[i];
        }
        result[0] = carry + '0';
    }

    result[strlen(result)] = '\0';
}

void rot(char* num1, char* num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int rotations = 0;

    // Calculate number of rotations.
    for (int i = 0; i < len2; i++) {
        rotations = (rotations * 10 + (num2[i] - '0')) % len1;
    }

    // Keep characters to be rotated in temp string
    char* temp = (char *)malloc(rotations + 1);
    strncpy(temp, num1, rotations);
    temp[rotations] = '\0';

    // Shift the remaining characters to the left
    for (int i = rotations; i < len1; i++) {
        num1[i - rotations] = num1[i];
    }

    // Add temp to num1
    strcpy(num1 + len1 - rotations, temp);

    // Remove leading zeros, but not if num1 is "0"
    while (num1[0] == '0' && num1[1] != '\0') {
        int i = 0;
        while (num1[i]) {
            num1[i] = num1[i + 1];
            i++;
        }
    }

    free(temp);
}