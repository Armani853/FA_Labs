#include "status_codes.h"
#include <stdbool.h>
bool is_double(const char* str);

bool is_int(const char* str);

StatusCode str_to_int(const char* str, long* result);

StatusCode quad_solve(double a, double b, double c, double epsilon, double *r1, double *r2, int *num_roots);

StatusCode str_to_double(const char* const str, double* result);

StatusCode check_mul(long long m, long long n, bool *is_multiple);

StatusCode handle_flag_q(int argc, char* argv[]);

StatusCode check_right_triangle(double s1, double s2, double s3, double epsilon, bool *is_right);

StatusCode check_mul(long long m, long long n, bool *is_multiple);

void print_error(StatusCode status);


