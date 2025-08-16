#ifndef LEXER_H_
#define LEXER_H_

// Scanner: read input character by character

#include <stdio.h>
#include <stdlib.h>
#include "token.h"

#define EOF_CHAR ((char)-1)

extern char *source_buffer;
extern char *current_input_char; 
extern char *next_input_char;
extern char *peekptr;

extern int line;
extern int column;

void load_source(const char *filename);
char peek(int offset);
void advance(void);
void skip_comments(void);
int lexer(void);

// void add_token(TokenType type, const char* lexeme, int length);
// void print_token();
// void free_tokens();


#endif