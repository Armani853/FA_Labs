#include "status_codes.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#define MAX_NAME_LEN 50
#define MAX_DATE_LEN 11
#define CURRENT_YEAR 2025

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    unsigned int id;
    char surname[MAX_NAME_LEN];
    char first_name[MAX_NAME_LEN];
    char second_name[MAX_NAME_LEN];
    Date dob;
    char gender;
    double avg_income;
} Liver;


#define LIST_TYPE Liver

typedef struct Node {
    LIST_TYPE data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    size_t size;
} LinkedList;

typedef enum {
    MOD_ADD,
    MOD_DELETE,
    MOD_UPDATE,
} ModificationType;

typedef struct {
    ModificationType type;
    Liver old_data;
    unsigned int target_id;
    size_t target_index;
} Modification;

typedef LinkedList UndoStack;

StatusCode liver_validate(const Liver* l);

void liver_print(const Liver* l);

StatusCode liver_copy(const Liver* src, Liver* dest);

int liver_compare_age(const Liver* l1, const Liver* l2);

int liver_get_age(const Date* dob);

Node* create_node(const LIST_TYPE* value);

LinkedList* create_list(void);

void erase_list(LinkedList* list);

void delete_list(LinkedList* list);

StatusCode push_back_list(LinkedList* list, const LIST_TYPE* value);

StatusCode push_front_list(LinkedList* list, const LIST_TYPE* value);

StatusCode pop_back_list(LinkedList* list, LIST_TYPE* result);

StatusCode pop_front_list(LinkedList* list, LIST_TYPE* result);

StatusCode insert_at_list(LinkedList* list, size_t index, const LIST_TYPE* value);

StatusCode delete_at_list(LinkedList* list, size_t index);

StatusCode get_at_list(const LinkedList* list, size_t index, LIST_TYPE* result);

StatusCode is_equal_list(const LinkedList* l1, const LinkedList* l2);


StatusCode push_stack(LinkedList* stack, const LIST_TYPE* value);

StatusCode pop_stack(LinkedList* stack, LIST_TYPE* result);

StatusCode peek_stack(const LinkedList *stack, LIST_TYPE *result);

StatusCode enqueue(LinkedList* queue, const LIST_TYPE* value);

StatusCode dequeue(LinkedList* queue, LIST_TYPE* result);

StatusCode peek_queue(const LinkedList* queue, LIST_TYPE* result);


StatusCode read_data_from_file(const char *filename, LinkedList *list);

StatusCode write_data_to_file(const char *filename, const LinkedList *list);

StatusCode insert_ordered_liver(LinkedList *list, const Liver *new_liver);

StatusCode update_liver_by_id(LinkedList *list, UndoStack *undo, unsigned int id, const Liver *new_data);

StatusCode delete_liver_by_id(LinkedList *list, UndoStack *undo, unsigned int id);

StatusCode perform_undo(LinkedList *list, UndoStack *undo);

Node* get_node_at(const LinkedList *list, size_t index);

Node* find_node_by_id(LinkedList *list, unsigned int id, size_t *index);

StatusCode find_liver_data_by_id(const LinkedList *list, unsigned int id, Liver *result);

int is_latin_letters(const char *s);

int is_valid_date(const Date *d);

Node* find_node_by_id(LinkedList *list, unsigned int id, size_t *index);


