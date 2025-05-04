#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

// Token types
typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_KEYWORD,
    TOKEN_OPERATOR,
    TOKEN_EOF,
    TOKEN_INVALID
} TokenType;

// Keyword list for recognizing keywords
const char *keywords[] = {
    "if", "else", "while", "for", "return", NULL
};

// Function to check if a word is a keyword
int is_keyword(const char *str) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to print token information
void print_token(TokenType type, const char *value) {
    switch (type) {
        case TOKEN_IDENTIFIER:
            printf("Identifier: %s\n", value);
            break;
        case TOKEN_NUMBER:
            printf("Number: %s\n", value);
            break;
        case TOKEN_KEYWORD:
            printf("Keyword: %s\n", value);
            break;
        case TOKEN_OPERATOR:
            printf("Operator: %s\n", value);
            break;
        case TOKEN_INVALID:
            printf("Invalid token: %s\n", value);
            break;
        case TOKEN_EOF:
            printf("End of file\n");
            break;
    }
}

// Function to handle reading numbers
int read_number(FILE *file, char *buffer) {
    int i = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF && isdigit(ch)) {
        buffer[i++] = ch;
    }
    buffer[i] = '\0';  // Null terminate the string
    return ch;
}

// Function to handle reading identifiers and keywords
int read_identifier(FILE *file, char *buffer) {
    int i = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF && (isalnum(ch) || ch == '_')) {
        buffer[i++] = ch;
    }
    buffer[i] = '\0';  // Null terminate the string
    return ch;
}

// Function to handle reading operators
int read_operator(FILE *file, char *buffer) {
    int ch = fgetc(file);
    if (ch != EOF) {
        buffer[0] = ch;
        buffer[1] = '\0';  // Null terminate the string
    }
    return ch;
}

// Main function to perform scanning
void tokenize(FILE *file) {
    int ch;
    char buffer[MAX_TOKEN_LENGTH];
    TokenType token_type;

    while ((ch = fgetc(file)) != EOF) {
        // Skip whitespace and comments
        if (isspace(ch)) {
            continue;
        }

        // Handle comments (C-style comments)
        if (ch == '/' && (ch = fgetc(file)) == '/') {
            // Skip till end of line for single-line comments
            while ((ch = fgetc(file)) != EOF && ch != '\n');
            continue;
        } else if (ch == '/' && ch == '*') {
            // Skip till end of block comment
            while ((ch = fgetc(file)) != EOF && !(ch == '*' && (ch = fgetc(file)) == '/'));
            continue;
        }

        // If the character is a number, read the full number
        if (isdigit(ch)) {
            buffer[0] = ch;
            if (read_number(file, buffer + 1) != EOF) {
                token_type = TOKEN_NUMBER;
                print_token(token_type, buffer);
                continue;
            }
        }

        // If the character is part of an identifier, read the identifier
        if (isalpha(ch) || ch == '_') {
            buffer[0] = ch;
            if (read_identifier(file, buffer + 1) != EOF) {
                token_type = is_keyword(buffer) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
                print_token(token_type, buffer);
                continue;
            }
        }

        // If the character is an operator
        if (ispunct(ch)) {
            buffer[0] = ch;
            read_operator(file, buffer + 1);
            token_type = TOKEN_OPERATOR;
            print_token(token_type, buffer);
            continue;
        }

        // If we encounter an invalid character
        buffer[0] = ch;
        buffer[1] = '\0';
        print_token(TOKEN_INVALID, buffer);
    }

    // Print end-of-file token
    print_token(TOKEN_EOF, "");
}

int main() {
    // Open a file for reading
    FILE *file = fopen("README.md", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Call the tokenize function
    tokenize(file);

    // Close the file
    fclose(file);
    return 0;
}
