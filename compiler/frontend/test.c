#include <stdio.h>
#include "tokeniser.h"

int main() {

    printf("Starting frontend to scanner file.\n");
    char *filename = "test.txt";

    // load the file into memory
    load_source(filename);

    // loop 
    while(1)
    {
        char next = peek(1);
        char ch = advance();
        if (ch == EOF_CHAR)
        {
            printf("End of file.\n");
            return 0;
        }
        else
        {
            printf("line: %d, col: %d: char -> %c ", line, column, ch);
            printf("\t next: %c \n", next);    
        }
    }

    return 0;
}
