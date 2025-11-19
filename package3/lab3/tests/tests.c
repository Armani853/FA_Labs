#include "../include/functions.h"
#include <assert.h>

void test_liver_validate(void) {
    Liver l;
    l.id = 1;
    strcpy(l.surname, "Ivanov");
    strcpy(l.first_name, "Ivan");
    strcpy(l.second_name, "Ivanovich");
    l.dob = (Date){1, 1, 1990};
    l.gender = 'M';
    l.avg_income = 1000.0;
    
    assert(liver_validate(&l) == STATUS_OK);

    l.dob = (Date){30, 2, 2000}; 
    assert(liver_validate(&l) == INVALID_INPUT);

    l.dob = (Date){1, 1, 2030};
    assert(liver_validate(&l) == INVALID_INPUT);

    l.dob = (Date){1, 1, 1990};
    strcpy(l.surname, "123"); 
    assert(liver_validate(&l) == INVALID_INPUT);

    strcpy(l.surname, "Ivanov");
    l.gender = 'X';
    assert(liver_validate(&l) == INVALID_INPUT);

    printf("Test: liver_validate OK\n");
}

void test_list_base_ops(void) {
    LinkedList *list = create_list();
    assert(list != NULL);
    assert(list->size == 0);
    
    Liver l1 = {.id = 1, .dob = {1, 1, 2000}};
    Liver l2 = {.id = 2, .dob = {1, 1, 1990}};
    Liver temp;

    assert(push_front_list(list, &l1) == STATUS_OK);
    assert(list->size == 1);
    
    assert(push_back_list(list, &l2) == STATUS_OK);
    assert(list->size == 2);
    
    assert(pop_front_list(list, &temp) == STATUS_OK);
    assert(temp.id == 1);
    assert(list->size == 1);
    
    assert(pop_back_list(list, &temp) == STATUS_OK);
    assert(temp.id == 2);
    assert(list->size == 0);

    delete_list(list);
    printf("Test: list_base_ops OK\n");
}

void test_insert_ordered_and_age_compare(void) {
    LinkedList *list = create_list();
    
    Liver l1 = {.id = 10, .dob = {1, 1, 1980}}; 
    Liver l2 = {.id = 20, .dob = {1, 1, 2000}}; 
    Liver l3 = {.id = 30, .dob = {1, 1, 1990}}; 
    
    assert(insert_ordered_liver(list, &l1) == STATUS_OK); 
    assert(insert_ordered_liver(list, &l2) == STATUS_OK);
    assert(insert_ordered_liver(list, &l3) == STATUS_OK);
    
    assert(list->size == 3); 
    
    assert(list->head->data.id == 20); 
    assert(list->head->next->data.id == 30);
    assert(list->tail->data.id == 10);
    
    delete_list(list);
    printf("Test: insert_ordered_and_age_compare OK\n");
}

int main(void) {
    printf("--- Starting Quick Assert Tests ---\n");
    
    test_liver_validate();
    test_list_base_ops();
    test_insert_ordered_and_age_compare();    
    printf("All Assert Tests Passed Successfully!\n");
    return 0;
}