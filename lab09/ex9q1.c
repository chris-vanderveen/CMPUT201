/* Purpose: Uses the Levenshtien distance algorithm to compare each word in a given sentence with words in a 
 * predefined dictionary. The program identifies the most similar word in the dictionary and replaces the incorrect 
 * word with the similar word.
 * Author: Christopher Vander Veen
 * Date: Nov 8, 2023
 * Persons discussed w/: None
 * References: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int levenshtienDistance(char* string1, char* stirng2);
int findMin(int deletion, int insertion, int substitution);
void replace(char** sentence, int sizeSentence, char** dictionary, int numWords);

int main(void) {
    int sizeDict, numLines, sizeWord;

    scanf("%d %d", &sizeDict , &numLines);

    char** dictionary = (char**)malloc(sizeDict * sizeof(char*));
    for (int i = 0; i < sizeDict; i++) {
        dictionary[i] = (char*)malloc(11 * sizeof(char));
    }

    for (int i = 0; i < sizeDict; i++) {
        scanf("%s", dictionary[i]);
    }

    for (int i = 0; i < numLines; i++) {
        char** sentence = (char**)malloc(10 * sizeof(char*));
        for (int j = 0; j < 10; j++) {
            sentence[j] = (char*)malloc(11 *sizeof(char));
        }

        // Count how many words are in the sentence array.
        int sizeSentence = 0; 
        while (scanf("%s", sentence[sizeSentence]) == 1) {
            sizeSentence++;
            if (getchar() == '\n') {
                break;
            }
        }

        replace(sentence, sizeSentence, dictionary, sizeDict);

        for (int j = 0; j < sizeSentence; j++) {
            free(sentence[j]);
        }
        free(sentence);
    }

    for (int i = 0; i < sizeDict; i++) {
        free(dictionary[i]);
    }
    free(dictionary);

    return 0;
}

// Function to calculate the Levenshtein distance between two strings.  
int levenshtienDistance(char* string1, char* string2) {
    int len1 = strlen(string1), len2 = strlen(string2);
    int insertion, deletion, substitution;

    int** d = (int**)malloc((len1 + 1) * sizeof(int*)); // Initialize 2D array d.
    for (int i = 0; i < len1 + 1; i++) {
        d[i] = (int*)malloc((len2 + 1) * sizeof(int));
    }

    for (int i = 0; i < len1 + 1; i++) { // Initialize the first column.
        d[i][0] = i;
    }

    for (int j = 0; j < len2 + 1; j++) { // Initialize first row.
        d[0][j] = j;
    }

    // Fill the rest of the array.
    for (int i = 1; i < len1 + 1; i++){
        for (int j = 1; j < len2 + 1; j++) { 
            if (string1[i - 1] == string2[j - 1]) {
                d[i][j] = d[i - 1][j - 1];
            }
            else {
                deletion = d[i - 1][j];
                insertion = d[i][j - 1];
                substitution = d[i - 1][j - 1];

                d[i][j] = 1 + findMin(deletion, insertion, substitution);
            }
        }
    }
    int distance = d[len1][len2];

    for (int i = 0; i < len1 + 1; i++) { // Free the memory inside the array.
        free(d[i]);
    }
    free(d); // Free the remainder of the array. 

    return distance;
}

// Function to find the minimum of three values.
int findMin(int deletion, int insertion, int substitution) { 
    if (deletion <= insertion && deletion <= substitution) {
        return deletion;
    }
    else if (insertion <= deletion && insertion <= substitution) {
        return insertion;
    }
    else {
        return substitution;
    }
}

// Function to replace each word in the sentence with the closest word from the dictionary.
void replace(char** sentence, int sizeSentence, char** dictionary, int numWords) {
    int minDistance, distance;
    char* closest;
    // Loop through each word in the sentence.
    for (int i = 0; i < sizeSentence; i++) {
        minDistance = INT_MAX;
        closest = NULL;

        // Loop through each word in the dictionary.
        for (int j = 0; j < numWords; j++) {
            distance = levenshtienDistance(sentence[i], dictionary[j]);
            // If the distance is smaller than the smallest so far, update closest.
            if (distance < minDistance) {
                minDistance = distance;
                closest = dictionary[j];
            }
        }
        printf("%s ", closest);
    }
    printf("\n");
}