#include "../include/functions.h"
int main() {
    unsigned int num;
    int r;

    StatusCode in = get_input(&num, &r);
    if (in != STATUS_OK) {
       print_status(in);
       return 1;
    }

    char* buf = (char *)malloc(BUF_SIZE * sizeof(char));
    if (buf == NULL) {
        print_status(MEMORY_ERROR);
        return 1;
    }
    StatusCode st = convert_to_r_base(num, r, buf);
    if (st == STATUS_OK) {
        printf("%s ", buf);
    } else {
        print_status(st);
        return 1;
    }
    free(buf);
    return 0;
}