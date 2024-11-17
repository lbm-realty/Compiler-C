#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TABLE_SIZE 26

char* array[TABLE_SIZE][2] = {
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

char str[10];
void getChar(char c, char* str);
void addAlphabet(char c);
void addCharacter(char c);
void confirmString(char* s);
int tokenMatchingString (char* s);
void tokenMatchingPunct (char* c);
void stringEmptying (char* s);
void handleNumberString (char* s);
int len = 0;
FILE* file_ptr;

int main(int argc, char *argv[]) {
    file_ptr = fopen(argv[1], "r");
    if ((file_ptr = fopen(argv[1], "r")) == NULL) {
        printf("The file couldn't be opened \n");
    } else {
        printf("Cooke Analyzer :: R11828317\n");
        char ch;
        while ((ch = fgetc(file_ptr)) != EOF) {
            getChar(ch, str);
        }
    }
}

void getChar(char ptr, char* str) {
    if (isalpha(ptr)) {
        addAlphabet(ptr);
    }
    else if (isspace(ptr)) {
        if (len > 0) {
            if (isdigit(str[0])) {
                handleNumberString(str);
            } else if (isalpha(str[0])) {
                int result = tokenMatchingString(str);
                if (result != 0) {
                    printf("%s IDENT\n", str);
                }
            }
            stringEmptying(str);
        }
    }
    else if (ispunct(ptr)) {
        long pos = ftell(file_ptr);
        char next_char = fgetc(file_ptr);

        if ((ptr == '<' && next_char == '=') ||
            (ptr == '>' && next_char == '=') ||
            (ptr == '!' && next_char == '=') ||
            (ptr == '&' && next_char == '&') ||
            (ptr == '|' && next_char == '|') ||
            (ptr == '=' && next_char == '=')) {

            if (len > 0) {
                if (isalpha(str[0])) {
                    int result = tokenMatchingString(str);
                    if (result != 0) {
                        printf("%s IDENT\n", str);
                    }
                } else if (isdigit(str[0])) {
                    handleNumberString(str);
                }
                stringEmptying(str);
            }

            addCharacter(ptr);
            addCharacter(next_char);
            tokenMatchingPunct(str);
            stringEmptying(str);
        } else {
            fseek(file_ptr, pos, SEEK_SET);

            if (len > 0) {
                if (isalpha(str[0])) {
                    int result = tokenMatchingString(str);
                    if (result != 0) {
                        printf("%s IDENT\n", str);
                    }
                } else if (isdigit(str[0])) {
                    handleNumberString(str);
                }
                stringEmptying(str);
            }
            addCharacter(ptr);
            tokenMatchingPunct(str);
            stringEmptying(str);
        }
    }
    else if (isdigit(ptr)) {
        addAlphabet(ptr);
    }
}

void addAlphabet(char c) {
    if (len < 9) {
        str[len] = c;
        str[len + 1] = '\0';
        len++;
    }
}

void confirmString(char* s) {
    int length = strlen(s);
    if (isalpha(s[length - 1])) {
        int value = tokenMatchingString(s);
        if (value == 1) {
            printf("%s IDENT\n", s);
        }
    }
}

int tokenMatchingString(char* st) {
    for (int i = 0; i < 26; i++) {
        if (strcmp(st, array[i][0]) == 0) {
            printf("%s %s\n", array[i][0], array[i][1]);
            return 0;
        }
    }
    return 1;
}

void tokenMatchingPunct(char* ptr) {
    if (strlen(ptr) == 2) {
        for (int i = 14; i < 20; i++) {
            if (strcmp(ptr, array[i][0]) == 0) {
                printf("%s %s\n", array[i][0], array[i][1]);
                return;
            }
        }
    }
    if (strlen(ptr) == 1) {
        for (int i = 0; i < 14; i++) {
            if (strcmp(ptr, array[i][0]) == 0) {
                printf("%s %s\n", array[i][0], array[i][1]);
                return;
            }
        }
        printf("%s UNKNOWN\n", ptr);
    }
}

void addCharacter(char c) {
    if (len < 9) {
        str[len] = c;
        str[len + 1] = '\0';
        len++;
    }
}

void stringEmptying(char* s) {
    memset(s, 0, sizeof(char) * 10);
    len = 0;
}

void handleNumberString (char* s) {
    int asciiValue = (int)s[0];
    if (48 <= asciiValue && asciiValue <= 57)
        printf("%s INT_LIT\n", s);
}
