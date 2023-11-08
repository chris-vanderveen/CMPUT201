/* Purpose: Organizes IKEA DJUNGLESKOG for different stores based upon the serial number of the items. 
 * Author: Christopher Vander Veen
 * Date: Oct 28, 2023
 * Persons discussed w/: None
 * References: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addItem(char **store, int *counts, int serialNumber, char itemType, int numAisles);
void printAisle(char **store, int *counts, int aisleIndex);
void freeMemory(char **store, int *counts, int numAisles);

int main() {
    int numAisles;
    scanf("%d", &numAisles);
    getchar();

    char** store = (char**)malloc(numAisles * sizeof(char*));
    int* counts = (int*)malloc(numAisles * sizeof(int));

    for (int i = 0; i < numAisles; i++) {
        store[i] = NULL;
        counts[i] = 0;
    }

    char line[100];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        int command;
        sscanf(line, "%d", &command);

        if (command == 0) {
            int aisleIndex;
            sscanf(line, "%d %d", &command, &aisleIndex);
            printAisle(store, counts, aisleIndex);
        } else {
            char itemType;
            int serialNumber;
            sscanf(line, "%d %c", &serialNumber, &itemType);
            addItem(store, counts, serialNumber, itemType, numAisles);
        }
    }

    freeMemory(store, counts, numAisles);
    return 0;
}

void addItem(char **store, int *counts, int serialNumber, char itemType, int numAisles) {
    int aisleIndex = serialNumber % numAisles;
    counts[aisleIndex]++;
    store[aisleIndex] = (char*)realloc(store[aisleIndex], counts[aisleIndex] * sizeof(char));
    store[aisleIndex][counts[aisleIndex] - 1] = itemType;
}

void printAisle(char **store, int *counts, int aisleIndex) {
    for (int j = 0; j < counts[aisleIndex]; j++) {
        printf("%c", store[aisleIndex][j]);
    }
    printf("\n");
}

void freeMemory(char **store, int *counts, int numAisles) {
    for (int i = 0; i < numAisles; i++) {
        free(store[i]);
    }
    free(store);
    free(counts);
}
