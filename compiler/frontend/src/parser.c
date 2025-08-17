#include "parser.h"
#include "token.h"


Parser* init_parser()
{
    Parser* parser =  (Parser *)malloc(sizeof(Parser));
    parser->tokens = global_array;
    parser->current = 0;
    printf("\nParser initialized....\n");
    return parser;
}

Token peek_parser(Parser* parser)
{
    if (parser->tokens[parser->current].type == TOKEN_EOF)
    {
        printf("\n End of token array \n.");
        return parser->tokens[parser->current];
    }
    return parser->tokens[parser->current];
}

Token advance_parser(Parser* parser)
{
    parser->current++;

    if (parser->tokens[parser->current].type == TOKEN_EOF)
    {
        return parser->tokens[parser->current];
    }

    return parser->tokens[parser->current];
}

// match current token in parser stream with a given token
int match(Parser *parser, TokenType type)
{
    if (parser->tokens[parser->current].type == type && parser->tokens[parser->current].type != TOKEN_EOF)
    {
        advance(parser);
        return TRUE;
    }
    return FALSE;
}

// return error message on finding different token
int expect(Parser* parser, TokenType type, const char* errorMessage) 
{
    if (parser->tokens[parser->current].type != type) {
        printf("%s\n", errorMessage); // assuming you have a function like this
        return FALSE;
    }
    advance(parser);
    return TRUE;
}



// takes the initialised parser as an argument
int parser()
{
    // main parsing loop; parse until eof token
    int i = 0;
    while(i < 2)
    {
        printf("\n Parsing loop....\n");
        i++;
    }

    return 0;
}
