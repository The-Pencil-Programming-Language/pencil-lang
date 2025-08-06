Sure! Here’s a detailed **parser pseudocode** and explanation for your simple programming language, based on the grammar you provided. We'll build a **recursive descent parser** because it is:

* **Simple to write**
* **Easy to understand**
* **Perfect for small and well-structured languages like yours**

---

## ✅ OVERVIEW OF PARSING STEPS

**Parsing Process Summary**:

1. **Lexical Analysis (Tokenization)**: Convert source code into a stream of tokens.
2. **Parsing (Syntax Analysis)**: Match token stream against grammar rules to build an **Abstract Syntax Tree (AST)**.
3. **Error Handling**: Detect and report unexpected tokens or malformed input.
4. **AST Construction**: Build nodes for expressions, statements, and declarations.

We will walk through each part now.

---

## 🧩 TOKENS (assumed)

```text
Token types:
- IDENTIFIER
- NUMBER, FLOAT, STRING, CHAR, BOOL
- KEYWORDS: const, import, if, else, while, return, true, false
- SYMBOLS: + - * / % = == != < <= > >= && || ! ~ ^ << >> ( ) [ ] { } , ; : =>

Token structure:
Token {
    type: TokenType
    value: string
    line: int
    column: int
}
```

---

## 🧠 RECURSIVE DESCENT PARSER PSEUDOCODE

```pseudocode
class Parser:
    tokens: list of Token
    current: int = 0

    function parse_program():
        statements = []
        while not is_at_end():
            statements.append(parse_statement())
        return ProgramNode(statements)

    function parse_statement():
        if match("const"):
            return parse_const_declaration()
        if match("import"):
            return parse_import_declaration()
        if check_next(":"):
            return parse_var_declaration()
        if match("if"):
            return parse_if_statement()
        if match("while"):
            return parse_while_statement()
        if match("return"):
            return parse_return_statement()
        return parse_expression_statement()

    function parse_var_declaration():
        name = consume(IDENTIFIER, "Expected variable name")
        consume(":", "Expected ':' after variable name")
        typ = consume(TYPE, "Expected type")
        if match("="):
            value = parse_expression()
        else:
            value = null
        consume(";", "Expected ';' after variable declaration")
        return VarDeclNode(name, typ, value)

    function parse_const_declaration():
        name = consume(IDENTIFIER, "Expected constant name")
        consume(":", "Expected ':' after constant name")
        typ = consume(TYPE, "Expected type")
        if match("="):
            value = parse_expression()
        else:
            value = null
        consume(";", "Expected ';' after const declaration")
        return ConstDeclNode(name, typ, value)

    function parse_import_declaration():
        path = consume(STRING, "Expected module path")
        consume(";", "Expected ';' after import")
        return ImportNode(path)

    function parse_expression_statement():
        expr = parse_expression()
        consume(";", "Expected ';' after expression")
        return ExprStmtNode(expr)

    function parse_expression():
        return parse_assignment()

    function parse_assignment():
        expr = parse_logical_or()
        if match("=", "+=", "-=", "*=", "/=", "%="):
            operator = previous()
            value = parse_assignment()
            if expr is VariableNode:
                return AssignmentNode(expr.name, operator, value)
            error("Invalid assignment target")
        return expr

    function parse_logical_or():
        expr = parse_logical_and()
        while match("||"):
            operator = previous()
            right = parse_logical_and()
            expr = LogicalExprNode(expr, operator, right)
        return expr

    function parse_logical_and():
        expr = parse_equality()
        while match("&&"):
            operator = previous()
            right = parse_equality()
            expr = LogicalExprNode(expr, operator, right)
        return expr

    function parse_equality():
        expr = parse_comparison()
        while match("==", "!="):
            operator = previous()
            right = parse_comparison()
            expr = BinaryExprNode(expr, operator, right)
        return expr

    function parse_comparison():
        expr = parse_term()
        while match("<", "<=", ">", ">="):
            operator = previous()
            right = parse_term()
            expr = BinaryExprNode(expr, operator, right)
        return expr

    function parse_term():  // + and -
        expr = parse_factor()
        while match("+", "-"):
            operator = previous()
            right = parse_factor()
            expr = BinaryExprNode(expr, operator, right)
        return expr

    function parse_factor():  // * / %
        expr = parse_unary()
        while match("*", "/", "%"):
            operator = previous()
            right = parse_unary()
            expr = BinaryExprNode(expr, operator, right)
        return expr

    function parse_unary():
        if match("!", "-", "~"):
            operator = previous()
            right = parse_unary()
            return UnaryExprNode(operator, right)
        return parse_primary()

    function parse_primary():
        if match(NUMBER, FLOAT, STRING, CHAR, BOOL):
            return LiteralNode(previous().value)
        if match(IDENTIFIER):
            if match("("):  // function call
                args = []
                if not check(")"):
                    do:
                        args.append(parse_expression())
                    while match(",")
                consume(")", "Expected ')' after arguments")
                return FuncCallNode(previous().value, args)
            return VariableNode(previous().value)
        if match("("):
            expr = parse_expression()
            consume(")", "Expected ')' after expression")
            return GroupingNode(expr)
        error("Expected expression")
```

---

## 💡 SUPPORTING FUNCTIONS

```pseudocode
function match(...types):
    for type in types:
        if check(type):
            advance()
            return true
    return false

function check(type):
    if is_at_end(): return false
    return peek().type == type

function check_next(sym):
    return peek(1).type == sym

function consume(type, message):
    if check(type): return advance()
    error(message)

function advance():
    if not is_at_end(): current += 1
    return previous()

function is_at_end():
    return peek().type == EOF

function peek(offset = 0):
    return tokens[current + offset]

function previous():
    return tokens[current - 1]
```

---

## 🧱 AST NODE EXAMPLES

You’ll likely have AST nodes like:

```text
ProgramNode(statements)
VarDeclNode(name, type, value)
ConstDeclNode(name, type, value)
AssignmentNode(name, operator, value)
BinaryExprNode(left, operator, right)
UnaryExprNode(operator, operand)
FuncCallNode(name, arguments)
LiteralNode(value)
VariableNode(name)
```

---

## ✅ Final Notes

* **The parser assumes the tokenizer is already done**.
* The **main entry point** is `parse_program()` which returns a full AST.
* You can **expand** this to include more features (e.g., structs, classes, switch-case) later.
* Error handling is simplified here but should be improved for line/column tracking.

---

Would you like the **tokenizer pseudocode**, **AST evaluator**, or a **Python implementation** of this parser next?
