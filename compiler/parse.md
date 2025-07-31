To implement a **parser** for the syntax and grammar you’ve defined above, you would follow the standard compiler design pipeline—specifically, the **parsing phase**—which comes after lexical analysis (tokenization). Your grammar is relatively clear, so we can focus on **how to build a recursive descent parser**, which is a common, simple, and human-readable parsing strategy suitable for the kind of grammar you've written.

---

## 🧩 Overview

### What You Have:

* A formal grammar for a small language (similar to Rust or Go).
* Syntax rules for declarations, expressions, control flow, and types.
* An operator and token list.

### What You Need:

* A **tokenizer (lexer)** — Converts source code into a stream of tokens.
* A **parser** — Consumes tokens and produces an **AST (Abstract Syntax Tree)**.
* A **recursive descent parser** — A top-down parser made of mutually recursive functions for each grammar rule.

---

## 🧱 Step-by-Step Parser Design

### 1. **Lexer/Tokenizer (Brief Overview)**

You’ll first tokenize the input source code into token objects:

```c
typedef enum {
    TOKEN_IDENT, TOKEN_INT_LITERAL, TOKEN_STRING_LITERAL, TOKEN_FLOAT_LITERAL,
    TOKEN_FN, TOKEN_IF, TOKEN_ELSE, TOKEN_LOOP, TOKEN_RETURN,
    TOKEN_PLUS, TOKEN_MINUS, TOKEN_STAR, TOKEN_SLASH, TOKEN_PERCENT,
    TOKEN_EQ, TOKEN_ASSIGN, TOKEN_ARROW, TOKEN_LPAREN, TOKEN_RPAREN,
    TOKEN_LBRACE, TOKEN_RBRACE, TOKEN_COLON, TOKEN_SEMICOLON,
    TOKEN_COMMA, TOKEN_EOF,
    // ... other tokens
} TokenType;

typedef struct {
    TokenType type;
    char* lexeme;
    int line;
    int column;
} Token;
```

---

### 2. **Parser Skeleton**

Create a parser with functions that mirror your grammar:

```c
typedef struct {
    Token* tokens;
    int current;
} Parser;
```

---

### 3. **Parser Utilities**

```c
Token peek(Parser* parser);
Token advance(Parser* parser);
bool match(Parser* parser, TokenType type);
bool expect(Parser* parser, TokenType type, const char* errorMessage);
```

---

### 4. **AST Nodes**

Define structs for AST nodes.

```c
typedef enum {
    AST_VAR_DECL,
    AST_CONST_DECL,
    AST_FUNC_DECL,
    AST_IF_STMT,
    AST_LOOP_STMT,
    AST_RETURN_STMT,
    AST_BINARY_EXPR,
    AST_UNARY_EXPR,
    AST_LITERAL,
    AST_BLOCK,
    // etc...
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    union {
        struct {
            char* name;
            char* typeName;
            struct ASTNode* value;
        } varDecl;

        struct {
            char* name;
            char* typeName;
            struct ASTNode* value;
        } constDecl;

        struct {
            char* name;
            struct ASTNode** params;
            int paramCount;
            char* returnType;
            struct ASTNode* body;
        } funcDecl;

        struct {
            Token op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binaryExpr;

        struct {
            Token op;
            struct ASTNode* operand;
        } unaryExpr;

        struct {
            char* literalValue;
        } literal;

        struct {
            struct ASTNode** stmts;
            int stmtCount;
        } block;

        // etc...
    };
} ASTNode;
```

---

### 5. **Parsing Functions (Recursive Descent)**

#### Example: Variable Declaration

```c
ASTNode* parse_var_declaration(Parser* parser) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_VAR_DECL;

    Token name = expect(parser, TOKEN_IDENT, "Expected identifier");
    expect(parser, TOKEN_COLON, "Expected ':'");
    Token typeName = expect(parser, TOKEN_IDENT, "Expected type name");
    expect(parser, TOKEN_ASSIGN, "Expected '='");
    ASTNode* value = parse_expression(parser);

    node->varDecl.name = name.lexeme;
    node->varDecl.typeName = typeName.lexeme;
    node->varDecl.value = value;

    return node;
}
```

#### Example: Function Declaration

```c
ASTNode* parse_function(Parser* parser) {
    expect(parser, TOKEN_FN, "Expected 'fn'");
    Token name = expect(parser, TOKEN_IDENT, "Expected function name");

    expect(parser, TOKEN_LPAREN, "Expected '('");

    // parse parameter list
    // param_list → (<ident> : <type>)*

    ASTNode** params = NULL;
    int paramCount = 0;
    if (!match(parser, TOKEN_RPAREN)) {
        do {
            Token paramName = expect(parser, TOKEN_IDENT, "Expected parameter name");
            expect(parser, TOKEN_COLON, "Expected ':'");
            Token typeName = expect(parser, TOKEN_IDENT, "Expected parameter type");

            // Store param node
            paramCount++;
        } while (match(parser, TOKEN_COMMA));

        expect(parser, TOKEN_RPAREN, "Expected ')'");
    }

    expect(parser, TOKEN_ARROW, "Expected '→'");
    Token returnType = expect(parser, TOKEN_IDENT, "Expected return type");

    ASTNode* block = parse_block(parser);

    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_FUNC_DECL;
    node->funcDecl.name = name.lexeme;
    node->funcDecl.returnType = returnType.lexeme;
    node->funcDecl.body = block;

    return node;
}
```

---

### 6. **Expression Parsing**

Use **precedence climbing** or **recursive descent with precedence levels** for:

```text
<expr> → <assign_expr> | <logical_expr> | <equality_expr> | <relation_expr> ...
```

Handle with layers:

```c
ASTNode* parse_expression(Parser* parser) {
    return parse_assignment(parser);
}

ASTNode* parse_assignment(Parser* parser) {
    ASTNode* left = parse_logical_or(parser);
    if (match(parser, TOKEN_ASSIGN)) {
        ASTNode* right = parse_assignment(parser);
        ASTNode* node = new_binary_expr_node(TOKEN_ASSIGN, left, right);
        return node;
    }
    return left;
}
```

---

### 7. **Control Flow**

#### If Statement

```c
ASTNode* parse_if(Parser* parser) {
    expect(parser, TOKEN_IF, "Expected 'if'");
    expect(parser, TOKEN_LPAREN, "Expected '('");
    ASTNode* condition = parse_expression(parser);
    expect(parser, TOKEN_RPAREN, "Expected ')'");
    ASTNode* thenBlock = parse_block(parser);

    // optionally handle 'else'
    return make_if_node(condition, thenBlock);
}
```

#### Loop Statement

```c
ASTNode* parse_loop(Parser* parser) {
    expect(parser, TOKEN_LOOP, "Expected 'loop'");
    expect(parser, TOKEN_LPAREN, "Expected '('");
    ASTNode* cond = parse_expression(parser);
    expect(parser, TOKEN_RPAREN, "Expected ')'");
    ASTNode* body = parse_block(parser);

    return make_loop_node(cond, body);
}
```

---

## 🧠 Final Notes

* **Parser construction mirrors grammar definition**: each non-terminal gets a function.
* **Error recovery** (optional) can be implemented by synchronizing after errors (e.g., skip to `;` or `}`).
* A **visitor pattern** or interpreter can then traverse the AST.

---

## ✅ Example Execution Order

```c
source code → tokenize() → tokens[]  
tokens[] → parse_program() → AST  
AST → execute or generate code
```

---

Would you like me to generate full C parser code or pseudo-code for each rule in your grammar next?
