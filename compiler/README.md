#### Syntax and Grammar definition

Declarations
<var_declaration> ->  <ident> : <type> = <literal> e.g count: int = 2;
<const_declaration> -> <ident> : const <type> = <literal> e.g const PI: float = 3.142;
<import_declaration> -> import “<string_literal>” e.g import "Pencil";

functions
<param_list> → (<ident> : <type>)* e.g (a: int, b: str)
<function_declaration> → fn <ident> (<param_list>) → <return_type> { <block> }
e.g fn add(a:int, b:int) -> int {}

Pattern Matching
<pattern> → _ | Some(<expr>) | Ok(<expr>) | Error(<expr>) | <literal> 
   case <pattern> : <literal> => <stmt>
                |   <literal> => <stmt>
                |   _ => <stmt>
e.g case value:
        0 => "zero"
        10 => "ten"
        100 => "hundred"
        _ => "empty"

Statements
<stmt> = <expr> | <stmt_list> 
e.g area: int = len * breadth
<stmt_list> = <stmt>+
<block> = <stmt_list>
<return_stmt> = (<literal> | <ident>)*
e.g area
    0
    -1
<if_stmt> →  if (<logical_expr>) { <stmt> | <stmt_list> | <block> }
e.g if (a > b) {}
<loop_stmt> → loop(<logical_expr> | <int_literal>) { <block> }
loop (1) {}
loop (a != 10) {}

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
<assign_op> → = | += | -= | *= |  /= | %=

Expressions
<expr> → <assign_expr> | <logical_expr> | <arithmetic_expr> | <equality_expr> | <relation_expr> | <unary_expr> | <func_call> | <index>

<assign> → <var_declaration> | <const_declaration>
<logical_expr> →  <expr> <logical_op> <expr> |<unary_expr>
<arithmetic_op> → <int_literal> <arithmetic_op> <int_literal>
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
<literal> = ...
<decimal_literal>  = [-|+]<digit>+
<binary_literal> = 0b<(0|1)+>
<hex_literal> = 0x<(0|1|2|3|4|5|6|7|8|9|A|B|C|D|E|F)+>
<octal_literal> = 0x<(0|1|2|3|4|5|6|7)+>
<float_literal> = <digit>+ , <dot> , <digit>+ 
<string_literal> = “ , <letter>+, “
<char_literal> = ‘ , <letter>, ‘
<bool_literal> = True | False


Whitespace and Comments
<whitespace> = “ “
<line_comment> = // , <string>*, <esc>
<block_comment> = /*, <string> , */

Types
primitive types: short, char, int, long, float, double bit, byte, word
1. Type <type> = Int | Float | <array> | <struct> | <enum>
2. Array <array> →  <ident>:<type> = [<literal>+]
3. Struct
<struct> → struct <ident>{ (<ident>:<type> = [literal, literal*] )+ }
4. enum <ident> : <ident>+
5. implements -> definition of functions that can be used only on specified data(s) e.g
implements User, Group {
    fn function0() {}
    fn function1() {}
    fn function2() {}
}

## Punctuators

## Keywords
int
short
float
double
char
long
byte
string
struct
enum
if
else
match
case
loop
signed
unsigned


## Strings
An array of characters with a terminating character \0. Enclosed in double quotes. Strings declare their length before use.
## Operators
Symbols that trigger an execution on one or more data values.
## Identifiers
Names given to variables, functions, arrays, other user-defined elements. Begin with a letter or an underscore but not a digit.
## Constants
These values do not change throunghout a programs lifetime


