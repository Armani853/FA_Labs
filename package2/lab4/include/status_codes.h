#ifndef STATUS_CODES_H
#define STATUS_CODES_H

typedef enum {
    STATUS_OK = 0,
    OVERSCANF_EOF,
    INVALID_INPUT = 1,
    MEMORY_ERROR = 2,
    NO_MATCH = 3
} overscanf_status;

#endif