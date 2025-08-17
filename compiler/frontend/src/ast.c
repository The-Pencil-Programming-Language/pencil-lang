#include "ast.h"
#include "parser.h"
#include "token.h"
#include <stdlib.h>


// <var_declaration>   = <ident> ":" <type> ["=" <literal>] ";"
// ASTNode* parse_var_declaration(Parser* parser)
// {
//     // allocate space for the node
//     ASTNode* node = (ASTNode *)malloc(sizeof(ASTNode));
    
//     node->type = VAR_DECL;  // set the type of ast node

//     // Token name = parser->tokens[parser->current];
//     // if (!expect(parser, IDENTIFIER, "\nExpected identifier.")) {
//     //     // handle error
//     // }

//     Token name = expect(parser, IDENTIFIER, "\nExpected identifier.");
//     expect(parser, COLON, "\nExpected : after identifier.");

//     Token type_name = expect(parser, TYPE, "\nExpected type.");
//     expect(parser, ASSIGN, "\nExpected '='. ");

//     ASTNode* value = NULL;

//     if (match(parser, ASSIGN))
//     {
//         ASTNode* value = parse_expersion(parser);
//     }
 
//     expect(parser, SEMICOLON, "\nExpected ';' after variable declaration.");

//     node->VarDeclaration.variable_name = name.lexeme;    // name is the token object, see token.h for the fields in the token struct
//     node->VarDeclaration.typename = type_name.lexeme;   // same as above
//     node->VarDeclaration.value = value;

//     return node;
// }
