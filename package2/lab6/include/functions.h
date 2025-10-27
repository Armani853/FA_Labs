#include "status_codes.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX_STR_LEN 50
#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2
#define EXAM_COUNT 5
#define MAX_INPUT_BUFFER 100

typedef struct {
    unsigned int id;
    char name[MAX_STR_LEN];
    char surname[MAX_STR_LEN];
    char group[MAX_STR_LEN];
    unsigned char* grades;
} Student;

typedef struct {
    Student* array;
    size_t count;
    size_t capacity;
} Student_collection;

enum {
    Field_Surname,
    Field_Name,
    Field_Group
};

void print_status(StatusCode s);

StatusCode validate_name_surname(const char* str);

StatusCode student_create(Student* s_out, unsigned int id, const char* name, const char* surname, const char* group, const unsigned char* grades);

double student_calculate_avg_grade(const Student* s);

void student_free(Student* s);

void collection_init(Student_collection* c);

void collection_free(Student_collection* c);

StatusCode collection_resize(Student_collection* c);

StatusCode collection_load_from_file(Student_collection* c, const char* filepath);

double collection_calculate_global_avg(const Student_collection* c);

const Student* search_by_id(const Student_collection* c, unsigned int id, StatusCode* st);

StatusCode search_by_string(const Student_collection* c, const char* search_key, int field_type, const Student*** results, size_t* result_count);

int compare_by_id(const void *a, const void *b);

int compare_by_surname(const void *a, const void *b);

int compare_by_name(const void *a, const void *b);

int compare_by_group(const void *a, const void *b);

void sort_collection(Student_collection* c, int (*comparator)(const void *, const void *));

StatusCode report_student_data(const Student* s, const char* filepath);

StatusCode report_above_avg_students(const Student_collection* c, double global_avg, const char* filepath);

StatusCode get_unsigned_int(const char* prompt, unsigned int* value);

StatusCode get_string(const char* prompt, char* buffer, size_t max_len);

void handle_search(const Student_collection* c, const char* report_filepath);

void handle_sort(Student_collection *c);

void handle_report_avg(const Student_collection *c, const char *report_filepath);



