#include "ex8q1.h"
#include <stdlib.h>

int main(void) {
    int is_print, value, size = 0;
    float index, *indices = NULL;
    int *values = NULL;

    while (!feof(stdin)) {
        read_line(&is_print, &index, &value);

        if (!is_print) {
            int pos = 0;
            while (pos < size && indices[pos] < index) {
                pos++;
            }

            if (pos < size && indices[pos] == index) {
                // Index already exists, update the value
                values[pos] = value;
            } else {
                // Index doesn't exist, insert new index and value
                indices = realloc(indices, (size + 1) * sizeof(float));
                values = realloc(values, (size + 1) * sizeof(int));

                for (int i = size; i > pos; i--) {
                    indices[i] = indices[i - 1];
                    values[i] = values[i - 1];
                }

                indices[pos] = index;
                values[pos] = value;
                size++;
            }
        } else {
            printf("[");
            for (int i = 0; i < size; i++) {
                printf("%d", values[i]);
                if (i < size - 1) {
                    printf(", ");
                }
            }
            printf("]\n");
        }
    }

    free(indices);
    free(values);
    return 0;
}