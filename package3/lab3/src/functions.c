#include "../include/functions.h"

Node* create_node(const LIST_TYPE* value) {
    Node* new_node = (Node* )malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    if (liver_copy(value, &new_node->data) != STATUS_OK) {
        free(new_node);
        return NULL;
    }
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}

LinkedList* create_list(void) {
    LinkedList* list = malloc(sizeof(LinkedList));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;

}


void erase_list(LinkedList *list) {
    if (list == NULL) return;
    
    Node *current = list->head;
    Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void delete_list(LinkedList *list) {
    erase_list(list);
    free(list);
}

StatusCode push_back_list(LinkedList *list, const LIST_TYPE *value) {
    if (list == NULL || value == NULL) {
        return INVALID_INPUT;
    } 
    
    Node *new_node = create_node(value);
    if (new_node == NULL) {
        return MEMORY_ERROR;
    }
    
    if (list->size == 0) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
    
    list->size++;
    return STATUS_OK;
}

StatusCode push_front_list(LinkedList *list, const LIST_TYPE *value) {
    if (list == NULL || value == NULL) {
        return INVALID_INPUT;
    }
    
    Node *new_node = create_node(value);
    if (new_node == NULL) {
        return MEMORY_ERROR;
    }

    if (list->size == 0) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
    
    list->size++;
    return STATUS_OK;
}

StatusCode pop_back_list(LinkedList *list, LIST_TYPE *result) {
    if (list == NULL || result == NULL || list->size == 0) {
        return INVALID_INPUT;
    }

    Node *tail_node = list->tail;
    
    if (liver_copy(&tail_node->data, result) != STATUS_OK) {
        return MEMORY_ERROR;
    }
    
    if (list->size == 1) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = tail_node->prev;
        list->tail->next = NULL;
    }
    
    free(tail_node);
    list->size--;
    return STATUS_OK;
}

StatusCode pop_front_list(LinkedList *list, LIST_TYPE *result) {
    if (list == NULL || result == NULL || list->size == 0) {
        return INVALID_INPUT;
    }

    Node *head_node = list->head;
    
    if (liver_copy(&(head_node->data), result) != STATUS_OK) {
        return MEMORY_ERROR;
    }
    
    if (list->size == 1) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = head_node->next;
        list->head->prev = NULL;
    }
    
    free(head_node);
    list->size--;
    return STATUS_OK;
}

Node* get_node_at(const LinkedList *list, size_t index) {
    if (list == NULL || index >= list->size) {
        return NULL;
    } 
    
    Node *current;
    
    if (index < list->size / 2) {
        current = list->head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
    } else {
        current = list->tail;
        for (size_t i = list->size - 1; i > index; --i) {
            current = current->prev;
        }
    }
    return current;
}

StatusCode insert_at_list(LinkedList *list, size_t index, const LIST_TYPE *value) {
    if (list == NULL || value == NULL || index > list->size) {
        return INVALID_INPUT;
    }
    
    if (index == 0) {
        return push_front_list(list, value);
    } 
    if (index == list->size) {
        return push_back_list(list, value);
    } 

    Node *existing_node = get_node_at(list, index);
    if (existing_node == NULL) {
        return INVALID_INPUT;
    }
    
    Node *new_node = create_node(value);
    if (new_node == NULL) {
        return MEMORY_ERROR;
    }
    
    new_node->next = existing_node;
    new_node->prev = existing_node->prev;
    
    existing_node->prev->next = new_node;
    existing_node->prev = new_node;
    
    list->size++;
    return STATUS_OK;
}

StatusCode delete_at_list(LinkedList *list, size_t index) {
    if (list == NULL || index >= list->size) {
        return INVALID_INPUT;
    }

    if (index == 0) {
        LIST_TYPE temp;
        return pop_front_list(list, &temp);
    }
    if (index == list->size - 1) {
        LIST_TYPE temp;
        return pop_back_list(list, &temp);
    }

    Node *to_delete = get_node_at(list, index);
    if (to_delete == NULL) {
        return INVALID_INPUT;
    }
    
    to_delete->prev->next = to_delete->next;
    to_delete->next->prev = to_delete->prev;
    
    free(to_delete);
    list->size--;
    return STATUS_OK;
}

StatusCode get_at_list(const LinkedList *list, size_t index, LIST_TYPE *result) {
    if (list == NULL || result == NULL || index >= list->size) {
        return INVALID_INPUT;
    }

    Node *node = get_node_at(list, index);
    if (node == NULL) {
        return INVALID_INPUT;
    }

    return liver_copy(&node->data, result);
}

StatusCode is_equal_list(const LinkedList *l1, const LinkedList *l2) {
    if (l1 == NULL || l2 == NULL || l1->size != l2->size) {
        return INVALID_INPUT;
    }
    
    Node *c1 = l1->head;
    Node *c2 = l2->head;
    
    while (c1 != NULL) {
        if (memcmp(&c1->data, &c2->data, sizeof(LIST_TYPE)) != 0) {
            return INVALID_INPUT;
        }
        c1 = c1->next;
        c2 = c2->next;
    }
    
    return STATUS_OK;
}

StatusCode push_stack(LinkedList *stack, const LIST_TYPE *value) {
    return push_back_list(stack, value);
}

StatusCode pop_stack(LinkedList *stack, LIST_TYPE *result) {
    return pop_back_list(stack, result);
}

StatusCode peek_stack(const LinkedList *stack, LIST_TYPE *result) {
    if (stack == NULL || result == NULL || stack->size == 0) {
        return INVALID_INPUT;
    }
    return liver_copy(&stack->tail->data, result);
}


StatusCode enqueue(LinkedList *queue, const LIST_TYPE *value) {
    return push_back_list(queue, value);
}

StatusCode dequeue(LinkedList *queue, LIST_TYPE *result) {
    return pop_front_list(queue, result);
}

StatusCode peek_queue(const LinkedList *queue, LIST_TYPE *result) {
    if (queue == NULL || result == NULL || queue->size == 0) {
        return INVALID_INPUT;
    }
    return liver_copy(&queue->head->data, result);
}


int is_latin_letters(const char *s) {
    for (size_t i = 0; i < strlen(s); i++) {
        if (!isalpha((unsigned char)s[i])) {
            return 0;
        }
    }
    return 1;
}

int is_valid_date(const Date *d) {
    if (d->year <= 0 || d->year > CURRENT_YEAR) {
        return 0;
    }
    if (d->month < 1 || d->month > 12) {
        return 0;
    }
    if (d->day < 1 || d->day > 31) {
        return 0;
    }
    
    if (d->month == 2) {
        int max_day = (d->year % 4 == 0 && (d->year % 100 != 0 || d->year % 400 == 0)) ? 29 : 28;
        if (d->day > max_day) {
            return 0;
        }
    } else if (d->month == 4 || d->month == 6 || d->month == 9 || d->month == 11) {
        if (d->day > 30) {
            return 0;
        }
    }
    return 1;
}

StatusCode liver_validate(const Liver *l) {
    if (l == NULL) {
        return INVALID_INPUT;
    } 
    
    if (strlen(l->surname) == 0 || !is_latin_letters(l->surname)) {
        return INVALID_INPUT;
    }
    
    if (strlen(l->first_name) == 0 || !is_latin_letters(l->first_name)) {
        return INVALID_INPUT;
    }
    
    if (!is_latin_letters(l->second_name)) {
        return INVALID_INPUT;
    }

    if (!is_valid_date(&l->dob)) {
        return INVALID_INPUT;
    }
    
    if (l->gender != 'M' && l->gender != 'W') {
        return INVALID_INPUT;
    }
    
    if (l->avg_income < 0.0) {
        return INVALID_INPUT;
    }

    return STATUS_OK;
}

StatusCode liver_copy(const Liver *src, Liver *dest) {
    if (src == NULL || dest == NULL) {
        return INVALID_INPUT;
    }
    memcpy(dest, src, sizeof(Liver));
    return STATUS_OK;
}

int liver_get_age(const Date *dob) {
    return CURRENT_YEAR - dob->year;
}

int liver_compare_age(const Liver *l1, const Liver *l2) {
    int age1 = liver_get_age(&l1->dob);
    int age2 = liver_get_age(&l2->dob);
    
    if (age1 > age2) {
        return 1;
    }
    if (age1 < age2) {
        return -1;
    }
    
    if (l1->id < l2->id) {
        return -1;
    }
    if (l1->id > l2->id) {
        return 1;
    }
    return 0;
}

void liver_print(const Liver *l) {
    if (l == NULL) {
        printf("[NULL Liver]\n");
        return;
    }
    printf("ID: %u, ФИО: %s %s %s, Дата: %d.%d.%d, Пол: %c, Доход: %.2f\n", 
           l->id, l->surname, l->first_name, l->second_name, 
           l->dob.day, l->dob.month, l->dob.year, 
           l->gender, l->avg_income);
}


StatusCode read_data_from_file(const char *filename, LinkedList *list) {
    if (filename == NULL || list == NULL) {
        return INVALID_INPUT;
    }

    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        return OPEN_ERROR;
    }

    StatusCode final_status = STATUS_OK;
    Liver temp_liver;
    
    while (fscanf(f, "%u %s %s %s %d %d %d %c %lf", 
                  &temp_liver.id, 
                  temp_liver.surname, 
                  temp_liver.first_name, 
                  temp_liver.second_name, 
                  &temp_liver.dob.day, 
                  &temp_liver.dob.month, 
                  &temp_liver.dob.year, 
                  &temp_liver.gender, 
                  &temp_liver.avg_income) == 9) 
    {
        if (liver_validate(&temp_liver) != STATUS_OK) {
            fprintf(stderr, "Ошибка валидации данных для ID: %u. Пропускаем.\n", temp_liver.id);
            continue;
        }

        StatusCode s = insert_ordered_liver(list, &temp_liver);
        if (s != STATUS_OK) {
            final_status = s; 
            break;
        }
    }

    if (ferror(f)) final_status = READ_ERROR;

    fclose(f);
    return final_status;
}

StatusCode write_data_to_file(const char *filename, const LinkedList *list) {
    if (filename == NULL || list == NULL) {
        return INVALID_INPUT;
    }

    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        return OPEN_ERROR;
    } 

    StatusCode final_status = STATUS_OK;
    Node *current = list->head;
    
    while (current != NULL) {
        const Liver *l = &current->data;
        int count = fprintf(f, "%u %s %s %s %d %d %d %c %.2f\n", 
                            l->id, l->surname, l->first_name, l->second_name, 
                            l->dob.day, l->dob.month, l->dob.year, 
                            l->gender, l->avg_income);
        
        if (count < 0) {
            final_status = WRITE_ERROR;
            break;
        }
        current = current->next;
    }

    fclose(f);
    return final_status;
}

StatusCode insert_ordered_liver(LinkedList *list, const Liver *new_liver) {
    if (list == NULL || new_liver == NULL) {
        return INVALID_INPUT;
    }
    
    if (list->size == 0) {
        return push_front_list(list, new_liver);
    }

    Node *current = list->head;
    size_t index = 0;

    while (current != NULL) {
        if (liver_compare_age(new_liver, &current->data) <= 0) {
            return insert_at_list(list, index, new_liver);
        }
        current = current->next;
        index++;
    }
    
    return push_back_list(list, new_liver);
}

StatusCode find_liver_data_by_id(const LinkedList *list, unsigned int id, Liver *result) {
    if (list == NULL || result == NULL) return INVALID_INPUT;
    Node *current = list->head;
    while (current != NULL) {
        if (current->data.id == id) {
            return liver_copy(&current->data, result);
        }
        current = current->next;
    }
    return ERROR_NOT_FOUND;
}

Node* find_node_by_id(LinkedList *list, unsigned int id, size_t *index) {
    Node *current = list->head;
    size_t i = 0;
    while (current != NULL) {
        if (current->data.id == id) {
            if (index != NULL) *index = i;
            return current;
        }
        current = current->next;
        i++;
    }
    return NULL;
}

StatusCode update_liver_by_id(LinkedList *list, UndoStack *undo, unsigned int id, const Liver *new_data) {
    if (list == NULL || undo == NULL || new_data == NULL) {
        return INVALID_INPUT;
    }
    if (liver_validate(new_data) != STATUS_OK) {
        return INVALID_INPUT;
    }
    
    size_t index;
    Node *target_node = find_node_by_id(list, id, &index);

    if (target_node == NULL) return ERROR_NOT_FOUND;

    Modification mod;
    mod.type = MOD_UPDATE;
    mod.target_id = id;
    mod.target_index = index;

    if (liver_copy(&target_node->data, &mod.old_data) != STATUS_OK) return MEMORY_ERROR;


    StatusCode s = delete_at_list(list, index); 
    if (s != STATUS_OK) {
        return s;
    }

    s = insert_ordered_liver(list, new_data);
    if (s != STATUS_OK) {
        return s; 
    }

    return push_stack(undo, (LIST_TYPE*)&mod);
}


StatusCode delete_liver_by_id(LinkedList *list, UndoStack *undo, unsigned int id) {
    if (list == NULL || undo == NULL) {
        return INVALID_INPUT;
    }
    
    size_t index;
    Node *target_node = find_node_by_id(list, id, &index);

    if (target_node == NULL) return ERROR_NOT_FOUND;

    Modification mod;
    mod.type = MOD_DELETE;
    mod.target_id = id;
    mod.target_index = index;
    if (liver_copy(&target_node->data, &mod.old_data) != STATUS_OK) {
        return MEMORY_ERROR;
    }

    StatusCode s = delete_at_list(list, index);
    if (s != STATUS_OK) {
        return s;
    }

    return push_stack(undo, (LIST_TYPE*)&mod);
}


StatusCode perform_undo(LinkedList *list, UndoStack *undo) {
    if (list == NULL || undo == NULL) {
        return INVALID_INPUT;
    }

    size_t N = undo->size;
    size_t num_undo = N / 2;
    
    if (num_undo == 0) {
        printf("Нет доступных модификаций для отмены (N/2 = 0).\n");
        return STATUS_OK;
    }

    printf("Отмена последних %zu модификаций...\n", num_undo);

    for (size_t i = 0; i < num_undo; ++i) {
        Modification mod;
        
        StatusCode s = pop_stack(undo, (LIST_TYPE*)&mod);
        if (s != STATUS_OK) {
            return s;
        }

        switch (mod.type) {
            case MOD_ADD: {
                printf("  -> Отмена ADD (ID: %u). Удаление из списка.\n", mod.target_id);
                StatusCode del_s = delete_liver_by_id(list, NULL, mod.target_id);
                if (del_s != STATUS_OK && del_s != ERROR_NOT_FOUND) {
                    return del_s;
                }
                break;
            }
            case MOD_DELETE: {
                printf("  -> Отмена DELETE (ID: %u). Восстановление в список.\n", mod.target_id);
                StatusCode ins_s = insert_ordered_liver(list, &mod.old_data); 
                if (ins_s != STATUS_OK) {
                    return ins_s;
                }
                break;
            }
            case MOD_UPDATE: {
                printf("  -> Отмена UPDATE (ID: %u). Восстановление старых данных.\n", mod.target_id);
                
                StatusCode del_s = delete_liver_by_id(list, NULL, mod.target_id);
                if (del_s != STATUS_OK && del_s != ERROR_NOT_FOUND) return del_s;
                
                StatusCode ins_s = insert_ordered_liver(list, &mod.old_data);
                if (ins_s != STATUS_OK) {
                    return ins_s;
                }

                break;
            }
        }
    }

    return STATUS_OK;
}