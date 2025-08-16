#ifndef AST_H_ 
#define AST_H_

#include "token.h"
#include "parser.h"

typedef enum 
{
    AST_MULT_EXPR,
    AST_ADD_EXPR,
    AST_RELATIONAL_EXPR,
    AST_LOGICAL_EXPR,
    AST_ASSIGN_EXPR,
    AST_VAR_D,
    AST_CONST_D,
    AST_FUNC_D, 
    AST_IF_STMT,
    AST_LOOP_STMT,
    AST_RETURN_STMT,
    AST_BINARY_STMT,
    AST_UNARY_STMT,
    AST_LITERAL_STMT,
    AST_BLOCK_STMT,
    AST_CASE_STMT,
} ASTNodeType;

typedef struct
{
    ASTNodeType type;
    union
    {
       // add the type defintions above
    };
} ASTNode;

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
    Token op;
    ASTNode* left;
    ASTNode* right;
} BinaryExpr;

typedef struct
{
    Token op;
    ASTNode* operand;
} UnaryExpr;

typedef struct
{
    char* literal_value;
} Literal;

typedef struct
{
    ASTNode** stmts;
    int stmt_count;
} Block;

typedef struct
{
    char* name;
} Identifier;

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


#endif