#ifndef H_
#define H_

/*
Tokens of the Pencil Programming Language
whitespaces - \n10, \t9, \r13, " "32, \f12, \v11
letters - A..Z, a..z
digits - 0..9
operators - =, +, -, %, *, !=, +=, -=, ++, --, /=, *=, <, >, <=, >=, :, ;
symbols - _, [, ], {, }, ?, (, ), &, $, #, @, |, /, \, 

Define token types (enums and macros for keywords, operators, identifiers etc.)
*/


// Declare, not define
extern const char *keywords[];
#define KEYWORDS 18

// Tokentypes
typedef enum 
{
    IF,
    ELSE,
    FOR,
    LOOP,
    BREAK,
    CONTINUE,
    CASE,
    FN,
    MAIN,
    STRUCT,
    ENUM,
    TYPE,
    CONST,
    IMPORT,
    INT_LITERAL,
    FLOAT_LITERAL,
    CHAR_LITERAL,
    BOOL_LITERAL,
    HEX_LITERAL,
    OCTAL_LITERAL,
    BINARY_LITERAL,
    STRING_LITERAL,
    WHITESPACE,
    IDENTIFIER,
    KEYWORD,
    LBRACKET, // [
    RBRACKET, // ]
    LCURLY,   // {
    RCURLY,   // }
    LPAREN,   // (
    RPAREN,   // )
    SEMICOLON,    
    COLON,    
    COMMA,    
    DOT,  
    QUOTE, // '  
    DOUBLE_QUOTE, // '  
    ARROW,    
    TOKEN_EOF,
    NEW,
    DROP,
    PLUS,
    PLUS_PLUS,
    MINUS,
    MINUS_MINUS,
    STAR,
    STAR_STAR,
    SLASH,
    PERCENT,
    EQUAL,
    NOT_EQUAL,
    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,
    SLASH_EQUAL,
    AND,
    OR,
    NOT,
    BITWISE_AND,
    BITWISE_OR,
    BITWISE_XOR,
    BITWISE_NOT,
    LSHIFT,
    RSHIFT,
    ASSIGN,
    PLUS_ASSIGN,
    AND_ASSIGN,
    MINUS_ASSIGN,
    STAR_ASSIGN,
    SLASH_ASSIGN,
    PERCENT_ASSIGN,
    UNKNOWN
    
} TokenType;

typedef struct 
{
    TokenType type;
    char *lexeme;
    int line;
    int column;
} Token;

typedef struct
{
    Token** tokens;
    int count;
    int capacity;
} TokenArray;

extern Token* tokens[];
extern int  count;
// extern const char *keywords[];
extern TokenArray* global_array;

// returns the string of a token type
const char* tokentype_to_string(TokenType type);
void add_token(TokenType type, const char* lexeme, int length, int line, int column);
void print_token();
void free_tokens();
TokenType keyword_to_token(char *keyword);

// Token Array Management
TokenArray* create_array();
void init_global_array();
void free_array(TokenArray* arr);
void free_token(Token* token);

// Token Creation & Addition
Token* create_token(TokenType type, const char* lexeme, int length, int line, int column);
void add_to_array(TokenArray* arr, TokenType type, const char* lexeme, int length, int line, int column);
void add_token(TokenType type, const char* lexeme, int length, int line, int column);

// Printing Functions
void print_token(Token* token);
void print_detailed(Token* token);
void print_debug(Token* token);
void print_all_tokens_from_array(TokenArray* arr);
void print_all_tokens();
void print_tokens_filtered(TokenArray* arr);
void print_tokens_as_source(TokenArray* arr);
void print_stats(TokenArray* arr);

// Global Array Utilities
void print_tokens_filtered_global();
void print_tokens_as_source_global();
void print_stats_global();

// Global token array
extern TokenArray* global_array;

#endif