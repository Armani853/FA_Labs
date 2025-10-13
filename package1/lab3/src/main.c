#include <stdio.h>
#include <string.h>
#include "functions.h"
#include <stdlib.h>
#include "status_codes.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return WRONG_NUMBER_OF_ARGUMENTS;
    }
    char flag = argv[1][1];
    char first_char = argv[1][0];
    if (argv[1][2] != '\0') {
        return INVALID_INPUT;
    }
    if (!(first_char == '-') && !(first_char == '/')) {
        print_error(INVALID_INPUT);
        return INVALID_INPUT;
    }

    if (!(flag == 'q') && !(flag == 'm') && !(flag == 't')) {
        print_error(INVALID_INPUT);
        return INVALID_INPUT;
    }

    if (flag == 'q') {
        StatusCode q_status = handle_flag_q(argc, argv);
        return q_status;
    } else if (flag == 'm') {
        if (argc != 4) {
            print_error(WRONG_NUMBER_OF_ARGUMENTS);
            return WRONG_NUMBER_OF_ARGUMENTS;
        }
        long m, n;
        StatusCode status;
        bool is_mul;
        if ((status = str_to_int(argv[2], &m)) != STATUS_OK || (status = str_to_int(argv[3], &n)) != STATUS_OK) {
            print_error(status);
            return status;
        }
        if (n == 0) {
            print_error(DIVISION_BY_ZERO);
            return DIVISION_BY_ZERO;
        }
        if ((status = check_mul(m, n, &is_mul)) != STATUS_OK) {
            print_error(status);
            return status;
        }
        if (is_mul) {
            printf("Флаг -m: %ld кратно %ld\n", m, n);
        } else {
            printf("Флаг -m: %ld не кратно %ld\n", m, n);
        }
    } else if (flag == 't') {
        if (argc != 6) {
            print_error(WRONG_NUMBER_OF_ARGUMENTS);
            return WRONG_NUMBER_OF_ARGUMENTS;
        }
        double epsilon, s[3];
        StatusCode status;
        bool is_right;
        if ((status = str_to_double(argv[2],&epsilon)) != STATUS_OK) {
            print_error(status);
            return status;
        }
        if (epsilon <= 0) {
            print_error(INVALID_INPUT);
            return INVALID_INPUT;
        }
        for (int i = 0; i < 3; i++) {
            if ((status = str_to_double(argv[3 + i], &s[i])) != STATUS_OK) {
                print_error(status); 
                return status;
            }
            if (s[i] <= 0) {
                print_error(INVALID_INPUT);
                return INVALID_INPUT;
            }
        }
        if ((status = check_right_triangle(s[0], s[1], s[2], epsilon, &is_right)) != STATUS_OK) {
            print_error(status);
            return status;
        }

        printf("Флаг -t: Стороны %.4f, %.4f, %.4f %s могут быть сторонами прямоугольного треугольника (эпсилон=%.2e)\n", 
               s[0], s[1], s[2], is_right ? "" : "не", epsilon);
        return STATUS_OK;
        
    } else {
        print_error(INVALID_INPUT);
        return INVALID_INPUT;
    }
    return STATUS_OK;

}
