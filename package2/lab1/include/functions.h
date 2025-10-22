#include "status_codes.h"
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>
#define EPS 1.0e-15
#define IS_ZERO(val, eps) (fabs(val) < (eps))
#define IS_EQUAL(fval, sval, eps) (fabs((fval) - (sval)) < (eps))
#define IS_MORE(fval, sval, eps) (((fval) - (sval)) > (eps))
#define IS_LESS(fval, sval, eps) (((sval) - (fval)) > (eps))
#define IS_MORE_OR_EQUAL(fval, sval, eps) (((fval) - (sval)) > -(eps))
#define IS_LESS_OR_EQUAL(fval, sval, eps) (((sval) - (fval)) > -(eps))

void print_status(StatusCode s);

void print_res(const int base, const double epsilon, const int num_fractions, const double fractions[], const bool results[]);

StatusCode validate_base(const int base);

StatusCode check_finite(const int base, const double epsilon, bool* result_buffer, const int num_fractions, ...);

StatusCode validate_fraction(const double fraction, const double epsilon);

int gcd(long long num, long long denom);

StatusCode is_finite(const int base, long long num, long long denom, bool* res);




