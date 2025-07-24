#include "token.h"

// Keyword list for recognizing keywords
const char *keywords[] = 
{
    "if", 
    "else", 
    "loop", 
    "for",  
    "case", 
    "import", 
    "struct", 
    "enum",  
    "int", 
    "byte", 
    "short", 
    "long", 
    "float", 
    "double", 
    "in", 
    "break",
    "continue",
    "fn",
    "main"
};


const char* tokentype_to_string(TokenType type) {
    switch (type) {
        case TOKEN_IF: return "TOKEN_IF";
        case TOKEN_ELSE: return "TOKEN_ELSE";
        case TOKEN_FOR: return "TOKEN_FOR";
        case TOKEN_LOOP: return "TOKEN_LOOP";
        case TOKEN_BREAK: return "TOKEN_BREAK";
        case TOKEN_CONTINUE: return "TOKEN_CONTINUE";
        case TOKEN_CASE: return "TOKEN_CASE";

        case TOKEN_FN: return "TOKEN_FN";

        case TOKEN_STRUCT: return "TOKEN_STRUCT";
        case TOKEN_ENUM: return "TOKEN_ENUM";
        case TOKEN_TYPE: return "TOKEN_TYPE";
        case TOKEN_IMPORT: return "TOKEN_IMPORT";

        case TOKEN_INT_LITERAL: return "TOKEN_INT_LITERAL";
        case TOKEN_SHORT_LITERAL: return "TOKEN_SHORT_LITERAL";
        case TOKEN_BYTE_LITERAL: return "TOKEN_BYTE_LITERAL";
        case TOKEN_LONG_LITERAL: return "TOKEN_LONG_LITERAL";
        case TOKEN_FLOAT_LITERAL: return "TOKEN_FLOAT_LITERAL";
        case TOKEN_DOUBLE_LITERAL: return "TOKEN_DOUBLE_LITERAL";
        case TOKEN_CHAR_LITERAL: return "TOKEN_CHAR_LITERAL";
        case TOKEN_BOOL_LITERAL: return "TOKEN_BOOL_LITERAL";
        case TOKEN_STRING_LITERAL: return "TOKEN_STRING_LITERAL";

        case TOKEN_WHITESPACE: return "TOKEN_WHITESPACE";
        case TOKEN_IDENTIFIER: return "TOKEN_IDENTIFIER";

        case TOKEN_LBRACKET: return "TOKEN_LBRACKET";
        case TOKEN_RBRACKET: return "TOKEN_RBRACKET";
        case TOKEN_LCURLY: return "TOKEN_LCURLY";
        case TOKEN_RCURLY: return "TOKEN_RCURLY";
        case TOKEN_LPAREN: return "TOKEN_LPAREN";
        case TOKEN_RPAREN: return "TOKEN_RPAREN";
        case TOKEN_SEMICOLON: return "TOKEN_SEMICOLON";
        case TOKEN_COLON: return "TOKEN_COLON";
        case TOKEN_COMMA: return "TOKEN_COMMA";
        case TOKEN_QUOTE: return "TOKEN _QUOTE";
        case TOKEN_DOUBLE_QUOTE: return "TOKEN _DOUBLE_QUOTE";
        case TOKEN_DOT: return "TOKEN_DOT";
        case TOKEN_ARROW: return "TOKEN_ARROW";
        case TOKEN_ELLIPSIS: return "TOKEN_ELLIPSIS";

        case TOKEN_EOF: return "TOKEN_EOF";
        case TOKEN_UNKNOWN: return "TOKEN_UNKNOWN";

        case TOKEN_NEW: return "TOKEN_NEW";
        case TOKEN_DROP: return "TOKEN_DROP";

        case TOKEN_IDENT: return "TOKEN_IDENT";

        case TOKEN_PLUS: return "TOKEN_PLUS";
        case TOKEN_MINUS: return "TOKEN_MINUS";
        case TOKEN_STAR: return "TOKEN_STAR";
        case TOKEN_SLASH: return "TOKEN_SLASH";
        case TOKEN_PERCENT: return "TOKEN_PERCENT";

        case TOKEN_EQUAL: return "TOKEN_EQUAL";
        case TOKEN_NOT_EQUAL: return "TOKEN_NOT_EQUAL";
        case TOKEN_LESS: return "TOKEN_LESS";
        case TOKEN_LESS_EQUAL: return "TOKEN_LESS_EQUAL";
        case TOKEN_GREATER: return "TOKEN_GREATER";
        case TOKEN_GREATER_EQUAL: return "TOKEN_GREATER_EQUAL";

        case TOKEN_AND: return "TOKEN_AND";
        case TOKEN_OR: return "TOKEN_OR";
        case TOKEN_NOT: return "TOKEN_NOT";

        case TOKEN_BITWISE_AND: return "TOKEN_BITWISE_AND";
        case TOKEN_BITWISE_OR: return "TOKEN_BITWISE_OR";
        case TOKEN_BITWISE_XOR: return "TOKEN_BITWISE_XOR";
        case TOKEN_BITWISE_NOT: return "TOKEN_BITWISE_NOT";
        case TOKEN_LSHIFT: return "TOKEN_LSHIFT";
        case TOKEN_RSHIFT: return "TOKEN_RSHIFT";

        case TOKEN_ASSIGN: return "TOKEN_ASSIGN";
        case TOKEN_PLUS_ASSIGN: return "TOKEN_PLUS_ASSIGN";
        case TOKEN_MINUS_ASSIGN: return "TOKEN_MINUS_ASSIGN";
        case TOKEN_STAR_ASSIGN: return "TOKEN_STAR_ASSIGN";
        case TOKEN_SLASH_ASSIGN: return "TOKEN_SLASH_ASSIGN";
        case TOKEN_PERCENT_ASSIGN: return "TOKEN_PERCENT_ASSIGN";
        case TOKEN_AND_ASSIGN: return "TOKEN_AND_ASSIGN";
        case TOKEN_OR_ASSIGN: return "TOKEN_OR_ASSIGN";
        case TOKEN_NOT_ASSIGN: return "TOKEN_NOT_ASSIGN";
        case TOKEN_XOR_ASSIGN: return "TOKEN_XOR_ASSIGN";
        case TOKEN_LSHIFT_ASSIGN: return "TOKEN_LSHIFT_ASSIGN";
        case TOKEN_RSHIFT_ASSIGN: return "TOKEN_RSHIFT_ASSIGN";

        default: return "UNKNOWN_TOKEN_TYPE";
    }
}


#define MAX_TOKENS 10000

Token* tokens[MAX_TOKENS];
int token_count = 0;

void add_token(TokenType type, const char* lexeme, int length, int line, int column) 
{
    if (token_count >= MAX_TOKENS) {
        printf("Token Count %d", token_count);
        printf("Too many tokens!\n");
        exit(1);
    }

    Token* token = (Token*)malloc(sizeof(Token));
    token->type = type;
    token->line = line;
    token->column = column;

    token->lexeme = (char*)malloc(length + 1);
    strncpy(token->lexeme, lexeme, length);
    token->lexeme[length] = '\0';

    tokens[token_count++] = token;
}

void print_token()
{
    for (int i = 0; i < token_count; i++) {
        Token* t = tokens[i];
        printf("%s: '%s' (line %d, col %d)\n", tokentype_to_string(t->type), t->lexeme, t->line, t->column);
    }
    
}

void free_tokens() 
{
    for (int i = 0; i < token_count; i++) {
        free(tokens[i]->lexeme);
        free(tokens[i]);
    }
    token_count = 0;
}
