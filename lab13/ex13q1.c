/* Purpose: This program is designed to manage and query a set of students using a Disjoint Sets data structure. 
            It reads commands from a file, where each command is either 'j' followed by two student numbers, joining the two students
            in the same set, or '?' followed by two student numbers, querying whether the two students are in the same set. 
            The program prints 'T' if the two students are in the same set and 'F' otherwise. 
            It supports two modes of operation: a fast I/O mode that buffers output and prints it all at the end, and an easy I/O mode that prints output immediately.
 * Author: Christopher Vander Veen
 * Date: Dec 6, 2023
 * Persons discussed w/: None
 * References: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ex13q1.h"

#ifdef FASTIO
#define PRINTF(...) do { \
    len += snprintf(buff + len, sizeof(buff) - len, __VA_ARGS__); \
    if (len >= sizeof(buff) - 1) { \
        printf("%s", buff); \
        len = 0; \
    } \
} while(0)
char buff[2100000];
size_t len = 0;
#else
#define PRINTF(...) printf(__VA_ARGS__)
#endif

#define MAX_STUDENTS 3000000

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Invalid number of arguments.");
        return EXIT_FAILURE;
    }

    char *f = argv[3];

    handle_file(f);

#ifdef FASTIO
    printf("%s", buff);
    len = 0;
#endif

    return 0;
}

void handle_file(char* f) {
    FILE *file = fopen(f, "r");
    if (file == NULL) {
        PRINTF("Failed to open file %s\n", f);
        exit(EXIT_FAILURE);
    }

    DisjointSets *ds = createDisjointSets(MAX_STUDENTS);
    if (ds == NULL) {
        PRINTF("Failed to create disjoint sets\n");
        exit(EXIT_FAILURE);
    }

    char command;
    int num1, num2;

    while (fscanf(file, " %c %d %d", &command, &num1, &num2) == 3) {
        if (command == 'j') {
            unionSets(ds, num1, num2);
        } else if (command == '?') {
            if (find(ds, num1) == find(ds, num2)) {
                PRINTF("T\n");
            } else {
                PRINTF("F\n");
            }
        }
    }

    destroyDisjointSets(ds);
    fclose(file);
}

DisjointSets* createDisjointSets(int size) {
    DisjointSets *ds = malloc(sizeof(DisjointSets));
    ds->parent = malloc(size * sizeof(int));
    ds->rank = malloc(size * sizeof(int));
    ds->size = size;

    for (int i = 0; i < size; i++) {
        ds->parent[i] = i;
        ds->rank[i] = 0;
    }

    return ds;
}

int find(DisjointSets *ds, int i) {
    if (ds->parent[i] != i) {
        ds->parent[i] = find(ds, ds->parent[i]);
    }
    return ds->parent[i];
}

void unionSets(DisjointSets *ds, int i, int j) {
    int ri = find(ds, i);
    int rj = find(ds, j);

    if (ri != rj) {
        if (ds->rank[ri] < ds->rank[rj]) {
            ds->parent[ri] = rj;
        } else if (ds->rank[ri] > ds->rank[rj]) {
            ds->parent[rj] = ri;
        } else {
            ds->parent[ri] = rj;
            ds->rank[rj]++;
        }
    }
}

void destroyDisjointSets(DisjointSets *ds) {
    free(ds->parent);
    free(ds->rank);
    free(ds);
}