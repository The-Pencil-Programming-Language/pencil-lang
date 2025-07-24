#include <stdio.h>
#include "lexer.h"
#include "token.h"

int main() 
{
    printf("Starting frontend to scanner file.\n");

    char *filename = "hello.txt";

    printf("Loading source file....\n");
    load_source(filename);
    
    if (source_buffer == NULL || *source_buffer == '\0') {
        printf("Error: Source buffer is empty or not loaded properly.\n");
        return -1;
    }
    
    lexer();
    print_token();
    free_tokens();

    return 0;
}

