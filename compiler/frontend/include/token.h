#ifndef _TOKEN_H_
#define _TOKEN_H_


/*
Tokens of the Pencil Programming Language
whitespaces - \n10, \t9, \r13, " "32, \f12, \v11
letters - A..Z, a..z
digits - 0..9
operators - =, +, -, %, *, !=, +=, -=, ++, --, /=, *=, <, >, <=, >=, :, ;
symbols - _, [, ], {, }, ?, (, ), &, $, #, @, |, /, \, 

Define token types (enums and macros for keywords, operators, identifiers etc.)
*/

// Tokentypes
typedef enum {
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_FOR,
    TOKEN_LOOP,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_CASE,

    TOKEN_FN,

    TOKEN_STRUCT,
    TOKEN_ENUM,
    TOKEN_TYPE,
    TOKEN_IMPORT,
    
    TOKEN_INT_LITERAL,
    TOKEN_SHORT_LITERAL,
    TOKEN_BYTE_LITERAL,
    TOKEN_LONG_LITERAL,
    TOKEN_FLOAT_LITERAL,
    TOKEN_DOUBLE_LITERAL,
    TOKEN_CHAR_LITERAL,
    TOKEN_BOOL_LITERAL,
    TOKEN_STRING_LITERAL,

    TOKEN_WHITESPACE,
    TOKEN_IDENTIFIER,

    TOKEN_LBRACKET, // [
    TOKEN_RBRACKET, // ]
    TOKEN_LCURLY,   // {
    TOKEN_RCURLY,   // }
    TOKEN_LPAREN,   // (
    TOKEN_RPAREN,   // )
    TOKEN_SEMICOLON,    
    TOKEN_COLON,    
    TOKEN_COMMA,    
    TOKEN_DOT,    
    TOKEN_ARROW,    
    TOKEN_ELLIPSIS, // ...    

    TOKEN_EOF,
    TOKEN_UNKNOWN,

    TOKEN_NEW,
    TOKEN_DROP,

    TOKEN_IDENT,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,

    TOKEN_EQUAL_EQUAL,
    TOKEN_NOT_EQUAL,
    TOKEN_LESS,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER,
    TOKEN_GREATER_EQUAL,

    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,

    TOKEN_BITWISE_AND,
    TOKEN_BITWISE_OR,
    TOKEN_BITWISE_XOR,
    TOKEN_BITWISE_NOT,
    TOKEN_LSHIFT,
    TOKEN_RSHIFT,

    TOKEN_ASSIGN,
    TOKEN_PLUS_ASSIGN,
    TOKEN_MINUS_ASSIGN,
    TOKEN_STAR_ASSIGN,
    TOKEN_SLASH_ASSIGN,
    TOKEN_PERCENT_ASSIGN,
    TOKEN_AND_ASSIGN,
    TOKEN_OR_ASSIGN,
    TOKEN_NOT_ASSIGN, // same as TOKEN_NOT_EQUAL
    TOKEN_XOR_ASSIGN,
    TOKEN_LSHIFT_ASSIGN,
    TOKEN_RSHIFT_ASSIGN,
} TokenType;

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




#endif