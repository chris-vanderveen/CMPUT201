/* Purpose: Converts CAD to USD and then determines the least
 * amount of USD bills to make up the amount, rounded to the nearest USD.
 * Author: Christopher Vander Veen 
 * Date: Sept 18 2023
 * Persons discussed w/: None
 * References: None
 */

# include <stdio.h>

int main() {
    int CAD, USD, convertedUSD, result; // USD will initially be represented in cents.
    const int conversion = 75; // Conversion rate in cents.
    int hundreds = 0, fifties = 0, twenties = 0;
    int tens = 0, fives = 0, twos = 0, ones = 0;

    printf("Enter CAD amount: ");
    result = scanf("%d", &CAD);

    // Logic for exit in case of improper input.
    if (result != 1 || CAD < 0) {
        printf("Invalid input.\n");
        return 1;
    }
    // Calculates USD in cents.
    USD = CAD * conversion;
    // Logic to determine rounding.
    if (USD % 100 >= 50) {
        USD += 100 - (USD % 100);
    }
    // if the if statement is not satisfied, this will remove any decimal points.
    convertedUSD = USD / 100;
    printf("Converted USD amount: $%d\n", convertedUSD);

    // Logic for converting USD into bills
    while (convertedUSD > 0) {
        if (convertedUSD >= 100) {
            hundreds += convertedUSD / 100;
            convertedUSD -= (hundreds * 100);
        }
        else if (convertedUSD >= 50) {
            fifties += convertedUSD / 50;
            convertedUSD -= (fifties * 50);
        }
        else if (convertedUSD >= 20) {
            twenties += convertedUSD / 20;
            convertedUSD -= (twenties * 20);
        }
        else if (convertedUSD >= 10) {
            tens += convertedUSD / 10;
            convertedUSD -= (tens * 10);
        }
        else if (convertedUSD >= 5) {
            fives += convertedUSD / 5;
            convertedUSD -= (fives * 5);
        }
        else if (convertedUSD >= 2) {
            twos += convertedUSD / 2;
            convertedUSD -= (twos * 2);
        }
        else {
            ones = convertedUSD;
            convertedUSD = 0;
        }
    }

    printf("$100 bills: %d\n"
       " $50 bills: %d\n"
       " $20 bills: %d\n"
       " $10 bills: %d\n"
       "  $5 bills: %d\n"
       "  $2 bills: %d\n"
       "  $1 bills: %d\n",
       hundreds, fifties, twenties, tens, fives, twos, ones);

    return 0;
}
