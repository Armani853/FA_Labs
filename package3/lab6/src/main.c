#include "../include/functions.h"


const char* st_to_str(int code) {
    if (code == NOT_BALANCED) {
        return "Не сбалансировано";
    } 
    if (code == BALANCED) {
        return "Сбалансировано";
    }
}

int main() {
    printf("Введите строку для проверки скобок: \n");
    char line[256];
    if (fgets(line, sizeof(line), stdin) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        int res_code = check_brackets(&line[0]);
        printf("Строка: %s \n", line);
        printf("Результат: %s \n", st_to_str(res_code));
    } else {
        printf("Ошибка при чтении ввода\n");
        return 1;
    }
    return 0;

}