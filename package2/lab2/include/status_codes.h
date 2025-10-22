#ifndef STATUS_CODES_H
#define STATUS_CODES_H

typedef enum {
    STATUS_OK = 0,
    NULL_ERROR = 1,
    NOT_FOUND_ERROR = 2,
    INVALID_ERRNUM = 3,
    OUT_OF_RANGE_ERROR = 4
} StatusCode;

#endif