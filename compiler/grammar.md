## ** Operators **
<add_op>          = "+" | "-"
<mult_op>         = "*" | "/"
<rem_op>          = "%"
<arithmetic_op>   = <add_op> | <mult_op> | <rem_op>

<increment_op>    = "++"
<decrement_op>    = "--"

<logical_op>      = "&&" | "||" | "!"
<bitwise_op>      = "&" | "|" | "^" | "~" | ">>" | "<<"
<comparison_op>   = "==" | "!=" | ">" | "<" | ">=" | "<=" 
<assign_op>       = "=" | "+=" | "-=" | "*=" | "/=" | "%=" | "/="
<arrow_op>        = "=>"
<optional_op>     = "?"

<dot>             = "."
<underscore>      = "_"
<esc>             = "\n" | "\t" | "\r"

## ** Characters **
<digit>           = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<lower_case>      = "a" .. "z"
<upper_case>      = "A" .. "Z"
<letter>          = <lower_case> | <upper_case>

## ** Literals **
<decimal_literal> = ["+" | "-"] <digit>+
<binary_literal>  = "0b" ("0" | "1")+
<hex_literal>     = "0x" ("0".."9" | "A".."F")+
<octal_literal>   = "0o" ("0".."7")+
<float_literal>   = <digit>* "." <digit>+

<string_literal>  = "\"" (<letter> | <digit> | " " | <esc>)* "\""
<char_literal>    = "'" <letter> "'"
<bool_literal>    = "true" | "false"
<literal>         = <decimal_literal> | <float_literal> | <binary_literal> |
                   <hex_literal> | <octal_literal> | <string_literal> |
                   <char_literal> | <bool_literal>

## ** Whitespace and Comments **
<whitespace>      = " " | <esc>
<line_comment>    = "//" (any character)* <esc>
<block_comment>   = "/*" (any character)* "*/"

## ** Identifier **
<ident> = <letter> (<letter> | <digit> | "_")*

## ** Expressions **
<primary_expr>    = <literal> | <ident> | "(" <expr> ")"
<unary_expr>      = ("+" | "-" | "!" | "~") <primary_expr>
<mult_expr>       = <unary_expr> (("*" | "/" | "%") <unary_expr>)*
<add_expr>        = <mult_expr> (("+" | "-") <mult_expr>)*
<relation_expr>   = <add_expr> (<comparison_op> <add_expr>)*
<logical_expr>    = <relation_expr> (<logical_op> <relation_expr>)*
<assign_expr>     = <ident> <assign_op> <expr>
<expr>            = <assign_expr> | <logical_expr> | <add_expr>

<index_expr>      = <ident> "[" <expr> "]"
<func_call>       = <ident> "(" [<expr> ("," <expr>)*] ")"
<range>           = <digit> "..." <digit>

## 📐 **Operator Precedence (High → Low)**

1. Parentheses: `()`
2. Unary operators: `+ - ! ~`
3. Multiplicative: `* / %`
4. Additive: `+ -`
5. Comparison: `== != > < >= <=`
6. Logical: `&& ||`
7. Assignment: `= += -= *= /= %=`


## ** Declaractions **

<var_declaration>   = <ident> ":" <type> ["=" <literal>] ";"
<const_declaration> = "const" <ident> ":" <type> ["=" <literal>] ";"
<import_declaration> = "import" <string_literal> ";"

## ** Data Structures **
<array> = <ident> ":" <type> "[" [<digit>] "]" ["=" (<literal>)* ] ";"
<struct> = "struct" "{" (<var_declaration>)* "}" ";"
<enum> = "enum" "{" (<identifier>)* "}" ";"
<vector> = "vec" "[" "]" ";"

## ** Types **
<type> = "int" | "float" | "bool" | "char" | "str" | <user-defined-type>

## ** Statements **
<statement> =
      <var_declaration>
    | <const_declaration>
    | <expr> ";"
    | <func_call> ";"
    | <if_statement>
    | <loop_statement>
    | <return_statement>


## 🔁 **Control Structures **

<if_statement> = "if" "(" <expr> ")" "{" <statement>* "}" ["else" "{" <statement>* "}"]
<case_statement> = "case" <pattern> "{" =
    (<ident> <arrow> <statement> ";")*
    <underscore> <arrow> <statement> ";"
"}"

<loop_statement> = "loop" "{" <statement>* "}"
<for_statement> = "for" "(" <expr> ")" "{" <statement>* "}"
<return_statement> = "return" [<expr>] ";"















