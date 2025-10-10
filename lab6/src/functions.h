#include "status_codes.h"

double integral_a(double x);
double integral_b(double x);
double integral_c(double x);
double integral_d(double x);

StatusCode calculate_integral(double (*func)(double), double a, double b, double epsilon, double* result, int* iterations);

StatusCode validate_arguments(int argc, char* argv[], double* epsilon);

void print_error(StatusCode status);

StatusCode calc(double (*func)(double), double a, double b, double epsilon, double* result, int* iterations);


