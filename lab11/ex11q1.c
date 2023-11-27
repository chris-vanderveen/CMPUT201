/* Purpose: Tests the runtime of three different data structures; Vectors, Singly Linked Lists, and Doubly Linked Lists. Compares runtime to evaluate 
 *          real world performance differences between the three. 
 * Author: Christopher Vander Veen
 * Date: Nov 26, 2023
 * Persons discussed w/: None
 * References: None
 */
#include "ex11q1.h"

// ############################################################################
// Vector
// ############################################################################
Vec* vec_create(void) {
    Vec* vec = malloc(sizeof(Vec));
    vec->length = 0;
    vec->capacity = 10;
    vec->storage = malloc(vec->capacity * sizeof(int));
    
    return vec;
}

void vec_insert_at(Vec* vec, int at, int item) {
    if (vec->length == vec->capacity) {
        vec->capacity *= 2;
        vec->storage = realloc(vec->storage, vec->capacity * sizeof(int));
        if (vec->storage == NULL) {
            return;
        }
    }

    for (int i = vec->length; i > at; i--) {
        vec->storage[i] = vec->storage[i - 1];
    }

    vec->storage[at] = item;
    vec->length++;
}

void vec_print(Vec* vec) {
    printf("[");
    for (int i = 0; i < vec->length; i++) {
        printf("%d", vec->storage[i]);
        if (i < vec->length - 1) {
            printf(", ");
        }

    }
    printf("]\n");
}

void vec_free(Vec* vec) {
    free(vec->storage);
    free(vec);
}

// ############################################################################
// Linked List
// ############################################################################
LinkedListNode* list_node_create(int item) {
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    
    node->item = item;
    node->next = NULL;
    return node;
}

LinkedList* list_create(void) {
    LinkedList* list = malloc(sizeof(LinkedList));
    
    list->length = 0;
    list->start = NULL;
    return list;
}

void list_insert_at(LinkedList* list, int at, int item) {
    LinkedListNode* new_node = list_node_create(item);

    if (at == 0) {
        new_node->next = list->start;
        list->start = new_node;
    } else {
        LinkedListNode* node = list->start;
        for (int i = 0; i < at - 1; i++) {
            node = node->next;
        }
        new_node->next = node->next;
        node->next = new_node;
    }

    list->length++;
}

void list_print(LinkedList* list) {
    LinkedListNode* node = list->start;
    printf("[");
    while (node != NULL) {
        printf("%d", node->item);
        if (node->next != NULL) {
            printf(", ");
        }
        node = node->next;
    }
    printf("]\n");
}

void list_free(LinkedList* list) {
    LinkedListNode* node = list->start;
    LinkedListNode* temp;

    while (node != NULL) {
        temp = node;
        node = node->next;
        free(temp);
    }

    free(list);
}

 //############################################################################
 //Doubly Linked List
 //############################################################################
DoublyLinkedListNode* dlist_node_create(int item) {
    DoublyLinkedListNode* node = malloc(sizeof(DoublyLinkedListNode));

    node->item = item;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

DoublyLinkedList* dlist_create(void) {
    DoublyLinkedList* list = malloc(sizeof(DoublyLinkedList));

    list->length = 0;
    list->start = NULL;
    list->end = NULL;
    return list;
}

void dlist_insert_at(DoublyLinkedList* list, int at, int item) {
    DoublyLinkedListNode* new_node = dlist_node_create(item);

    if (at == 0) {
        new_node->next = list->start;
        if (list->start != NULL) {
            list->start->prev = new_node;
        }
        list->start = new_node;
        if (list->end == NULL) {
            list->end = new_node;
        }
    } else {
        DoublyLinkedListNode* node = list->start;
        for (int i = 0; i < at - 1; i++) {
            node = node->next;
        }
        new_node->next = node->next;
        new_node->prev = node;
        if (node->next != NULL) {
            node->next->prev = new_node;
        }
        node->next = new_node;
        if (list->end == node) {
            list->end = new_node;
        }
    }

    list->length++;
}

void dlist_print(DoublyLinkedList* list) {
    DoublyLinkedListNode* node = list->start;
    printf("[");
    while (node != NULL) {
        printf("%d", node->item);
        if (node->next != NULL) {
            printf(", ");
        }
        node = node->next;
    }
    printf("]\n");
}

void dlist_free(DoublyLinkedList* list) {
    DoublyLinkedListNode* node = list->start;
    DoublyLinkedListNode* temp;

    while (node != NULL) {
        temp = node;
        node = node->next;
        free(temp);
    }

    free(list);
}

 //############################################################################
 //Main
 //############################################################################
int main(void) {
    char line[1000];
     // Uncomment each for loop as you implement that part

    clock_t begin_vec = clock();
    Vec* v = vec_create();

    for (int i = 0; i < 100000; i++) {
        int a, b;
        if (getchar() == 'i') {
            scanf("%s %d %s %d\n", line, &a, line, &b);
            vec_insert_at(v, b, a);
        } else {
            scanf("%s\n", line);
            vec_print(v);
        }
    }

    vec_free(v);
    clock_t end_vec = clock();

    clock_t begin_list = clock();
    LinkedList* l = list_create();

    for (int i = 0; i < 100000; i++) {
        int a, b;
        if (getchar() == 'i') {
            scanf("%s %d %s %d\n", line, &a, line, &b);
            list_insert_at(l, b, a);
        } else {
            scanf("%s\n", line);
            list_print(l);
        }
    }

    list_free(l);
    clock_t end_list = clock();

    clock_t begin_dlist = clock();
    DoublyLinkedList* dlist = dlist_create();

    for (int i = 0; i < 100000; i++) {
        int a, b;
        if (getchar() == 'i') {
            scanf("%s %d %s %d\n", line, &a, line, &b);
            dlist_insert_at(dlist, b, a);
        } else {
            scanf("%s\n", line);
            dlist_print(dlist);
        }
    }

    dlist_free(dlist);
    clock_t end_dlist = clock();

    fprintf(stderr, "Vector: %gs\n", (double)(end_vec - begin_vec) / CLOCKS_PER_SEC);
    fprintf(stderr, "Linked List: %gs\n", (double)(end_list - begin_list) / CLOCKS_PER_SEC);
    fprintf(stderr, "Doubly Linked List: %gs\n", (double)(end_dlist - begin_dlist) / CLOCKS_PER_SEC);
}