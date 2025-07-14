#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "char.h"


#define LOOKAHEAD 8

char *source_buffer = NULL;
char *current_input_char = NULL; 
char *next_input_char;
char *peekptr;

int line = 1;
int column = 1;


void load_source(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("error opening file: %s\n", filename);
        return;
    }
        
    /* Peek first three bytes for BOM */
    int b1 = fgetc(file), b2 = fgetc(file), b3 = fgetc(file);
    if (!(b1 == 0xEF && b2 == 0xBB && b3 == 0xBF)) {
        /* not a BOM: rewind so we don’t lose data */
        fseek(file, 0, SEEK_SET);
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    // allocate buffer
    char *buf = (char *)malloc(fsize+1);
    if (buf == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }

    // read into memory
    size_t read = fread(buf, 1, fsize, file);
    fclose(file);
    buf[fsize] = '\0';

    source_buffer = buf;
    current_input_char = source_buffer;
}

char peek(int offset)
{
    // moves ahead to specific character in the file
    if (*(current_input_char + offset) == EOF_CHAR)
    {
        return EOF_CHAR;
    }

    return *(current_input_char + offset);
}

void skip_comments()
{
    while(1)
    {
        // skip single line comments
        if (*current_input_char == '/' && peek(1) == '/') 
        {
            // move to the second '/', skips over both '/' 
            current_input_char += 2; 

            while (*current_input_char != '\n' && *current_input_char != '\0')
            {
                current_input_char++;
            }
            continue;
        }

        // skip multi-line comment
        else if (*current_input_char == '/' && peek(1) == '*')
        {
            current_input_char += 2; // skip '/*'

            while (1) // check for '*/'
            {
                if (*current_input_char == EOF_CHAR)
                {
                    printf("Error: Unclosed block comment.\n");
                    return;
                }
                if (*current_input_char == '*' && peek(1) == '/')
                {
                    current_input_char += 2;
                    break;
                }
                if (*current_input_char == '\n')
                {
                    line++;
                    column = 1;
                }
                current_input_char++;
            }
            continue;
        }

        // leave if not inside comment
        break;
    }
}


char skip_whitespace()
{
    char temp;

    // logic to skip whitespaces
    do {
        // set temp to current input at least one.
        temp = *current_input_char;
        // ignore tabs
        if (temp == '\t' || temp == '\r')   
        {
            current_input_char++;
            continue;
        }
        // newline handler
        else if (temp == '\n') 
        {
            line++;
            column = 0;
        }
        break;
    } while(1);
   
    current_input_char++;
    column++;
    return temp;
}

char advance()
{
    // check for end of buffer
    if (*current_input_char == '\0')
    {
        return EOF_CHAR;
    }

    char temp;

    // logic to skip whitespaces
    do {
        // set temp to current input at least one.
        temp = *current_input_char;
        // ignore tabs
        if (temp == '\t' || temp == '\r')   
        {
            current_input_char++;
            continue;
        }
        // newline handler
        else if (temp == '\n') 
        {
            line++;
            column = 0;
        }
        break;
    } while(1);
   
    current_input_char++;
    column++;
    return temp;
}

char handle_parenthesis()
{

}

char handle_block()
{

}

void handle_loop()
{

}

void handle_selection()
{

}

void handle_values()
{

}

int lexer()
{
    for(;;)
    {
        skip_comments();
        char ch = *current_input_char; // look at current character

        // EOF or end of buffer
        if (ch == '\0' || ch == EOF_CHAR)
        {
            printf("DEBUG: End of file reached at line %d, column %d\n", line, column);
            break;
        }
         
        // This function checks if the current character is an operator. 
        // It also handles cases that involves compound operators such as ==, ++, -= etc.
        if (isoperator(ch))
        {
            char next = peek(1);
            // read compound operators: ==, -=, +=, >=, etc.
            if (isoperator(next))  // check if next character is an operator
            {
                if ((ch == '+' && next == '+') ||
                    (ch == '-' && next == '-') ||
                    (ch == '=' && next == '=') ||
                    (ch == '+' && next == '=') ||
                    (ch == '-' && next == '=') ||
                    (ch == '!' && next == '=') ||
                    (ch == '/' && next == '=') ||
                    (ch == '<' && next == '=') ||
                    (ch == '>' && next == '=') ||
                    (ch == '*' && next == '='))
                {
                    char op_buf[3]; // the two and null terminator; 
                    op_buf[0] = ch;
                    op_buf[1] = next;
                    op_buf[2] = '\0';
                    printf("DEBUG: operator = '%s' (ASCII: %d) line: %d col: %d\n", op_buf, ch, line, column);
                    advance();
                    advance();
                    continue; 
                }
                
                printf("DEBUG: operator = '%c' (ASCII: %d) line: %d col: %d\n", ch, ch, line, column);
                advance();
                continue;              
            }
        }

        if (isdigit(ch))
        {
            // read all digits untils different character type
            do{
                // stuck......
            } while(peek(1) != " ")
        }

        if (isalpha(ch))
        {
            
        }

        // handle left parenthesis
        if (ch == '(')
        {
            advance();
            while(peek(i) != ')')
            {
                i++;
            }
            // copy string from current input character to i
            char *str_buf = (char *)malloc(i + 1);  // don't forget to free after creating the token
            for(int j = 0; j < i; j++)
            {
                str_buf[j] = *current_input_char;
                advance();
            }
            str_buf[i] = '\0';
             
            printf("DEBUG: expression = '%s' (ASCII: %d) line: %d col: %d\n", str_buf, line, column);
            advance();
            continue;
        }


        // handle brackets
        if (ch == '[')
        {

        }

        // left curly braces
        if (ch == '{')
        {
            do 
            {

            } while(peek(1) != '}')
        }
        
    }

    
}
