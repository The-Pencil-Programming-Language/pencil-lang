#ifndef AST_H_ 
#define AST_H_

struct Node{
    Token type;
};

struct AST_H_{
    Node root;
};

typedef enum 
{
    VAR_DECLARATION;
    CONST_DECLARATION;
} AST_Type;



#endif