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
    "char",
    "str",
    "short", 
    "long", 
    "float", 
    "double", 
    "break",
    "continue",
    "fn",
    "main",
    "unsigned",
    "signed"
};

TokenType keyword_to_token(char *keyword)
{
    if (strcmp(keyword, "if") == 0) return TOKEN_IF;
    else if (strcmp(keyword, "else") == 0) return TOKEN_ELSE;
    else if (strcmp(keyword, "loop") == 0) return TOKEN_LOOP;
    else if (strcmp(keyword, "for") == 0) return TOKEN_FOR;
    else if (strcmp(keyword, "case") == 0) return TOKEN_CASE;
    else if (strcmp(keyword, "import") == 0) return TOKEN_IMPORT;
    else if (strcmp(keyword, "struct") == 0) return TOKEN_STRUCT;
    else if (strcmp(keyword, "enum") == 0) return TOKEN_ENUM;
    else if (strcmp(keyword, "break") == 0) return TOKEN_BREAK;
    else if (strcmp(keyword, "continue") == 0) return TOKEN_CONTINUE;
    else if (strcmp(keyword, "fn") == 0) return TOKEN_FN;
    else if (strcmp(keyword, "main") == 0) return TOKEN_MAIN;
    else if (strcmp(keyword, "byte") == 0) return TOKEN_TYPE;
    else if (strcmp(keyword, "short") == 0) return TOKEN_TYPE;
    else if (strcmp(keyword, "str") == 0) return TOKEN_TYPE;
    else if (strcmp(keyword, "char") == 0) return TOKEN_TYPE;
    else if (strcmp(keyword, "int") == 0) return TOKEN_TYPE;
    else if (strcmp(keyword, "long") == 0) return TOKEN_TYPE;
    else if (strcmp(keyword, "float") == 0) return TOKEN_TYPE;
    else if (strcmp(keyword, "double") == 0) return TOKEN_TYPE;
    else if (strcmp(keyword, "signed") == 0) return TOKEN_SIGNED;
    else if (strcmp(keyword, "unsigned") == 0) return TOKEN_UNSIGNED;
    else return TOKEN_UNKNOWN;
}


const char* tokentype_to_string(TokenType type) 
{
    switch (type) {
        case TOKEN_IF: return "TOKEN_IF";
        case TOKEN_ELSE: return "TOKEN_ELSE";
        case TOKEN_FOR: return "TOKEN_FOR";
        case TOKEN_LOOP: return "TOKEN_LOOP";
        case TOKEN_BREAK: return "TOKEN_BREAK";
        case TOKEN_CONTINUE: return "TOKEN_CONTINUE";
        case TOKEN_CASE: return "TOKEN_CASE";

        case TOKEN_FN: return "TOKEN_FN";
        case TOKEN_MAIN: return "TOKEN_MAIN";

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
        
        case TOKEN_HEX_LITERAL: return "TOKEN_HEX_LITREAL";
        case TOKEN_OCTAL_LITERAL: return "TOKEN_OCTAL_LITREAL";
        case TOKEN_BINARY_LITERAL: return "TOKEN_BINARY_LITREAL";

        case TOKEN_STRING_LITERAL: return "TOKEN_STRING_LITERAL";

        case TOKEN_WHITESPACE: return "TOKEN_WHITESPACE";
        case TOKEN_IDENTIFIER: return "TOKEN_IDENTIFIER";
        case TOKEN_KEYWORD: return "TOKEN_KEYWORD";

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

// Create a new token array
TokenArray* create_token_array() {
    TokenArray* arr = malloc(sizeof(TokenArray));
    if (!arr) {
        printf("Error: Failed to allocate memory for token array\n");
        exit(1);
    }
    
    arr->tokens = malloc(sizeof(Token*) * 16);  // Start with capacity of 16
    if (!arr->tokens) {
        printf("Error: Failed to allocate memory for tokens\n");
        free(arr);
        exit(1);
    }
    
    arr->count = 0;
    arr->capacity = 16;
    return arr;
}

// Create a new token with the given fields
Token* create_token(TokenType type, const char* lexeme, int length, int line, int column) {
    Token* token = malloc(sizeof(Token));
    if (!token) {
        printf("Error: Failed to allocate memory for token\n");
        exit(1);
    }
    
    token->type = type;
    token->line = line;
    token->column = column;
    
    // Allocate and copy lexeme
    if (lexeme && length > 0) {
        token->lexeme = malloc(length + 1);
        if (!token->lexeme) {
            printf("Error: Failed to allocate memory for lexeme\n");
            free(token);
            exit(1);
        }
        strncpy(token->lexeme, lexeme, length);
        token->lexeme[length] = '\0';
    } else {
        token->lexeme = malloc(1);
        token->lexeme[0] = '\0';
    }
    
    return token;
}

// Fixed function signature - takes individual fields, not a Token parameter
void add_token_to_array(TokenArray* arr, TokenType type, const char* lexeme, int length, int line, int column) {
    if (!arr) {
        printf("Error: Token array is NULL\n");
        return;
    }
    
    // Resize array if needed
    if (arr->count >= arr->capacity) {
        int new_capacity = arr->capacity * 2;
        Token** new_tokens = realloc(arr->tokens, sizeof(Token*) * new_capacity);
        if (!new_tokens) {
            printf("Error: Failed to resize token array\n");
            exit(1);
        }
        arr->tokens = new_tokens;
        arr->capacity = new_capacity;
        
        printf("Token array resized to capacity: %d\n", new_capacity);
    }
    
    // Create and add the token
    Token* new_token = create_token(type, lexeme, length, line, column);
    arr->tokens[arr->count] = new_token;
    arr->count++;
}

// Global token array instance
TokenArray* global_token_array = 0;  // Use 0 instead of NULL for C99 compatibility

void init_global_token_array() {
    if (!global_token_array) {
        global_token_array = create_token_array();
    }
}

// Wrapper function that matches your lexer's add_token signature
void add_token(TokenType type, const char* lexeme, int length, int line, int column) {
    if (!global_token_array) {
        init_global_token_array();
    }
    add_token_to_array(global_token_array, type, lexeme, length, line, column);
}

// Clean up functions
void free_token(Token* token) {
    if (token) {
        if (token->lexeme) {
            free(token->lexeme);
        }
        free(token);
    }
}

void free_token_array(TokenArray* arr) {
    if (arr) {
        for (int i = 0; i < arr->count; i++) {
            free_token(arr->tokens[i]);
        }
        free(arr->tokens);
        free(arr);
    }
}

// Print a single token (basic version)
void print_token(Token* token) {
    if (token == 0) {  // Use 0 instead of NULL
        printf("NULL TOKEN\n");
        return;
    }
    
    printf("%-20s | %-20s | Line: %d, Col: %d\n", 
           tokentype_to_string(token->type),
           token->lexeme ? token->lexeme : "(null)",
           token->line,
           token->column);
}

// Print a single token (detailed version) - removed length field access
void print_token_detailed(Token* token) {
    if (token == 0) {
        printf("NULL TOKEN\n");
        return;
    }
    
    printf("Token {\n");
    printf("  Type:    %s\n", tokentype_to_string(token->type));
    printf("  Lexeme:  \"%s\"\n", token->lexeme ? token->lexeme : "(null)");
    printf("  Line:    %d\n", token->line);
    printf("  Column:  %d\n", token->column);
    printf("}\n");
}

// Print all tokens from TokenArray
void print_all_tokens_from_array(TokenArray* arr) {
    if (!arr) {
        printf("Token array is NULL\n");
        return;
    }
    
    printf("=== TOKEN LIST ===\n");
    printf("%-15s | %-20s | Position\n", "Type", "Lexeme");
    printf("----------------+----------------------+-----------\n");
    
    for (int i = 0; i < arr->count; i++) {
        if (arr->tokens[i] != 0) {
            print_token(arr->tokens[i]);
        }
    }
    
    printf("\nTotal tokens: %d (Capacity: %d)\n", arr->count, arr->capacity);
}

// Print all tokens (for compatibility)
void print_all_tokens() {
    if (!global_token_array) {
        printf("No tokens available\n");
        return;
    }
    print_all_tokens_from_array(global_token_array);
}

// Print tokens with filtering - commented out TOKEN_NEWLINE and TOKEN_COMMENT for now
void print_tokens_filtered(TokenArray* arr) {
    if (!arr) {
        printf("Token array is NULL\n");
        return;
    }
    
    printf("=== FILTERED TOKEN LIST ===\n");
    printf("%-20s | %-20s | Position\n", "Type", "Lexeme");
    printf("-------------------+----------------------+-----------\n");
    
    int printed = 0;
    for (int i = 0; i < arr->count; i++) {
        if (arr->tokens[i] != 0 && 
            arr->tokens[i]->type != TOKEN_WHITESPACE) {
            // Add these back if you have these token types:
            // && arr->tokens[i]->type != TOKEN_NEWLINE
            // && arr->tokens[i]->type != TOKEN_COMMENT) {
            print_token(arr->tokens[i]);
            printed++;
        }
    }
    
    printf("\nFiltered tokens: %d (out of %d total)\n", printed, arr->count);
}

// Print tokens as they would appear in source
void print_tokens_as_source(TokenArray* arr) {
    if (!arr) {
        printf("Token array is NULL\n");
        return;
    }
    
    printf("=== SOURCE RECONSTRUCTION ===\n");
    for (int i = 0; i < arr->count; i++) {
        if (arr->tokens[i] != 0 && arr->tokens[i]->lexeme != 0) {
            printf("%s", arr->tokens[i]->lexeme);
        }
    }
    printf("\n");
}

// Print token statistics
void print_token_stats(TokenArray* arr) 
{
    if (!arr) 
    {
        printf("Token array is NULL\n");
        return;
    }
    
    int counts[50] = {0}; // Adjust size based on your token types
    
    for (int i = 0; i < arr->count; i++) {
        if (arr->tokens[i] != 0 && arr->tokens[i]->type < 50) {
            counts[arr->tokens[i]->type]++;
        }
    }
    
    printf("=== TOKEN STATISTICS ===\n");
    for (int i = 0; i < 50; i++) {
        if (counts[i] > 0) {
            printf("%-20s: %d\n", tokentype_to_string((TokenType)i), counts[i]);
        }
    }
    printf("Total: %d tokens\n", arr->count);
}

// Debug function - removed length field access, use strlen instead
void print_token_debug(Token* token) {
    if (token == 0) {
        printf("NULL TOKEN\n");
        return;
    }
    
    int lexeme_length = token->lexeme ? strlen(token->lexeme) : 0;
    
    printf("=== TOKEN DEBUG ===\n");
    printf("Type: %s\n", tokentype_to_string(token->type));
    printf("Lexeme: \"%s\"\n", token->lexeme ? token->lexeme : "(null)");
    printf("Length: %d\n", lexeme_length);
    printf("Position: Line %d, Column %d\n", token->line, token->column);
    
    if (token->lexeme != 0) {
        printf("Hex dump: ");
        for (int i = 0; i < lexeme_length && i < 32; i++) {
            printf("%02x ", (unsigned char)token->lexeme[i]);
        }
        printf("\n");
        
        printf("ASCII:    ");
        for (int i = 0; i < lexeme_length && i < 32; i++) {
            char c = token->lexeme[i];
            printf("%c  ", (c >= 32 && c <= 126) ? c : '.');
        }
        printf("\n");
    }
}

// Convenience functions for global array
void print_tokens_filtered_global() {
    print_tokens_filtered(global_token_array);
}

void print_tokens_as_source_global() {
    print_tokens_as_source(global_token_array);
}

void print_token_stats_global() {
    print_token_stats(global_token_array);
}