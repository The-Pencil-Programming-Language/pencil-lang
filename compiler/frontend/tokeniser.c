#include <stdlib.h>
#include <stdio.h>
#include "tokeniser.h"


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

#define LOOKAHEAD 8

char peek(int offset)
{
    // end of buffer
    if (*(current_input_char + offset) == EOF_CHAR)
    {
        return EOF_CHAR;
    }

    return *(current_input_char + offset);
}

// char mpeek(int offset, char *str, int len)
// {
//     char *temp_buf;
//     for(int i = 0; i < len; i++)
//     {
//         char tchar = current_input_char[offset+i];
//         if (tchar == '\0')
//         {
//             return EOF_CHAR;
//         }
//         else
//         {
//             temp_buf += tchar;
//         }
//     }
// }

char advance()
{
    // check for end of buffer
    if (*current_input_char == '\0')
    {
        return EOF_CHAR;
    }

    char temp;

    // logic to skip whitespaces and comments
    do{
        // set temp to current input at least one.
        temp = *current_input_char;
        // ignore tabs
        if (temp == '\t')  
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
        // skip single line comments
        else if (temp == '/' && peek(1) == '/') 
        {
            while (*current_input_char != '\n' && *current_input_char != '\0')
            {
                current_input_char++;
            }
            continue;
        }
        // skip multi-line comment
        else if (temp == '/' && peek(1) == '*')
        {
            current_input_char += 2; // skip '/*'
            while (!(*current_input_char != '*' && peek(1) != '/')) // check for '*/'
            {
                current_input_char++;
            }
            current_input_char += 2;
            continue;
        }
        break;
    } while(1);
   
    current_input_char++;
    column++;
    return temp;
}
