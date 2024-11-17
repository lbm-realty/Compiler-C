#ifndef FRONT_H
#define FRONT_H

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define OPEN_PAREN 25
#define CLOSE_PAREN 26
#define LESSER_OP 27 
#define GREATER_OP 28
#define MOD_OP 29
#define BOOL_NOT 30
#define SEMICOLON 31
#define OPEN_CURL 32
#define CLOSE_CURL 33
#define EQUAL_OP 34
#define NEQUAL_OP 35
#define LEQUAL_OP 36
#define GEQUAL_OP 37
#define BOOL_AND 38
#define BOOL_OR 39
#define KEY_IN 40
#define KEY_OUT 41
#define KEY_IF 42
#define KEY_ELSE 43

char *tokenName(int token);
int lex();

#endif
