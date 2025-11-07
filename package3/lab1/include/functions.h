#include "status_codes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 35


StatusCode convert_to_r_base(unsigned int number, int r, char* res);

StatusCode get_input(unsigned int* number, int* r);

StatusCode print_status(StatusCode st);

