#ifndef STATUS_CODES_H
#define STATUS_CODES_H

typedef enum {
    STATUS_OK = 0,
    INVALID_INPUT = 1, 
    MEMORY_ERROR = 2,
    READ_ERROR = 3,
    WRITE_ERROR = 4,
    OPEN_ERROR = 5

} StatusCode;

#endif