#include <stdio.h>
#include "lexer.h"

int main() {
    printf("Starting frontend to scanner file.\n");

    // char *filename = "test.txt";
    char *filename = "test.txt";

    load_source(filename);
    if (source_buffer == NULL || *source_buffer == '\0') {
        printf("Error: Source buffer is empty or not loaded properly.\n");
        return -1;
    }

    tokeniser();

    return 0;
}

