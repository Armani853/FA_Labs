#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(int argc, char* argv[]) {
    double epsilon;
    StatusCode status;
    status = validate_arguments(argc, argv, &epsilon);
    if (status != STATUS_OK) {
        print_error(status);
        return status;
    }

    printf("Вычисление интегралов с точностью ε = %g\n\n", epsilon);
    
    double (*functions[]) (double) = {integral_a, integral_b, integral_c, integral_d};
    const char* names[] = {
        "∫₀¹ ln((1+x)/x) dx",
        "∫₀¹ e^(-x²/2) dx", 
        "∫₀¹ ln(1/(1-x)) dx",
        "∫₀¹ x^x dx"
    };
    const size_t num_integrals = sizeof(functions) / sizeof(functions[0]);
    
    for (size_t i = 0; i < num_integrals; i++) {
        double result;
        int iterations;

        status = calc(functions[i], 0.0, 1.0, epsilon, &result, &iterations);
        if (status == STATUS_OK) {
            printf("%s = %.10f\n", names[i], result);
            printf("  Итераций: %zu, Точность: %g\n\n", iterations, epsilon);
        } else {
            printf("%s - ", names[i]);
            print_error(status);
            printf("\n");
        }
    }
    return STATUS_OK;
}