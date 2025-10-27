#include <stdio.h>
#include "../include/functions.h"

void print_menu() {
    printf("\n--- МЕНЮ ---\n");
    printf("1. Поиск студента\n");
    printf("2. Сортировка коллекции\n");
    printf("3. Вывести в отчет студентов с баллом выше среднего\n");
    printf("4. Вывести текущую коллекцию (для проверки)\n");
    printf("0. Выход\n");
    printf("Введите выбор: ");
}

void print_collection(const Student_collection* c){
    if (c->count == 0) {
        print_status(INVALID_INPUT);
        return;
    }
    printf("\n--- Текущая коллекция студентов (%zu) ---\n", c->count);
    for (size_t i = 0; i < c->count; i++) {
        printf("[%zu] ID: %u, ФИО: %s %s, Группа: %s, Ср. балл: %.2f\n",
               i, c->array[i].id, c->array[i].surname, c->array[i].name, c->array[i].group, student_calculate_avg_grade(&c->array[i]));
    }
}

void create_test_file(const char* filepath) {
    FILE* f = fopen(filepath, "w");
    if (f == NULL) {
        print_status(OPEN_ERROR);
        return;
    }

    fprintf(f, "100 Alice Smith G1 100 90 80 70 60\n"); 
    fprintf(f, "101 Bob Johnson G2 90 85 80 75 70\n"); 
    fprintf(f, "102 Charlie Brown G1 70 60 50 40 30\n"); 
    fprintf(f, "103 David Lee G3 100 100 100 100 100\n"); 
    fprintf(f, "104 Eve Davis G2 10 20 30 40 50\n");
    fprintf(f, "105 Frank Miller G3 10 20 30 40 50\n");
    fclose(f);
}

int main(int argc, char* argv[]) {
    Student_collection students;
    collection_init(&students);
    StatusCode s = STATUS_OK;
    int choice;
    if (argc != 3) {
        s = INVALID_INPUT;
        print_status(s);
        return s;        
    }

    const char* student_filepath = argv[1];
    const char* report_filepath = argv[2];

    create_test_file(student_filepath);

    s = collection_load_from_file(&students, student_filepath);
    if (s != STATUS_OK && s != INVALID_INPUT) {
        print_status(s);
        collection_free(&students);
        return s;
    }
    printf("Файл '%s' загружен. Найдено %zu корректных записей.\n", student_filepath, students.count);
    FILE* f_report = fopen(report_filepath, "w");
    if (f_report != NULL) {
        fprintf(f_report, "--- НАЧАЛО ТРАССИРОВКИ ---\n");
        fclose(f_report);
    }

    do {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            choice = -1;
        }
        while (getchar() != '\n');

        switch(choice) {
            case 0:
                printf("Завершение работы.\n");
                break;
            case 1:
                handle_search(&students, report_filepath);
                break;
            case 2:
                handle_sort(&students);
                break;
            case 3:
                handle_report_avg(&students, report_filepath);
                break;
            case 4:
                print_collection(&students);
                break;
            
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
                break;
        }
    } while (choice != 0);
    
    collection_free(&students);
    return 0;
}