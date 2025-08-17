#ifndef PARSER_H_
#define PARSER_H_

#include "token.h"
#include "error.h"
#include "ast.h"

// define parser object
typedef struct 
{
    Token* tokens;
    int current;
} Parser;

/* parser functions */
Parser* init_parser(void);

// lookahead in token stream
Token peek_parser(Parser* parser);

// advance in token stream
Token advance_parser(Parser* parser);

#define TRUE 1
#define FALSE 0

// match current token in parser stream with a given token
int match(Parser* parser, TokenType type);

// return error message on finding different token
int expect(Parser* parser, TokenType type, const char* errorMessage);

// consume a token, add it to the parse tree
Token consume(Parser* parser);

// main program that does the parsing
int parser();

#endif
