#ifndef _TOKEN_H_
#define _TOKEN_H_

// Scanner: read input character by character

#include <stdio.h>
#include <stdlib.h>


#define EOF_CHAR ((char)-1)

extern char *source_buffer;
extern char *current_input_char; 
extern char *next_input_char;
extern char *peekptr;

extern int line;
extern int column;

void load_source(const char *filename);
char peek(int offset);
char advance(void);
int tokeniser(void);

#endif