#ifndef AST_H_ 
#define AST_H_

#include "token.h"
#include "parser.h"


// forward declaration of ASTNode
typedef struct ASTNode ASTNode;

typedef struct
{
    char* name;
} Identifier;

typedef struct
{
    char* literal_value;
} Literal;

typedef enum
{
    OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD,
    OP_LT, OP_GT, OP_LE, OP_GE, OP_EQ, OP_NE,
    OP_AND, OP_OR,
    OP_ASSIGN, OP_PLUS_ASSIGN, OP_MINUS_ASSIGN,
    OP_POS, OP_NEG, OP_NOT, OP_BITNOT
} Operator;

typedef struct
{
    union
    {
        Literal literal;
        Identifier ident;
        // or another expression
    };
} PrimaryExpr;

typedef struct
{
    Token op;
    ASTNode* left;
    ASTNode* right;
} BinaryExpr;

typedef struct
{
    Token op;
    PrimaryExpr operand;
} UnaryExpr;

typedef struct
{
    char* lhs;  // identifier
    Operator op; // =, +=, -=, etc
    ASTNode *rhs;  // as as value in variable declaration
} AssignExpr;

typedef struct
{
    Token op; // valid-> *, / and %
    PrimaryExpr** operands;   // list of primary expressions to  multiply
} MultExpr;

typedef struct
{
    int start;
    int stop;
} RangeExpr;

typedef struct
{
    char* array_name;
    int int_literal;
} IndexExpr;

typedef struct
{
    char* variable_name;
    char* typename;
    struct ASTNode* value;
} VarDeclaration;

typedef struct
{
    char* variable_name;
    char* typename;
    struct ASTNode* value;
} ConstDeclaration;

typedef struct
{
    char* name;
    char* return_type;
    ASTNode** params;   // parameters stored in an array
    int param_count;
    ASTNode* body;
} FuncDeclaration;

typedef struct
{
    ASTNode** stmts;
    int stmt_count;
} Block;

typedef struct
{
    ASTNode* condition;
    ASTNode* then_branch;
    ASTNode* else_branch;
} IfStmt;

typedef struct
{
    ASTNode* condition;
    ASTNode* body;
} LoopStmt;


typedef enum 
{
    MULT_EXPR,
    ADD_EXPR,
    RELATIONAL_EXPR,
    LOGICAL_EXPR,
    ASSIGN_EXPR,
    VAR_DECL,
    CONST_DECL,
    FUNC_DECL, 
    IF_STMT,
    LOOP_STMT,
    RETURN_STMT,
    BINARY_STMT,
    UNARY_STMT,
    LITERAL_STMT,
    BLOCK_STMT,
    CASE_STMT,
} ASTNodeType;

struct ASTNode
{
    ASTNodeType type;
    union
    {
        VarDeclaration VarDeclaration;
        ConstDeclaration ConstDeclaration;
        FuncDeclaration FuncDeclaration;
        IfStmt IfStmt;
        LoopStmt LoopStmt;
        AssignExpr assign_expr;
        BinaryExpr binary_expr;
        UnaryExpr unary_expr;
        PrimaryExpr primary_expr;
        MultExpr mult_expr;
        Block block;
        // add more
    };
};

// ========= function prototypes ============ //
ASTNode* parse_var_declaration();
ASTNode* parse_const_declaration();
ASTNode* parse_func_declaration();

ASTNode* parse_if_stmt();
ASTNode* parse_loop_stmt();
ASTNode* parse_return_stmt();

ASTNode *parse_primary_expr();
ASTNode *parse_unary_expr();
ASTNode *parse_mult_expr();
ASTNode *parse_add_expr();
ASTNode *parse_relation_expr();
ASTNode *parse_logical_expr();
ASTNode *parse_assign_expr();
ASTNode *parse_expr();

ASTNode *parse_index_expr();
ASTNode *parse_func_call();
ASTNode *parse_range();

#endif