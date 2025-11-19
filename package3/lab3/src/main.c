#include "../include/functions.h"

static unsigned int read_id(const char *prompt) {
    unsigned int id;
    printf("%s", prompt);
    while (scanf("%u", &id) != 1) {
        printf("Неверный ввод. ID должно быть неотрицательным целым: ");
        int c; 
        while ((c = getchar()) != '\n' && c != EOF); // Очистка буфера
    }
    return id;
}

static StatusCode read_liver_data(Liver *l, unsigned int id_to_use) {
    if (l == NULL) return INVALID_INPUT;
    
    l->id = id_to_use;

    printf("Введите фамилию (лат. буквы): ");
    if (scanf("%99s", l->surname) != 1) return INVALID_INPUT;
    printf("Введите имя (лат. буквы): ");
    if (scanf("%99s", l->first_name) != 1) return INVALID_INPUT;
    printf("Введите отчество (можно пропустить - 99s): ");
    if (scanf("%99s", l->second_name) != 1) return INVALID_INPUT;

    printf("Введите дату рождения (день месяц год, например 1 1 1990): ");
    if (scanf("%d %d %d", &l->dob.day, &l->dob.month, &l->dob.year) != 3) return INVALID_INPUT;

    printf("Введите пол (M/W): ");
    char gender_str[2];
    if (scanf("%1s", gender_str) != 1) return INVALID_INPUT;
    l->gender = gender_str[0];

    printf("Введите средний доход (вещ. число): ");
    if (scanf("%lf", &l->avg_income) != 1) return INVALID_INPUT;

    return liver_validate(l);
}


StatusCode run_program(const char *initial_file) {
    LinkedList* list = create_list();
    LinkedList* undo_stack = create_list(); 

    if (list == NULL || undo_stack == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для списка или стека.\n");
        return MEMORY_ERROR;
    }

    printf("Загрузка данных из файла '%s'...\n", initial_file);
    StatusCode s = read_data_from_file(initial_file, list);
    if (s != STATUS_OK) {
        fprintf(stderr, "Ошибка при загрузке данных: Код %d\n", s);
        delete_list(list);
        delete_list(undo_stack);
        return s;
    }
    printf("Данные успешно загружены. В списке %zu жителей.\n", list->size);

    int choice = -1;
    while (choice != 0) {
        printf("\n================ МЕНЮ ================\n");
        printf("1. Вывести список жителей (по возрасту)\n");
        printf("2. Добавить жителя\n");
        printf("3. Удалить жителя по ID\n");
        printf("4. Изменить жителя по ID\n");
        printf("5. Поиск жителя по ID\n");
        printf("6. Выгрузить данные в файл\n");
        printf("7. Отменить N/2 последних модификаций (N=%zu)\n", undo_stack->size);
        printf("0. Выход и очистка памяти\n");
        printf("Выберите действие: ");
        
        if (scanf("%d", &choice) != 1) {
            choice = -1;
            int c; while ((c = getchar()) != '\n' && c != EOF);
        }

        switch (choice) {
            case 1: {
                printf("\n--- СПИСОК ЖИТЕЛЕЙ (Размер: %zu) ---\n", list->size);
                Node *current = list->head;
                while(current != NULL) {
                    liver_print(&current->data);
                    current = current->next;
                }
                break;
            }
            
            case 2: {
                unsigned int new_id = read_id("Введите уникальный ID для нового жителя: ");
                Liver new_liver;
                
                s = read_liver_data(&new_liver, new_id);
                if (s != STATUS_OK) {
                    printf("Ошибка ввода или валидации данных.\n");
                    break;
                }
                
                s = insert_ordered_liver(list, &new_liver);
                if (s != STATUS_OK) {
                     fprintf(stderr, "Ошибка добавления жителя: Код %d\n", s);
                     return s;
                }

                Modification mod;
                mod.type = MOD_ADD;
                mod.target_id = new_id;
                
                s = push_stack(undo_stack, (LIST_TYPE*)&mod);
                if (s != STATUS_OK) {
                     fprintf(stderr, "Ошибка регистрации ADD в UndoStack: Код %d\n", s);
                     return s;
                }
                printf("Житель с ID %u успешно добавлен.\n", new_id);

                break;
            }

            case 3: {
                unsigned int id = read_id("Введите ID жителя для удаления: ");
                s = delete_liver_by_id(list, undo_stack, id);
                if (s == ERROR_NOT_FOUND) {
                    printf("Житель с ID %u не найден.\n", id);
                } else if (s != STATUS_OK) {
                     fprintf(stderr, "Ошибка при удалении жителя: Код %d\n", s);
                     break;
                } else {
                    printf("Житель с ID %u успешно удален.\n", id);
                }
                break;
            }

            case 4: {
                unsigned int id = read_id("Введите ID жителя для изменения: ");
                Liver new_data;

                printf("\n--- Ввод НОВЫХ данных для жителя ID %u ---\n", id);
                s = read_liver_data(&new_data, id);
                if (s != STATUS_OK) {
                    printf("Ошибка ввода или валидации данных.\n");
                    break;
                }

                s = update_liver_by_id(list, undo_stack, id, &new_data);
                if (s == ERROR_NOT_FOUND) {
                    printf("Житель с ID %u не найден.\n", id);
                } else if (s != STATUS_OK) {
                    fprintf(stderr, "Ошибка при изменении жителя: Код %d\n", s);
                    return s;
                } else {
                    printf("Житель с ID %u успешно изменен и пересортирован.\n", id);
                }
                break;
            }

            case 5: {
                unsigned int id = read_id("Введите ID жителя для поиска: ");
                Liver found_liver;
                s = find_liver_data_by_id(list, id, &found_liver);
                
                if (s == ERROR_NOT_FOUND) {
                    printf("Житель с ID %u не найден.\n", id);
                } else if (s != STATUS_OK) {
                     fprintf(stderr, "Ошибка при поиске: Код %d\n", s);
                     return s;
                } else {
                    printf("--- НАЙДЕН ЖИТЕЛЬ ---\n");
                    liver_print(&found_liver);
                }
                break;
            }

            case 6: {
                char out_filename[256];
                printf("Введите имя файла для выгрузки: ");
                if (scanf("%255s", out_filename) != 1) break;
                
                s = write_data_to_file(out_filename, list);
                if (s != STATUS_OK) {
                    fprintf(stderr, "Ошибка при выгрузке данных в файл: Код %d\n", s);
                    return s;
                }
                printf("Данные успешно выгружены в файл '%s'.\n", out_filename);
                break;
            }
            
            case 7: {
                s = perform_undo(list, undo_stack);
                if (s != STATUS_OK) {
                    fprintf(stderr, "Ошибка при выполнении Undo: Код %d\n", s);
                    return s;
                }
                printf("Операция Undo завершена. Текущее N=%zu.\n", undo_stack->size);
                break;
            }
            
            default:
                if (choice != 0) printf("Неверный выбор. Попробуйте снова.\n");
                break;
        }
    }

    delete_list(list); 
    delete_list(undo_stack);
    printf("Память очищена. Программа завершена.\n");
    return STATUS_OK;
}

int main() {
    
    const char *data_file = "initial_data.txt";

    StatusCode s = run_program(data_file);

    if (s != STATUS_OK) {
        fprintf(stderr, "Программа завершилась с ошибкой: %d\n", s);
        return 1;
    }

    return 0;
}