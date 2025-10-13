#ifndef STATUS_CODES_H
#define STATUS_CODES_H

typedef enum {
    STATUS_OK = 0,
    INVALID_INPUT = 1,
    NOT_PRIME = 2,
    OUT_OF_RANGE = 3,
    MEMORY_ERROR = 4,
} StatusCode;

#endif