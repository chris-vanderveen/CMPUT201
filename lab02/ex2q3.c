/* Purpose: Takes input from the user about their book purchases
 * and automatically applies the appropriate discounts.
 * Author: Christopher Vander Veen 
 * Date: Sept 19 2023
 * Persons discussed w/: None
 * References: None
 */
#include <stdio.h>

int main() {
    int hardcover, softcover, ebook, res1, res2, res3;
    float total = 0, percentage = 0;

    printf("How many hardcover books are you buying? ");
    res1 = scanf("%d", &hardcover);

    printf("How many softcover books are you buying? ");
    res2 = scanf("%d", &softcover);

    printf("How many ebooks are you buying? ");
    res3 = scanf("%d", &ebook);

    // Improper input exit logic.
    if (!res1 || !res2 || !res3 || hardcover < 0 || hardcover >= 100000
     || softcover < 0 || softcover >= 100000 || ebook < 0 || ebook >= 100000) {
        printf("Improper input.");
        return 1;
    }

    total += hardcover * 15;
    total += softcover * 12;
    total += ebook * 7;

    // Logic to handle coupons
    if (hardcover >= 2) {
        total -= 5;
    }
    if (softcover >= 4) {
        total -= 10;
    }
    if (hardcover + softcover >= 6) {
        total -= 20;
    }

    // Logic for percentage discounts
    if (hardcover >= 1 && softcover >= 1 && ebook >= 1) {
        percentage += 3;
    }
    if (ebook >= 3) {
        percentage += 4;
    }
    if (total > 75) {
        percentage += 10;
    }
    if (total > 150) {
        percentage += 15;
    }

    // Re-calculate total with percentage discounts
    total -= total * (percentage/100);

    printf("Order total: $%.2f\n", total);
}
