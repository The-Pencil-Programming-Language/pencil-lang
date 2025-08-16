#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "token.h"

#define TRUE 1
#define FALSE 0

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
    if (*(current_input_char + offset) == '\0')
    {
        return EOF_CHAR;
    }
    return *(current_input_char + offset);
}

void advance(void)
{
    if(*current_input_char == '\n')
    {
        line++;
        column = 1;
    } else
    {
        column++;
    }
    current_input_char++;
}

// int match(char expected)
// {
//     if (peek(1) == expected)
//     {
//         advance();
//         return TRUE;
//     }
//     return FALSE;
// }

// main lexer logic
int lexer(void)
{
    printf("Lexer...\n");
    for(;;)
    {
        char ch = *current_input_char;
        
        if (isspace(ch))
        {
            advance();
            continue;
        }

        if (ch == '/')
        {
            if (peek(1) == '/')
            {
                while(ch != '\n' && ch != '\0')
                {
                    advance();
                    ch = *current_input_char;
                }
                if (ch == '\n') advance();  // (NOTE: only if newline) | consume the newline (if not EOF)
                continue;
                
            }
            else if (peek(1) == '*')
            {
                // advance(); // consume '/'
                // advance(); // consume '*'
                while(1)
                {
                    advance();
                    ch = *current_input_char;
                    if (ch == '\0')
                    {
                        printf("Error: Unclosed block comment.\n");
                        exit(1);
                    }

                    if (peek(1) == '*' && peek(2) == '/')
                    {
                        advance(); advance();
                        break;
                    }
                }

                advance();
                continue;
            }
            else
            {
                goto operators_delimiters;
            }

            // else it's a division operator or SLASH
            continue;
        }

        // check for eof
        if (ch == '\0' || ch == EOF_CHAR)
        {
            add_token(TOKEN_EOF, "EOF", 3, line, column);
            break;
        }
        
        // handle digits
        // handle different number systems like hex, octal and binary
        if (isdigit(ch))
        {
            if (ch == '0')
            {
                int has_point = FALSE;
                char next = peek(1);
                
                if (next == 'b' || next == 'B') 
                {
                    advance();
                    advance(); // skip the prefix -> '0b'
                    int j = 0;
                    while(peek(j) == '0' || peek(j) == '1')
                    {
                        j++;
                    }
                    char lexeme[j+1];
                    for (int k = 0; k < j; k++)
                    {
                        lexeme[k] = *current_input_char;
                        advance();
                    }
                    lexeme[j] = '\0';
                    add_token(BINARY_LITERAL, lexeme, j, line, column-j);
                    continue;
                } 
                
                if (next == 'o' || next == 'O') 
                {
                    advance();
                    advance(); // skip the prefix -> '0o'
                    int j = 0;
                    while(peek(j) >= '0' && peek(j) <= '7')
                    {
                        j++;
                    }
                    char lexeme[j+1];
                    for (int k = 0; k < j; k++)
                    {
                        lexeme[k] = *current_input_char;
                        advance();
                    }
                    lexeme[j] = '\0';
                    add_token(OCTAL_LITERAL, lexeme, j, line, column-j);
                    continue;
                } 
                
                if (next == 'x' || next == 'X') 
                {
                    advance();
                    advance(); // skip the prefix -> '0x'
                    int j = 0;
                    while(isxdigit(peek(j)))  // Using isxdigit() for cleaner hex checking
                    {
                        j++;
                    }
                    char lexeme[j+1];
                    for (int k = 0; k < j; k++)
                    {
                        lexeme[k] = *current_input_char;
                        advance();
                    }
                    lexeme[j] = '\0';
                    add_token(HEX_LITERAL, lexeme, j, line, column-j);
                    continue;
                }

                // Handle regular numbers starting with 0 (including 0.5, 007, etc.)
                int i = 0;  // Start from current position
                char curr = ch;  // Start with the '0' we already have
                
                while(1)
                {
                    if (isdigit(curr))
                    {
                        i++;
                        curr = peek(i);
                    }
                    else if (curr == '.' && !has_point && isdigit(peek(i+1)))
                    {
                        has_point = TRUE;
                        i++;
                        curr = peek(i);
                    }
                    else
                    {
                        break;
                    }
                }
                
                char lexeme[i+1];
                for (int k = 0; k < i; k++)
                {
                    lexeme[k] = *current_input_char;
                    advance();
                }
                lexeme[i] = '\0';
                add_token(has_point ? FLOAT_LITERAL : INT_LITERAL, lexeme, i, line, column-i);
                continue;
            }
            else
            {
                // Handle numbers not starting with 0
                int i = 0;
                int has_point = FALSE;
                char curr = ch;
                
                while(1)
                {
                    if (isdigit(curr))
                    {
                        i++;
                        curr = peek(i);
                    }
                    else if (curr == '.' && !has_point && isdigit(peek(i+1)))
                    {
                        has_point = TRUE;
                        i++;
                        curr = peek(i);
                    }
                    else
                    {
                        break;
                    }
                }
                
                char lexeme[i+1];
                for (int k = 0; k < i; k++)
                {
                    lexeme[k] = *current_input_char;
                    advance();
                }
                lexeme[i] = '\0';
                add_token(has_point ? FLOAT_LITERAL : INT_LITERAL, lexeme, i, line, column-i);
                continue;
            }
        }

        // handle alnum
        if (isalpha(ch))
        {
            int i = 0;
            while (isalnum(peek(i)) || peek(i) == '_') {
                i++;
            }

            char lexeme[i+1];
            for (int k = 0; k < i; k++)
            {
                lexeme[k] = *current_input_char;
                advance();
            }
            lexeme[i] ='\0';

            int j = 0;
            while(j != KEYWORDS)
            {
                if (strcmp(keywords[j], lexeme) == 0)
                {
                    add_token(keyword_to_token(keywords[j]), lexeme, i, line, column-i);
                    break;
                }
                j++;
            }

            if (j == KEYWORDS)
            {
                add_token(IDENTIFIER, lexeme, i, line, column-i);
            }
            // advance();
            continue; 
        }

        string_and_char:
        if (ch == '"' || ch == '\'') 
        {
            char quote = ch;
            advance(); // skip opening quote, no need " and ' handles it before jumping here
            int i = 0;
            while (peek(i) != quote && peek(i) != '\0') {
                i++;
            }

            if (peek(i) == '\0') {
                fprintf(stderr, "Unterminated string/char literal. Line %d, Column %d\n", line, column);
                exit(1);
            }

            char* lexeme = malloc(i + 1);
            for (int k = 0; k < i; k++) {
                lexeme[k] = *current_input_char;
                advance();
            }
            lexeme[i] = '\0';
            advance(); // skip closing quote

            add_token(STRING_LITERAL, lexeme, i, line, column);
            free(lexeme);
            continue;
        }

        operators_delimiters:
        switch(ch)
        {
            case '"': 
                // add_token(DOUBLE_QUOTE, "\"", 1, line, column); 
                advance();
                goto string_and_char; 
                continue;
            case '\'': 
                // add_token(QUOTE, "\'", 1, line, column); 
                advance(); 
                goto string_and_char; 
                continue;
            case '(': 
                add_token(LPAREN, "(", 1, line, column); 
                advance(); 
                continue;
            case ')': 
                add_token(RPAREN, ")", 1, line, column); 
                advance(); 
                continue;
            case '{': 
                add_token(LCURLY, "{", 1, line, column); 
                advance(); 
                continue;
            case '}': 
                add_token(RCURLY, "}", 1, line, column); 
                advance(); 
                continue;
            case '[': 
                add_token(LBRACKET, "[", 1, line, column); 
                advance(); 
                continue;
            case ']': 
                add_token(RBRACKET, "]", 1, line, column); 
                advance(); 
                continue;
            case '>':
                if (peek(1) == '>')
                {
                    add_token(RSHIFT, ">>", 3, line, column);
                    advance();
                    advance();
                    continue;
                } 
                if (peek(1) == '=')
                {
                    add_token(GREATER_EQUAL, ">=", 3, line, column);
                    advance();
                    advance();
                    continue;
                }
                else
                {
                    add_token(GREATER, ">", 2, line, column);
                    advance();
                    continue;
                }

            case '<':
                if (peek(1) == '<')
                {
                    add_token(LSHIFT, "<<", 3, line, column);
                    advance();
                    advance();
                    continue;
                } 
                if (peek(1) == '=')
                {
                    add_token(LESS_EQUAL, "<=", 3, line, column);
                    advance();
                    advance();
                    continue;
                }
                else
                {
                    add_token(LESS, "<", 2, line, column);
                    advance();
                    continue;
                }
            case ';': 
                add_token(SEMICOLON, ";", 1, line, column); 
                advance(); 
                continue;
            case ':': 
                add_token(COLON, ":", 1, line, column); 
                advance(); 
                continue;
            case ',': 
                add_token(COMMA, ",", 1, line, column); 
                advance(); 
                continue;
            case '.':
                if (peek(1) == '.' && peek(2) == '.') 
                {
                    add_token(UNKNOWN, "...", 3, line, column);
                    advance(); advance(); advance();
                    continue;
                } else 
                {
                    add_token(DOT, ".", 1, line, column);
                    advance();
                    continue;
                }
            case '=':
                if (peek(1) == '=')
                {
                    add_token(EQUAL, "==", 3, line, column);
                    advance();
                    advance();
                    continue;
                } else 
                {
                    char lexeme[2] = {ch, '\0'};
                    add_token(ASSIGN, lexeme, 2, line, column); 
                    advance(); 
                    continue;
                }
                case '/':
                if (peek(1) == '=')
                {
                    add_token(SLASH_EQUAL, "/=", 3, line, column);
                    advance();
                    advance();
                    continue;
                } else 
                {
                    char lexeme[2] = {ch, '\0'};
                    add_token(SLASH, lexeme, 2, line, column); 
                    advance(); 
                    continue;
                }
            case '-':
                if (peek(1) == '-')
                {
                    add_token(MINUS_MINUS, "--", 3, line, column);
                    advance();
                    advance();
                    continue;
                }
                if (peek(1) == '=')
                {
                    add_token(MINUS_ASSIGN, "-=", 3, line, column);
                    advance();
                    advance();
                    continue;
                }
                if (peek(1) == '>')
                {
                    add_token(ARROW, "->", 3, line, column);
                    advance();
                    advance();
                    continue;
                } else 
                {
                    char lexeme[2] = {ch, '\0'};
                    add_token(MINUS, lexeme, 2, line, column); 
                    advance(); 
                    continue;
                }
            case '+':
                if (peek(1) == '+')
                {
                    add_token(PLUS_PLUS, "++", 3, line, column);
                    advance();
                    advance();
                    printf("minusminus\n");
                    continue;
                }
                if (peek(1) == '=')
                {
                    add_token(PLUS_ASSIGN, "+=", 3, line, column);
                    advance();
                    advance();
                    continue;
                } else 
                {
                    char lexeme[2] = {ch, '\0'};
                    add_token(PLUS, lexeme, 2, line, column); 
                    advance(); 
                    continue;
                }
            case '*':
                if (peek(1) == '*')
                {
                    add_token(STAR_STAR, "**", 3, line, column);
                    advance();
                    advance();
                    continue;
                }
                if (peek(1) == '=')
                {
                    add_token(STAR_ASSIGN, "*=", 3, line, column);
                    advance();
                    advance();
                    continue;
                } else 
                {
                    char lexeme[2] = {ch, '\0'};
                    add_token(STAR, lexeme, 2, line, column); 
                    advance(); 
                    continue;
                }
            case '&':
                if (peek(1) == '&')
                {
                    add_token(AND, "&&", 3, line, column);
                    advance();
                    advance();
                    continue;
                }
                if (peek(1) == '=')
                {
                    add_token(AND_ASSIGN, "&=", 3, line, column);
                    advance();
                    advance();
                    continue;
                } else 
                {
                    char lexeme[2] = {ch, '\0'};
                    add_token(BITWISE_AND, lexeme, 2, line, column); 
                    advance(); 
                    continue;
                }
            default: 
            {
                // char unknown[2] = {ch, '\0'};
                // add_token(UNKNOWN, unknown, 1, line, column);
                advance();
                break;
            }
        }

        // If we get here, we didn't match any token pattern
        char unknown[2] = {ch, '\0'};
        add_token(UNKNOWN, unknown, 1, line, column);
        advance();
    }

    return 0;
}

