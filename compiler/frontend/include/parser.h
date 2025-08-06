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
Parser init_parser(void);

// lookahead in token stream
Token peek(Parser* parser);

// advance in token stream
Token advance(Parser *parser);

#define TRUE 1
#define FALSE 0
// match current token in parser stream with a given token
int match(Parser *parser, TokenType type);

// return error message on finding different token
int expect(Parser* parser, TokenType type, char* errorMessage);

// parse variable
// parse const
// parse stmt
// parse function
// parse loop
// parse if stmt




#endif
