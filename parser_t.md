Here’s a **completed and refined version** of your grammar for a **basic programming language** implementation. I've kept things simple, consistent, and minimal — ideal for a small custom language. I've clarified your grammar rules and fixed some issues in formatting, naming, and precedence.

---

## 🔣 **Operators**

```ebnf
<add_op>          = "+" | "-"
<mult_op>         = "*" | "/"
<rem_op>          = "%"
<arithmetic_op>   = <add_op> | <mult_op> | <rem_op>

<increment_op>    = "++"
<decrement_op>    = "--"

<logical_op>      = "&&" | "||" | "!"
<bitwise_op>      = "&" | "|" | "^" | "~" | ">>" | "<<"
<comparison_op>   = "==" | "!=" | ">" | "<" | ">=" | "<="
<assign_op>       = "=" | "+=" | "-=" | "*=" | "/=" | "%="
<arrow_op>        = "=>"
<optional_op>     = "?"

<dot>             = "."
<underscore>      = "_"
<esc>             = "\n" | "\t" | "\r"
```

---

## 🔡 **Characters**

```ebnf
<digit>           = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<lower_case>      = "a" .. "z"
<upper_case>      = "A" .. "Z"
<letter>          = <lower_case> | <upper_case>
```

---

## 🔢 **Literals**

```ebnf
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
```

---

## 🧾 **Whitespace and Comments**

```ebnf
<whitespace>      = " " | <esc>
<line_comment>    = "//" (any character)* <esc>
<block_comment>   = "/*" (any character)* "*/"
```

---

## 🆔 **Identifiers**

```ebnf
<ident>           = <letter> (<letter> | <digit> | "_")*
```

---

## 🧮 **Expressions**

```ebnf
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
```

---

## 📐 **Operator Precedence (High → Low)**

1. Parentheses: `()`
2. Unary operators: `+ - ! ~`
3. Multiplicative: `* / %`
4. Additive: `+ -`
5. Comparison: `== != > < >= <=`
6. Logical: `&& ||`
7. Assignment: `= += -= *= /= %=`

---

## 🧾 **Declarations**

```ebnf
<var_declaration>   = <ident> ":" <type> ["=" <literal>] ";"
<const_declaration> = "const" <ident> ":" <type> ["=" <literal>] ";"
<import_declaration> = "import" <string_literal> ";"
```

---

## 📦 **Types**

```ebnf
<type> = "int" | "float" | "bool" | "char" | "string"
```

---

## 🧱 **Statements**

```ebnf
<statement> =
      <var_declaration>
    | <const_declaration>
    | <expr> ";"
    | <func_call> ";"
    | <if_statement>
    | <while_statement>
    | <return_statement>
```

---

## 🔁 **Control Structures (Optional Additions)**

```ebnf
<if_statement> = "if" "(" <expr> ")" "{" <statement>* "}" ["else" "{" <statement>* "}"]
<while_statement> = "while" "(" <expr> ")" "{" <statement>* "}"
<return_statement> = "return" [<expr>] ";"
```

---

## ✅ Notes:

* Simplified for parsing and implementation.
* You can expand `<statement>` and `<expr>` as needed.
* Precedence and associativity are handled by structuring `expr` rules from lowest to highest precedence.

---

Would you like me to generate **example code snippets** written in this language, or a **parser in Python** using this grammar?
