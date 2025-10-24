#include "../include/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define LINE_WIDTH 80 
#define PATH_MAX_LEN 256
#define MAX_LINE_BUFFER 1024


void run_simple_justification_test() {
    const char* input_content = 
        "This text is designed to perfectly fill exactly two whole lines using the strict justification algorithm and ensure that every single part of the code works correctly to reach the eighty character width target. Last words.";
    
    const char* input_filename = "assert_test_input.txt";
    const char* output_filename = "assert_test_output.txt";
    
    FILE* fin = fopen(input_filename, "w+");
    assert(fin != NULL);
    fprintf(fin, "%s", input_content);
    fclose(fin); 
    fin = fopen(input_filename, "r");
    FILE* fout = fopen(output_filename, "w+");
    assert(fin != NULL && fout != NULL);

    StatusCode result = process_file(fin, fout);
    assert(result == STATUS_OK);
    
    fclose(fin);
    rewind(fout); 
    
    char output_line[LINE_WIDTH + 2]; 
    
    assert(fgets(output_line, LINE_WIDTH + 2, fout) != NULL);
    assert(strlen(output_line) == LINE_WIDTH + 1); 
    output_line[LINE_WIDTH] = '\0';
    assert(strlen(output_line) == LINE_WIDTH); 
    printf("Тест 1 (80 символов, Строка 1) успешно пройден.\n"); 

    assert(fgets(output_line, LINE_WIDTH + 2, fout) != NULL);
    assert(strlen(output_line) == LINE_WIDTH + 1);
    output_line[LINE_WIDTH] = '\0';
    assert(strlen(output_line) == LINE_WIDTH);
    printf("Тест 2 (80 символов, Строка 2) успешно пройден.\n"); 

    assert(fgets(output_line, LINE_WIDTH + 2, fout) != NULL);
    assert(strlen(output_line) < LINE_WIDTH + 1); 
    printf("Тест 3 (Последняя строка < 80 символов) успешно пройден.\n"); 
    
    assert(fgets(output_line, LINE_WIDTH + 2, fout) == NULL);
    printf("Тест 4 (Достигнут конец файла) успешно пройден.\n"); 

    fclose(fout);
    remove(input_filename);
    remove(output_filename);

    printf("\nВсе assert тесты на выравнивание (80 символов) успешно пройдены!\n");
}

int main() {
    run_simple_justification_test();
    return 0;
}