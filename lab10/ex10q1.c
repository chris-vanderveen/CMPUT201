/* Purpose: This program simulates a queue of students waiting for autographs, with special rules for CMPUT 201 and non-CMPUT 201 students. 
            It reads commands from stdin to add students to the queue, remove the first student (who got an autograph), or remove the last student (who couldn't wait any longer). 
            The output is the ID of each student as they leave the queue.
 * Author: Christopher Vander Veen
 * Date: Dec 02, 2023
 * Persons discussed w/: None
 * References: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ex10q1.h"

#define DEFAULT_RING_CAPACITY 8

int main(void) {
    Ring* ring = init_ring();
    char** result;
    Student* front_student;

    while((result = parser()) != NULL) {
        if (result[0][0] == 'F') {
            front_student = dequeue(ring);
            if (front_student == NULL) {
                printf("empty\n");
            } else {
                printf("%s\n", front_student->id);
            }
        } else if (result[0][0] == 'L') {
            dequeue_last(ring);
        } else {
            Student* student = init_student(result[0][0], atoi(result[1]), result[2]);
            if (result[0][0] == 'C') {
                int pos = (ring->length + 1) / 2;
                if (pos < student->maxWait) {
                    push_at(ring, *student, pos);
                }
            } else if (result[0][0] == 'N' && student->maxWait > ring->length) {
                push_back(ring, *student);
            }
        }
        for (int i = 0; i < 3; i++) {
            free(result[i]);
        }
        free(result);
    }
    free_ring(ring);
    return 0;
}

char** parser(void) {
    char** result = malloc(3 * sizeof(char*));
    for (int i = 0; i < 3; i++) {
        result[i] = malloc(8 * sizeof(char));
    }

    char line[12];
    if (fgets(line, 12, stdin) == NULL) {
        for (int i = 0; i < 3; i++) {
            free(result[i]);
        }
        free(result);
        return NULL;
    }

    if (line[0] == 'F' || line[0] == 'L') {
        result[0][0] = line[0];
        result[0][1] = '\0';
        return result;
    }

    char type;
    int maxWait;
    char id[8];

    sscanf(line, "%c %d %s", &type, &maxWait, id);

    result[0][0] = type;
    result[0][1] = '\0';
    sprintf(result[1], "%d", maxWait);
    strcpy(result[2], id);

    return result;
}

Student* init_student(char type, int maxWait, char* id) {
    Student* student = malloc(sizeof(Student));

    student->id = malloc((strlen(id) + 1) * sizeof(char));
    strcpy(student->id, id);

    student->type = type;
    student->maxWait = maxWait;

    return student;
}

Ring* init_ring(void) {
    Ring * ring = malloc(sizeof(Ring));

    ring->head = (Student*)malloc(DEFAULT_RING_CAPACITY * sizeof(Student));
    ring->start = ring->head;
    ring->end = ring->head;
    ring->length = 0;
    ring->capacity = DEFAULT_RING_CAPACITY;

    return ring;
}

void push_front(Ring* ring, Student student) {
    if (ring->length == ring->capacity) {
        increase_ring_size(ring);
    }

    if (ring->start == ring->head) {
        ring->start = ring->head + ring->capacity - 1;
    } else {
        ring->start--;
    }

    *ring->start = student;
    ring->length++;
}

void push_at(Ring* ring, Student student, int pos) {
    if (ring->length == ring->capacity) {
        increase_ring_size(ring);
    }

    if (pos < 0 || pos > ring->length) {
        return;
    }

    int insertPos = (ring->start - ring->head + pos) % ring->capacity;

    for (int i = ring->length; i > pos; i--) {
        int currPos = (ring->start - ring->head + i) % ring->capacity;
        int prevPos = (ring->start - ring->head + i - 1) % ring->capacity;
        ring->head[currPos] = ring->head[prevPos];
    }

    ring->head[insertPos] = student;
    ring->length++;
}

void push_back(Ring* ring, Student student) {
    if (ring->length == ring->capacity) {
        increase_ring_size(ring);
    }

    int end = (ring->start - ring->head + ring->length) % ring->capacity;
    ring->head[end] = student;
    ring->length++;
}

Student* dequeue(Ring* ring) {
    if (ring->length == 0) {
        return NULL;
    }

    Student* front_student = malloc(sizeof(Student));
    *front_student = *ring->start;
    ring->start = ring->head + ((ring->start - ring->head + 1) % ring->capacity);
    ring->length--;

    return front_student;
}

int dequeue_last(Ring* ring) {
    if (ring->length == 0) {
        printf("empty\n");
        return 0;
    }

    ring->length--;
    return 1;
}

void increase_ring_size(Ring* ring) {
    int new_capacity = ring->capacity * 2;
    Student* new_buffer = malloc(new_capacity * sizeof(Student));

    for (int i = 0; i < ring->length; i++) {
        int old_index = (ring->start - ring->head + i) % ring->capacity;
        new_buffer[i] = ring->head[old_index];
    }

    free(ring->head);

    ring->head = new_buffer;
    ring->start = new_buffer;
    ring->capacity = new_capacity;
}

void free_ring(Ring* ring) {
    for (int i = 0; i < ring->capacity; i++) {
        free(ring->head[i].id);
    }
    free(ring->head);
    free(ring);
}

// Only used for debugging purposes
void print_student(Student* student) {
    printf("-------------------------\n");
    printf("Student ID: %s\n", student->id);
    printf("Student Type: %c\n", student->type);
    printf("Student MaxWait: %d\n\n", student->maxWait);
}

// Only used for debugging purposes
void print_ring(Ring* ring) {
    printf("-------------------------------\n");
    printf("|        Updated Ring         |\n");
    printf("-------------------------------\n");
    printf("Ring Capacity: %d\n", ring->capacity);
    printf("Ring Length: %d\n\n", ring->length);

    int position = 0;
    Student* current = ring->start;

    while (position < ring->length) {
        printf("Position: %d\n", position);
        print_student(current);
        current++;
        if (current == ring->head + ring->capacity) {
            current = ring->head;
        }
        position++;
    }
}