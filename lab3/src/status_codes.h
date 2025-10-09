#ifndef STATUS_CODE_H
#define STATUS_CODE_H

typedef enum {
    STATUS_OK = 0,
    INVALID_INPUT = 1,
    WRONG_NUMBER_OF_ARGUMENTS = 2,
    STATUS_ERROR = 3,
    NO_SOLUTION = 4,
    DIVISION_BY_ZERO = 5,
    OVERFLOW_ERROR = 6
} StatusCode;

#endif