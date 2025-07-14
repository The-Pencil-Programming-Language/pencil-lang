#### Syntax and Grammar definition

Declarations
<var_declaration> =  var <ident> : <type> = <literal>
<const_declaration> = let <ident> : <type> = <literal>
<import_declaration> = import,  “<string_literal>”

functions
<param_list> → (<ident>:<type>)*
<function_declaration> → 
fn , <ident>, (, <param_list>, ), →  <return_type> { <block> }

Pattern Matching
<pattern> → _ | Some(<expr>) | Ok(<expr>) | Error(<expr>) | <literal> 
<match_stmt> →  match <expr> { <case>+: (<pattern> => <stmt>) + }

Statements
<stmt> = <expr> | <stmt_list> 
<stmt_list> = <stmt>+
<block> = <stmt_list>
<return_stmt> = return (<literal> | <ident>)*
<if_stmt> →  if (<logical_expr>) { <stmt> | <stmt_list> | <block> }
<loop_stmt> → loop(<logical_expr> | <int_literal>) { <block> }
<break_stmt> = break <esc>
<continue_stmt> = continue <esc>

Operators
<arithmetic_op> = <add_op> | <mult_op> | <rem_op>
<mult_op> = * | /
<add_op> = + | -
<rem_op> = %
<underscore> = _
<esc> = \n | \t | \r
<dot> = . 
<increment_op> = ++
<decrement_op> = --
<logical_op> = && | || | !
<bitwise_op> = &, |, ^, ~, >>, <<
<comparison_op> → == | != | > | < | <= | >= | is | in
<assign_op> → = | += |  -= | *= |  /= | %=

Expressions
<expr> → <assign_expr> | <logical_expr> | <arithmetic_expr> | <equality_expr> | <relation_expr> | <unary_expr> | <func_call> | <index>

<assign> → <var_declaration> | <const_declaration>
<logical_expr> →  (<expr>) <logical_op> (<expr>)
<arithmetic_op> → (<expr>) <arithmetic_op> (<expr>)
<equality_expr> → <expr> <comparison_op> <expr>
<relation_expr> → <expr> <relation_op> <expr>
<unary_expr> → <op> <ident>
<index> → <array_name>[<int_literal>]
<func_call> → <func_name>(<arg_list>)

Characters
<digit> = 0 | 1| 2| 3 | 4 | 5 | 6 | 7 | 8 | 9
<lower_case> = a..z
<upper_case> = A..Z
<letter> = <upper_case> | <lower_case>

Identifier
<ident> = <letter>+ | ( <letter> | <digit> | _)*

Literals
<literal> = …. 
<int_literal>  = [-|+]<digit>+
<binary_literal> = 0b<(0|1)+>
<binary_literal> = 0x<(0|1|2|3|4|5|6|7|8|9|A|B|C|D|E|F)+>
<binary_literal> = 0x<(0|1|2|3|4|5|6|7)+>
<float_literal> = <digit>+ , <dot> , <digit>+ 
<string_literal> = “ , <letter>+, “
<char_literal> = ‘ , <letter>, ‘
<bool_literal> = True | False
<null> = Nil

Whitespace and Comments
<whitespace> = “ “
<line_comment> = // , <string>*, <esc>
<block_comment> = /*, <block> , */

Types
primitive types: short, char, int, long, float, double bit, byte, word
1. Type <type> = Int | Float | <array> | <struct> | <enum>
2. Array <array> →  <ident>:<type> = [<literal>+]
3. Struct
<struct> →struct <ident>{ (<ident>:<type> = [literal, literal*] )+ }
4. enum <ident> : <ident>+


## Punctuators
## Keywords
int
float
double
char
string
struct
enum
if
else
match
case
loop
return
## Strings
An array of characters with a terminating character \0. Enclosed in double quotes.
## Operators
Symbols that trigger an execution on one or more data
## Identifiers
Names given to variables, functions, arrays, other user-defined elements. Begin with a letter or an underscore but not a digit.
## Constants
values do not change.



## Tokens
c lang tokens - https://www.geeksforgeeks.org/tokens-in-c/

