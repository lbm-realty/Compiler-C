    //    case ASSIGN_OP:
    //         return "ASSIGN_OP";
#include <stdio.h> 

int main() {
    char* array[26][2] = {
    {"=", "ASSIGN_OP"},
    {"<", "LESSER_OP"},
    {">", "GREATER_OP"},
    {"(", "OPEN_PAREN"},
    {")", "CLOSE_PAREN"},
    {"+", "ADD_OP"},
    {"-", "SUB_OP"},
    {"*", "MULT_OP"},
    {"/", "DIV_OP"},
    {"%", "MOD_OP"},
    {"!", "BOOL_NOT"},
    {";", "SEMICOLON"},
    {"{", "OPEN_CURL"},
    {"}", "CLOSE_CURL"},
    {"==", "EQUAL_OP"},
    {"!=", "NEQUAL_OP"},
    {"<=", "LEQUAL_OP"},
    {">=", "GEQUAL_OP"},
    {"&&", "BOOL_AND"},
    {"||", "BOOL_OR"},
    {"input", "KEY_IN"},
    {"output", "KEY_OUT"},
    {"if", "KEY_IF"},
    {"else", "KEY_ELSE"},
    {"V", "IDENT"},
    {"N", "INT_LIT"}
};

    for (int i = 0; i < 26; i++) {
        printf("case %s:\n", array[i][1]);
        printf("return '%s';\n", array[i][1]);
    }
}