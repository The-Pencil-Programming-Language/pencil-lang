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
    
    init_global_token_array();
    lexer();
    
    // Just show the essential info
    print_tokens_filtered_global();  // Clean token list
    print_tokens_as_source_global();  // Clean token list
    print_token_stats_global();      // Quick statistics
    // free_tokens();
    free_token_array(global_token_array);
    return 0;
}

