#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

void skip_whitespace(void)
{
    while(1)
    {
        char ch = *current_input_char;
        switch(ch)
        {
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                advance();
                break;
            default:
                return;
        }
    }
}


// main lexer logic
int lexer(void)
{
    printf("Lexer...\n");
    for(;;)
    {
        skip_whitespace();

        char ch = *current_input_char;

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
                        break;
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

            // else it's a division operator or TOKEN_SLASH
            continue;
        }

        // check for eof
        if (ch == '\0' || ch == EOF_CHAR)
        {
            add_token(TOKEN_EOF, "EOF", 3, line, column);
            break;
        }
        // handle digits
        if (isdigit(ch))
        {
            int i = 1;
            int has_point = FALSE;
            while(1)
            {
                char next = peek(i);
                if (isdigit(next))
                {
                    i++;
                }
                else if (next == '.' && !has_point && isdigit(peek(i+1)))
                {
                    has_point = TRUE;
                    i++;
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
            lexeme[i] ='\0';
            add_token(has_point ? TOKEN_FLOAT_LITERAL : TOKEN_INT_LITERAL, lexeme, i, line, column);
            // advance();
            continue;
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

            // TODO: check to see if identifer is keyword
            add_token(TOKEN_IDENTIFIER, lexeme, i, line, column);
            // advance();
            continue; 
        }

        string_and_char:
        if (ch == '"' || ch == '\'') {
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

            add_token(TOKEN_STRING_LITERAL, lexeme, i, line, column);
            free(lexeme);
            continue;
        }

        switch(ch)
        {
            case '"': 
                add_token(TOKEN_DOUBLE_QUOTE, "\"", 1, line, column); 
                advance();
                goto string_and_char; 
                continue;
            case '\'': 
                add_token(TOKEN_QUOTE, "\'", 1, line, column); 
                advance(); 
                goto string_and_char; 
                continue;
            case '(': 
                add_token(TOKEN_LPAREN, "(", 1, line, column); 
                advance(); 
                continue;
            case ')': 
                add_token(TOKEN_RPAREN, ")", 1, line, column); 
                advance(); 
                continue;
            case '{': 
                add_token(TOKEN_LCURLY, "{", 1, line, column); 
                advance(); 
                continue;
            case '}': 
                add_token(TOKEN_RCURLY, "}", 1, line, column); 
                advance(); 
                continue;
            case '[': 
                add_token(TOKEN_LBRACKET, "[", 1, line, column); 
                advance(); 
                continue;
            case ']': 
                add_token(TOKEN_RBRACKET, "]", 1, line, column); 
                advance(); 
                continue;
            case ';': 
                add_token(TOKEN_SEMICOLON, ";", 1, line, column); 
                advance(); 
                continue;
            case ':': 
                add_token(TOKEN_COLON, ":", 1, line, column); 
                advance(); 
                continue;
            case ',': 
                add_token(TOKEN_COMMA, ",", 1, line, column); 
                advance(); 
                continue;
            case '.':
                if (peek(1) == '.' && peek(2) == '.') 
                {
                    add_token(TOKEN_ELLIPSIS, "...", 3, line, column);
                    advance(); advance(); advance();
                    continue;
                } else 
                {
                    add_token(TOKEN_DOT, ".", 1, line, column);
                    advance();
                    continue;
                }
            case '=':
                if (peek(1) == '=')
                {
                    add_token(TOKEN_EQUAL, "==", 3, line, column);
                    advance();
                    advance();
                    continue;
                } else 
                {
                    char lexeme[2] = {ch, '\0'};
                    add_token(TOKEN_ASSIGN, lexeme, 2, line, column); 
                    advance(); 
                    continue;
                }
            case '/':
                if (peek(1) == '=')
                {
                    add_token(TOKEN_SLASH_EQUAL, "/=", 3, line, column);
                    advance();
                    advance();
                    continue;
                } else 
                {
                    char lexeme[2] = {ch, '\0'};
                    add_token(TOKEN_SLASH, lexeme, 2, line, column); 
                    advance(); 
                    continue;
                }
            case '-':
                if (peek(1) == '-')
                {
                    add_token(TOKEN_MINUS_MINUS, "--", 3, line, column);
                    advance();
                    advance();
                    continue;
                }
                if (peek(1) == '=')
                {
                    add_token(TOKEN_MINUS_ASSIGN, "-=", 3, line, column);
                    advance();
                    advance();
                    continue;
                }
                if (peek(1) == '>')
                {
                    add_token(TOKEN_ARROW, "->", 3, line, column);
                    advance();
                    advance();
                    continue;
                } else 
                {
                    char lexeme[2] = {ch, '\0'};
                    add_token(TOKEN_MINUS, lexeme, 2, line, column); 
                    advance(); 
                    continue;
                }
            case '+':
                if (peek(1) == '+')
                {
                    add_token(TOKEN_PLUS_PLUS, "++", 3, line, column);
                    advance();
                    advance();
                    continue;
                }
                if (peek(1) == '=')
                {
                    add_token(TOKEN_PLUS_ASSIGN, "+=", 3, line, column);
                    advance();
                    advance();
                    continue;
                } else 
                {
                    char lexeme[2] = {ch, '\0'};
                    add_token(TOKEN_PLUS, lexeme, 2, line, column); 
                    advance(); 
                    continue;
                }
            case '*':
                if (peek(1) == '*')
                {
                    add_token(TOKEN_STAR_STAR, "**", 3, line, column);
                    advance();
                    advance();
                    continue;
                }
                if (peek(1) == '=')
                {
                    add_token(TOKEN_STAR_ASSIGN, "*=", 3, line, column);
                    advance();
                    advance();
                    continue;
                } else 
                {
                    char lexeme[2] = {ch, '\0'};
                    add_token(TOKEN_STAR, lexeme, 2, line, column); 
                    advance(); 
                    continue;
                }
            default: 
            {
                // char unknown[2] = {ch, '\0'};
                // add_token(TOKEN_UNKNOWN, unknown, 1, line, column);
                advance();
                break;
            }
        }

        // If we get here, we didn't match any token pattern
        char unknown[2] = {ch, '\0'};
        add_token(TOKEN_UNKNOWN, unknown, 1, line, column);
        advance();
    }

    return token_count;
}





