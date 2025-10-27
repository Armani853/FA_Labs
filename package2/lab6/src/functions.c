#include "../include/functions.h"


void print_status(StatusCode s) {
    printf("Статус: ");
    switch (s) {
        case STATUS_OK:
            printf("Операция выполнена успешно.\n");
            break;
        case INVALID_INPUT:
            printf("ОШИБКА: Неверный ввод.\n");
            break;
        case MEMORY_ERROR:
            printf("ОШИБКА: Невозможно выделить/перевыделить память.\n");
            break;
        case OPEN_ERROR:
            printf("ОШИБКА: Невозможно открыть файл.\n");
            break;
        case READ_ERROR:
            printf("ОШИБКА: Ошибка чтения данных из файла.\n");
            break;
        case WRITE_ERROR:
            printf("ОШИБКА: Ошибка записи в файл.\n");
            break;
        default:
            printf("Неизвестный статус.\n");
            break;
    }
}

StatusCode validate_name_surname(const char* str) {
    if (str == NULL || *str == '\0') {
        return INVALID_INPUT;
    }
    size_t len = strlen(str);
    if (len >= MAX_STR_LEN) {
        return INVALID_INPUT;
    }
    
    for (size_t i = 0; i < len; i++) {
        char c = str[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            return INVALID_INPUT;
        }
    }
    return STATUS_OK;
}

StatusCode student_create(Student* s_out, unsigned int id, const char* name, const char* surname, const char* group, const unsigned char* grades) {
    if (s_out == NULL || name == NULL || surname == NULL || group == NULL || grades == NULL) {
        return INVALID_INPUT;
    }
    if (validate_name_surname(name) != STATUS_OK || validate_name_surname(surname) != STATUS_OK) {
        return INVALID_INPUT;    
    }
    if (group[0] == '\0' || strlen(group) >= MAX_STR_LEN) {
        return INVALID_INPUT;
    }

    unsigned char* new_grades = (unsigned char* )malloc(EXAM_COUNT * sizeof(unsigned char));
    if (new_grades == NULL) {
        return MEMORY_ERROR;
    }

    s_out->id = id;
    strncpy(s_out->name, name, MAX_STR_LEN - 1);
    s_out->name[MAX_STR_LEN - 1] = '\0';
    strncpy(s_out->surname, surname, MAX_STR_LEN - 1);
    s_out->surname[MAX_STR_LEN - 1] = '\0';
    strncpy(s_out->group, group, MAX_STR_LEN - 1);
    s_out->group[MAX_STR_LEN - 1] = '\0';
    for (int i = 0; i < EXAM_COUNT; i++) {
        new_grades[i] = grades[i];
    }
    s_out->grades = new_grades;

    return STATUS_OK;
}

double student_calculate_avg_grade(const Student* s) {
    if (s == NULL || s->grades == NULL) {
        return 0.0;
    }
    unsigned int sum = 0;
    for (int i = 0; i < EXAM_COUNT; i++) {
        sum += s->grades[i];
    }
    return (double)sum / EXAM_COUNT;
}

void student_free(Student* s) {
    if (s != NULL && s->grades != NULL) {
        free(s->grades);
        s->grades = NULL;
    }
}

void collection_init(Student_collection* c) {
    c->array = NULL;
    c->count = 0;
    c->capacity = 0;
}

void collection_free(Student_collection* c) {
    if (c == NULL) {
        return;
    }
    for (size_t i = 0; i < c->count; i++) {
        student_free(&c->array[i]);
    }
    if (c->array != NULL) {
        free(c->array);
        c->array = NULL;
    }
    c->count = 0;
    c->capacity = 0;
}

StatusCode collection_resize(Student_collection* c) {
    size_t new_capacity;
    if (c->capacity == 0) {
        new_capacity = INITIAL_CAPACITY;
    } else {
        new_capacity = c->capacity * GROWTH_FACTOR;
    }
    Student* new_array = (Student* )realloc(c->array, new_capacity * sizeof (Student));
    if (new_array == NULL) {
        return MEMORY_ERROR;
    }
    c->array = new_array;
    c->capacity = new_capacity;
    return STATUS_OK;
}

StatusCode collection_load_from_file(Student_collection* c, const char* filepath) {
    if (c == NULL || filepath == NULL) {
        return INVALID_INPUT;
    }
    FILE* f = fopen(filepath, "r");
    if (f == NULL) {
        return OPEN_ERROR;
    }
    collection_free(c);
    StatusCode st = STATUS_OK;
    char line_buffer[256];

    while (fgets(line_buffer, sizeof(line_buffer), f) != NULL) {
        unsigned int id;
        char name[MAX_STR_LEN], surname[MAX_STR_LEN], group[MAX_STR_LEN];
        unsigned int grades_tmp[EXAM_COUNT];
        unsigned char grades_char[EXAM_COUNT];

        int parsed_items = sscanf(line_buffer, "%u %s %s %s %u %u %u %u %u",
                                  &id, name, surname, group,
                                  &grades_tmp[0], &grades_tmp[1], &grades_tmp[2], &grades_tmp[3], &grades_tmp[4]);
        if (parsed_items != 9) {
            st = READ_ERROR;
            return st;
        }
        bool grade_error = false;
        for (int i = 0; i < EXAM_COUNT; i++) {
            if (grades_tmp[i] > 256) {
                grade_error = true;
                break;
            }
            grades_char[i] = (unsigned char)grades_tmp[i];
        }
        if (grade_error) {
            st = READ_ERROR;
            return st;
        }
        if (c->count == c->capacity) {
            if (collection_resize(c) != STATUS_OK) {
                st = MEMORY_ERROR;
                break;
            }
        }
        StatusCode student_s = student_create(&c->array[c->count], id, name, surname, group, grades_char);
        if (student_s != STATUS_OK) {
            st = student_s;
            break;
        }
        c->count++;
    }
    if (fclose(f) == EOF && st == STATUS_OK) {
        st = READ_ERROR;
    } 
    if (c->count == 0 && st == STATUS_OK) {
        st = INVALID_INPUT;
    }
    return st;
}

double collection_calculate_global_avg(const Student_collection* c) {
    if (c == NULL || c->count == 0) {
        return 0.0;
    }
    double total_sum = 0.0;
    for (size_t i = 0; i < c->count; i++) {
        total_sum += student_calculate_avg_grade(&c->array[i]);
    }
    return total_sum / c->count;
}

const Student* search_by_id(const Student_collection* c, unsigned int id, StatusCode* st) {
    if (c == NULL) {
        *st = INVALID_INPUT;
        return NULL;
    }
    if (c->count == 0) {
        *st = INVALID_INPUT;
        return NULL;
    }
    for (size_t i = 0; i < c->count; i++) {
        if (c->array[i].id == id) {
            *st = STATUS_OK;
            return &c->array[i];
        }
    }
    *st = INVALID_INPUT;
    return NULL;
}

StatusCode search_by_string(const Student_collection* c, const char* search_key, int field_type, const Student*** results, size_t* result_count) {
    if (c == NULL || search_key == NULL || results == NULL || result_count == NULL) {
        return INVALID_INPUT;
    }
    if (c->count == 0) {
        return INVALID_INPUT;
    }
    const Student** temp_results = (const Student** )malloc(c->count * sizeof(Student*));
    if (temp_results == NULL) {
        return MEMORY_ERROR;
    }
    *result_count = 0;
    for (size_t i = 0; i < c->count; i++) {
        const char* field_to_compare = NULL;
        switch (field_type) {
            case Field_Surname:
                field_to_compare = c->array[i].surname;
                break;
            case Field_Name:
                field_to_compare = c->array[i].name;
                break;
            case Field_Group:
                field_to_compare = c->array[i].group;
                break;
            default:
                free(temp_results);
                return INVALID_INPUT;
        }
        if (strcmp(field_to_compare, search_key) == 0) {
            temp_results[*result_count] = &c->array[i];
            (*result_count)++;
        }
    }
    if (*result_count > 0) {
        const Student** final_results = (const Student**)realloc(temp_results, (*result_count) * sizeof(Student*));
        if (final_results == NULL) {
            free(temp_results);
            return MEMORY_ERROR;
        }
        *results = final_results; 
        return STATUS_OK;
    } else {
        free(temp_results);
        *results = NULL;
        return INVALID_INPUT;
    }
}

int compare_by_id(const void *a, const void *b) {
    const Student *sa = (const Student *)a;
    const Student *sb = (const Student *)b;
    
    if (sa->id < sb->id) {
        return -1;
    }
    if (sa->id > sb->id) {
        return 1; 
    }
    return 0;
}

int compare_by_surname(const void *a, const void *b) {
    const Student *sa = (const Student *)a;
    const Student *sb = (const Student *)b;
    return strcmp(sa->surname, sb->surname);
}

int compare_by_name(const void *a, const void *b) {
    const Student *sa = (const Student *)a;
    const Student *sb = (const Student *)b;
    return strcmp(sa->name, sb->name);
}

int compare_by_group(const void *a, const void *b) {
    const Student *sa = (const Student *)a;
    const Student *sb = (const Student *)b;
    return strcmp(sa->group, sb->group);
}

void sort_collection(Student_collection* c, int (*comparator)(const void *, const void *)) {
    if (c == NULL || c->count <= 1 || comparator == NULL) {
        return;
    }
    qsort(c->array, c->count, sizeof(Student), comparator);
}

StatusCode report_student_data(const Student* s, const char* filepath) {
    if (s == NULL || filepath == NULL) {
        return INVALID_INPUT;
    }
    FILE *f = fopen(filepath, "a");
    if (f == NULL) {
        return MEMORY_ERROR;
    }
    
    double avg_grade = student_calculate_avg_grade(s);
    
    fprintf(f, "--- Студент найден по ID (%u) ---\n", s->id);
    fprintf(f, "ФИО: %s %s\n", s->surname, s->name);
    fprintf(f, "Группа: %s\n", s->group);
    fprintf(f, "Средняя оценка: %.2f\n", avg_grade);
    
    if (fclose(f) == EOF) {
        return WRITE_ERROR;
    }
    
    return STATUS_OK;
}

StatusCode report_above_avg_students(const Student_collection* c, double global_avg, const char* filepath) {
    if (c == NULL || filepath == NULL) {
        return INVALID_INPUT;
    }
    if (c->count == 0) {
        return INVALID_INPUT;
    }

    FILE* f = fopen(filepath, "a");
    if (f == NULL) {
        return MEMORY_ERROR;
    }
    
    fprintf(f, "\n--- Студенты со средним баллом выше %.2f (средний по коллекции) ---\n", global_avg);
    
    size_t count = 0;
    for (size_t i = 0; i < c->count; ++i) {
        double student_avg = student_calculate_avg_grade(&c->array[i]);
        if (student_avg > global_avg) {
            fprintf(f, "  %s %s (Балл: %.2f)\n", c->array[i].surname, c->array[i].name, student_avg);
            count++;
        }
    }
    
    if (count == 0) {
        fprintf(f, "  Нет студентов с баллом выше среднего.\n");
    }

    if (fclose(f) == EOF) {
        return WRITE_ERROR;
    }

    return STATUS_OK;
}

StatusCode get_unsigned_int(const char* prompt, unsigned int* value) {
    char buffer[MAX_INPUT_BUFFER];
    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return READ_ERROR;
    }
    
    if (sscanf(buffer, "%u", value) != 1) {
        return INVALID_INPUT;
    }
    
    return STATUS_OK;
}

StatusCode get_string(const char* prompt, char* buffer, size_t max_len) {
    printf("%s", prompt);
    if (fgets(buffer, max_len, stdin) == NULL) {
        return READ_ERROR;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == max_len - 1) {
        return INVALID_INPUT;
    }
    
    if (buffer[0] == '\0') {
        return INVALID_INPUT;
    }
    
    return STATUS_OK;
}


void handle_search(const Student_collection* c, const char* report_filepath) {
    int choice;
    unsigned int search_id;
    char search_str[MAX_STR_LEN];
    StatusCode s = STATUS_OK;

    printf("\n--- Поиск студентов ---\n");
    printf("1. По ID\n2. По Фамилии\n3. По Имени\n4. По Группе\nВведите выбор: ");
    if (scanf("%d", &choice) != 1) {
        printf("Неверный ввод.\n"); 
        while (getchar() != '\n'); 
        return;
    }
    while (getchar() != '\n');

    if (choice == 1) {
        s = get_unsigned_int("Введите ID: ", &search_id);
        if (s != STATUS_OK) {
            print_status(s);
            return; 
        }
        
        const Student* result = search_by_id(c, search_id, &s);
        
        if (s == STATUS_OK) {
            printf("Найдено: %s %s, Группа: %s, Средний балл: %.2f\n", result->surname, result->name, result->group, student_calculate_avg_grade(result));
            s = report_student_data(result, report_filepath);
            if (s != STATUS_OK) {
                print_status(s);
            }
        } else {
            print_status(s);
        }
        
    } else if (choice >= 2 && choice <= 4) {
        s = get_string("Введите ключ для поиска: ", search_str, MAX_STR_LEN);
        if (s != STATUS_OK) {
            print_status(s);
            return;
        }

        const Student** results = NULL;
        size_t result_count = 0;
        int field_type = choice - 2;

        s = search_by_string(c, search_str, field_type, &results, &result_count);
        
        if (s == STATUS_OK) {
            printf("Найдено %zu студентов:\n", result_count);
            for (size_t i = 0; i < result_count; ++i) {
                 printf("  ID: %u, ФИО: %s %s, Группа: %s\n", results[i]->id, results[i]->surname, results[i]->name, results[i]->group);
            }
        } else {
            print_status(s);
        }
        if (results) free(results);
    } else {
        printf("Неверный выбор.\n");
    }
}

void handle_sort(Student_collection *c) {
    int choice;
    int (*comparator)(const void *, const void *) = NULL;

    printf("\n--- Сортировка студентов ---\n");
    printf("1. По ID\n2. По Фамилии\n3. По Имени\n4. По Группе\nВведите выбор: ");
    if (scanf("%d", &choice) != 1) {
        printf("Неверный ввод.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    switch (choice) {
        case 1: comparator = compare_by_id; break;
        case 2: comparator = compare_by_surname; break;
        case 3: comparator = compare_by_name; break;
        case 4: comparator = compare_by_group; break;
        default: printf("Неверный выбор.\n"); return;
    }

    sort_collection(c, comparator);
    printf("Коллекция успешно отсортирована.\n");
}

void handle_report_avg(const Student_collection *c, const char *report_filepath) {
    StatusCode s = STATUS_OK;
    if (c->count == 0) {
        s = INVALID_INPUT;
        print_status(s);
        return;
    }
    
    double global_avg = collection_calculate_global_avg(c);
    printf("Средний балл по всей коллекции: %.2f\n", global_avg);
    
    s = report_above_avg_students(c, global_avg, report_filepath);
    if (s == STATUS_OK) {
        printf("Список студентов с баллом выше среднего записан в трассировочный файл: %s\n", report_filepath);
    } else {
        print_status(s);
    }
}






