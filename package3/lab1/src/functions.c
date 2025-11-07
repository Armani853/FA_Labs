#include "../include/functions.h"

StatusCode convert_to_r_base(unsigned int number, const int r, char* res) {
    if (r > 5 || r < 1 || res == NULL) {
        return INVALID_INPUT;
    }
    char* start = res;
    char dig[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
    unsigned int mask = ~(~0 << r);  
    
    if (number == 0) {
        res[0] = '0';
        res[1] = '\0';
        return STATUS_OK; 
    }

    while (number != 0) {
        char symb = dig[number & mask];
        *res = symb;
        res++;
        number = number >> r;
    }
    *res = '\0';
    
    char* lt = start;
    char* rt = res - 1;
    while (lt < rt) {
        char sw = *lt;
        *lt = *rt;
        *rt = sw;
        lt++;
        rt--;
    }
    
    return STATUS_OK;
}


StatusCode get_input(unsigned int* number, int* r) {
    if (number == NULL || r == NULL) {
        return INVALID_INPUT;
    }

    printf("Введите число: ");
    if (scanf("%u", number) != 1) {
        return INVALID_INPUT;
    }

    printf("Введите степень двойки (от 1 до 5): ");
    if (scanf("%d", r) != 1) {
        while (getchar() != '\n');
        return INVALID_INPUT;
    }
    
    if (*r > 5 || *r < 1) {
        printf("Степень двойки может быть только от 1 до 5.\n");
        while (getchar() != '\n');
        return INVALID_INPUT;
    }
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    
    return STATUS_OK;
}

StatusCode print_status(StatusCode st) {

    switch (st) {
        case STATUS_OK:
            printf("Успешно");
            break;
        case INVALID_INPUT:
            printf("Неверный ввод");
            break;
        case MEMORY_ERROR:
            printf("Ошибка с памятью");
            break;
        default:
            printf("Неизвестная ошибка");
    }
}