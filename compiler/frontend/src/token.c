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
    "char",
    "str", 
    "float",  
    "break",
    "continue",
    "fn",
    "main",
    "impl",
    "const"
};

TokenType keyword_to_token(char *keyword)
{
    if (strcmp(keyword, "if") == 0) return IF;
    else if (strcmp(keyword, "else") == 0) return ELSE;
    else if (strcmp(keyword, "loop") == 0) return LOOP;
    else if (strcmp(keyword, "for") == 0) return FOR;
    else if (strcmp(keyword, "case") == 0) return CASE;
    else if (strcmp(keyword, "import") == 0) return IMPORT;
    else if (strcmp(keyword, "struct") == 0) return STRUCT;
    else if (strcmp(keyword, "enum") == 0) return ENUM;
    else if (strcmp(keyword, "break") == 0) return BREAK;
    else if (strcmp(keyword, "continue") == 0) return CONTINUE;
    else if (strcmp(keyword, "fn") == 0) return FN;
    else if (strcmp(keyword, "main") == 0) return MAIN;
    else if (strcmp(keyword, "str") == 0) return TYPE;
    else if (strcmp(keyword, "char") == 0) return TYPE;
    else if (strcmp(keyword, "int") == 0) return TYPE;
    else if (strcmp(keyword, "long") == 0) return TYPE;
    else if (strcmp(keyword, "float") == 0) return TYPE;
    else if (strcmp(keyword, "const") == 0) return CONST;
    else return UNKNOWN;
}


const char* tokentype_to_string(TokenType type) 
{
    switch (type) {
        case IF: return "IF";
        case ELSE: return "ELSE";
        case FOR: return "FOR";
        case LOOP: return "LOOP";
        case BREAK: return "BREAK";
        case CONTINUE: return "CONTINUE";
        case CASE: return "CASE";

        case FN: return "FN";
        case MAIN: return "MAIN";

        case STRUCT: return "STRUCT";
        case ENUM: return "ENUM";
        case TYPE: return "TYPE";
        case CONST: return "CONST";
        case IMPORT: return "IMPORT";

        case INT_LITERAL: return "INT_LITERAL";
        case FLOAT_LITERAL: return "FLOAT_LITERAL";
        case CHAR_LITERAL: return "CHAR_LITERAL";
        case BOOL_LITERAL: return "BOOL_LITERAL";
        case HEX_LITERAL: return "HEX_LITREAL";
        case OCTAL_LITERAL: return "OCTAL_LITREAL";
        case BINARY_LITERAL: return "BINARY_LITREAL";
        case STRING_LITERAL: return "STRING_LITERAL";

        case WHITESPACE: return "WHITESPACE";
        case IDENTIFIER: return "IDENTIFIER";
        case KEYWORD: return "KEYWORD";

        case LBRACKET: return "LBRACKET";
        case RBRACKET: return "RBRACKET";
        case LCURLY: return "LCURLY";
        case RCURLY: return "RCURLY";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case SEMICOLON: return "SEMICOLON";
        case COLON: return "COLON";
        case COMMA: return "COMMA";
        case QUOTE: return "QUOTE";
        case DOUBLE_QUOTE: return "DOUBLE_QUOTE";
        case DOT: return "DOT";
        case ARROW: return "ARROW";

        case TOKEN_EOF: return "EOF";

        case NEW: return "NEW";
        case DROP: return "DROP";

        case PLUS: return "PLUS";
        case PLUS_PLUS: return "PLUS_PLUS";
        case MINUS: return "MINUS";
        case MINUS_MINUS: return "MINUS_MINUS";
        case STAR: return "STAR";
        case SLASH: return "SLASH";
        case PERCENT: return "PERCENT";

        case EQUAL: return "EQUAL";
        case NOT_EQUAL: return "NOT_EQUAL";
        case LESS: return "LESS";
        case LESS_EQUAL: return "LESS_EQUAL";
        case GREATER: return "GREATER";
        case GREATER_EQUAL: return "GREATER_EQUAL";

        case AND: return "AND";
        case OR: return "OR";
        case NOT: return "NOT";

        case BITWISE_AND: return "BITWISE_AND";
        case BITWISE_OR: return "BITWISE_OR";
        case BITWISE_XOR: return "BITWISE_XOR";
        case BITWISE_NOT: return "BITWISE_NOT";
        case LSHIFT: return "LSHIFT";
        case RSHIFT: return "RSHIFT";

        case ASSIGN: return "ASSIGN";
        case PLUS_ASSIGN: return "PLUS_ASSIGN";
        case MINUS_ASSIGN: return "MINUS_ASSIGN";
        case STAR_ASSIGN: return "STAR_ASSIGN";
        case SLASH_ASSIGN: return "SLASH_ASSIGN";
        case PERCENT_ASSIGN: return "PERCENT_ASSIGN";

        default: return "UNKNOWN_TYPE";
    }
}

// Create a new token array
TokenArray* create_array() {
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
void add_to_array(TokenArray* arr, TokenType type, const char* lexeme, int length, int line, int column) {
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
TokenArray* global_array = 0;  // Use 0 instead of NULL for C99 compatibility

void init_global_array() {
    if (!global_array) {
        global_array = create_array();
    }
}

// Wrapper function that matches your lexer's add_token signature
void add_token(TokenType type, const char* lexeme, int length, int line, int column) {
    if (!global_array) {
        init_global_array();
    }
    add_to_array(global_array, type, lexeme, length, line, column);
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

void free_array(TokenArray* arr) {
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
void print_detailed(Token* token) {
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
    if (!global_array) {
        printf("No tokens available\n");
        return;
    }
    print_all_tokens_from_array(global_array);
}

// Print tokens with filtering - commented out NEWLINE and COMMENT for now
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
            arr->tokens[i]->type != WHITESPACE) {
            // Add these back if you have these token types:
            // && arr->tokens[i]->type != NEWLINE
            // && arr->tokens[i]->type != COMMENT) {
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
void print_stats(TokenArray* arr) 
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
void print_debug(Token* token) {
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
    print_tokens_filtered(global_array);
}

void print_tokens_as_source_global() {
    print_tokens_as_source(global_array);
}

void print_stats_global() {
    print_stats(global_array);
}