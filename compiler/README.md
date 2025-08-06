#### Syntax and Grammar definition
Declarations


functions
<param_list> → (<ident> : <type>)* e.g (a: int, b: str)
<function_declaration> → fn <ident> (<param_list>) → <return_type> { <block> }
e.g fn add(a:int, b:int) -> int {}

Pattern Matching
<pattern> → _ | Some(<expr>) | Ok(<expr>) | Error(<expr>) | <literal> 
   case <pattern> { <literal> => <stmt>
                |   <literal> => <stmt>
                |   _ => <stmt>
   }
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
str
struct
enum
if
else
case
loop
signed
unsigned
for
fn
true
false
typedef

u8, s8
u16, s16
u32, s32
u64, s64
f32, f64

## Strings
An array of characters with a terminating character \0. Enclosed in double quotes. Strings declare their length before use.
## Operators
Symbols that trigger an execution on one or more data values.
## Identifiers
Names given to variables, functions, arrays, other user-defined elements. Begin with a letter or an underscore but not a digit.
## Constants
These values do not change throunghout a programs lifetime


# Example program
## declaration
num: int = 5;
letter: char = 'Q';
rate: float = 0.05;

# if stmts
if (a == b) {
    a = 3;
} else if (a > b) {
    b = 2;
} else {
    a > b;
}

# ternary operator
!male ? "man" : "woman"

# pattern matching
case character {
    'a' => "Fist letter";
    'b' => "Second letter";
    _ => "Last letter";
}

# iteration

for value in data {
    //
}

loop {
    // 
}

typedef struct {
    id: int;
    status: Status;
} Proc;

typedef enum {
    car,
    lorry,
    truck,
    bus,
    bike
} Vehicle;

use typedef keyword to create a new type
Every type has a set of possible values in the type like a set in maths. for example, any create type proc is a value from the proc space i.e that is structured as a proc with all it's fields. or an enum the types are all the values in the enum. For example the type Vehicle has the set of values having it's type in the enum.

the type of a value defines what sort of operations can be applied to the value.

# functions
fn init_data(proc: Proc) -> proc {
    proc: Proc = new(Proc);
    proc.id = 11;
    proc.Status = ready;

    *proc   // return value stmt similar to rust-lang
}






