#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "front.h"
#include "parser.h"

int nextToken;
char secondChar;

static int charClass;
static char lexeme[100];
static char nextChar;
static int lexLen;
static FILE *in_fp;

static void addChar(char c);
static void getChar();
static void getNonBlank();
int verifyString();

int main(int argc, char *argv[])
{
    printf("Cooke Analyzer :: R11828317\n");
    if ((in_fp = fopen(argv[1], "r")) == NULL)
    {
        printf("ERROR - The file %s couldn't be opened \n", argv[1]);
    }
    else
    {
        getChar();
        do
        {
            lex();
            expr();
        } while (nextToken != EOF);
    }

    return 0;
}

static int lookup(char ch)
{
    switch (ch)
    {
    case '(':
        addChar(ch);
        nextToken = OPEN_PAREN;
        break;
    case ')':
        addChar(ch);
        nextToken = CLOSE_PAREN;
        break;
    case '+':
        addChar(ch);
        nextToken = ADD_OP;
        break;
    case '-':
        addChar(ch);
        nextToken = SUB_OP;
        break;
    case '*':
        addChar(ch);
        nextToken = MULT_OP;
        break;
    case '/':
        addChar(ch);
        nextToken = DIV_OP;
        break;
    case '=':
        addChar(ch);
        if ((secondChar = fgetc(in_fp)) == '=')
        {
            addChar(secondChar);
            nextToken = EQUAL_OP;
        }
        else
        {
            ungetc(secondChar, in_fp);
            nextToken = ASSIGN_OP;
        }
        break;
    case '<':
        addChar(ch);
        if ((secondChar = fgetc(in_fp)) == '=')
        {
            addChar(secondChar);
            nextToken = LEQUAL_OP;
        }
        else
        {
            ungetc(secondChar, in_fp);
            nextToken = LESSER_OP;
        }
        break;
    case '>':
        addChar(ch);
        if ((secondChar = fgetc(in_fp)) == '=')
        {
            addChar(secondChar);
            nextToken = GEQUAL_OP;
        }
        else
        {
            ungetc(secondChar, in_fp);
            nextToken = GREATER_OP;
        }
        break;
    case '%':
        addChar(ch);
        nextToken = MOD_OP;
        break;
    case '!':
        addChar(ch);
        if ((secondChar = fgetc(in_fp)) == '=')
        {
            addChar(secondChar);
            nextToken = NEQUAL_OP;
        }
        else
        {
            ungetc(secondChar, in_fp);
            nextToken = BOOL_NOT;
        }
        break;
    case ';':
        addChar(ch);
        nextToken = SEMICOLON;
        break;
    case '{':
        addChar(ch);
        nextToken = OPEN_CURL;
        break;
    case '}':
        addChar(ch);
        nextToken = CLOSE_CURL;
        break;
    case '&':
        addChar(ch);
        if ((secondChar = fgetc(in_fp)) == '&')
        {
            addChar(secondChar);
            nextToken = BOOL_AND;
        }
        break;
    case '|':
        addChar(ch);
        if ((secondChar = fgetc(in_fp)) == '|')
        {
            addChar(secondChar);
            nextToken = BOOL_OR;
        }
        break;
    default:
        addChar(ch);
        nextToken = UNKNOWN;
        break;
    }
    return nextToken;
}

static void addChar(char c)
{
    if (lexLen <= 98)
    {
        lexeme[lexLen++] = c;
        lexeme[lexLen] = 0;
    }
    else
    {
        printf("Error - lexeme is too long \n");
    }
}

static void getChar()
{
    if ((nextChar = getc(in_fp)) != EOF)
    {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else
    {
        charClass = EOF;
    }
}

static void getNonBlank()
{
    while (isspace(nextChar))
    {
        getChar();
    }
}

int verifyString()
{
    if (strcmp("input", lexeme) == 0)
    {
        nextToken = KEY_IN;
        // printf("%s %s\n", lexeme, tokenName(nextToken));
        return 0;
    }
    else if (strcmp("output", lexeme) == 0)
    {
        nextToken = KEY_OUT;
        // printf("%s %s\n", lexeme, tokenName(nextToken));
        return 0;
    }
    else if (strcmp("if", lexeme) == 0)
    {
        nextToken = KEY_IF;
        // printf("%s %s\n", lexeme, tokenName(nextToken));
        return 0;
    }
    else if (strcmp("else", lexeme) == 0)
    {
        nextToken = KEY_ELSE;
        // printf("%s %s\n", lexeme, tokenName(nextToken));
        return 0;
    }
    else if (strcmp("==", lexeme) == 0)
    {
        nextToken = EQUAL_OP;
        // printf("%s %s\n", lexeme, tokenName(nextToken));
        return 0;
    }
    else if (strcmp(">=", lexeme) == 0)
    {
        nextToken = GEQUAL_OP;
        // printf("%s %s\n", lexeme, tokenName(nextToken));
        return 0;
    }
    else if (strcmp("<=", lexeme) == 0)
    {
        nextToken = LEQUAL_OP;
        // printf("%s %s\n", lexeme, tokenName(nextToken));
        return 0;
    }
    else if (strcmp("!=", lexeme) == 0)
    {
        nextToken = NEQUAL_OP;
        // printf("%s %s\n", lexeme, tokenName(nextToken));
        return 0;
    }
    else
    {
        return 1;
    }
}

char *tokenName(int token)
{
    switch (token)
    {
    case ASSIGN_OP:
        return "ASSIGN_OP";
    case LESSER_OP:
        return "LESSER_OP";
    case GREATER_OP:
        return "GREATER_OP";
    case OPEN_PAREN:
        return "OPEN_PAREN";
    case CLOSE_PAREN:
        return "CLOSE_PAREN";
    case ADD_OP:
        return "ADD_OP";
    case SUB_OP:
        return "SUB_OP";
    case MULT_OP:
        return "MULT_OP";
    case DIV_OP:
        return "DIV_OP";
    case MOD_OP:
        return "MOD_OP";
    case BOOL_NOT:
        return "BOOL_NOT";
    case SEMICOLON:
        return "SEMICOLON";
    case OPEN_CURL:
        return "OPEN_CURL";
    case CLOSE_CURL:
        return "CLOSE_CURL";
    case EQUAL_OP:
        return "EQUAL_OP";
    case NEQUAL_OP:
        return "NEQUAL_OP";
    case LEQUAL_OP:
        return "LEQUAL_OP";
    case GEQUAL_OP:
        return "GEQUAL_OP";
    case BOOL_AND:
        return "BOOL_AND";
    case BOOL_OR:
        return "BOOL_OR";
    case KEY_IN:
        return "KEY_IN";
    case KEY_OUT:
        return "KEY_OUT";
    case KEY_IF:
        return "KEY_IF";
    case KEY_ELSE:
        return "KEY_ELSE";
    case IDENT:
        return "IDENT";
    case INT_LIT:
        return "INT_LIT";
    case UNKNOWN:
        return "UNKNOWN";
    }
}

int lex()
{
    lexLen = 0;
    getNonBlank();

    switch (charClass)
    {
    case LETTER:
        addChar(nextChar);
        getChar();
        while (charClass == LETTER || charClass == DIGIT)
        {
            addChar(nextChar);
            getChar();
        }
        int result = verifyString();
        if (result == 1)
        {
            nextToken = IDENT;
        }
        break;

    case DIGIT:
        addChar(nextChar);
        getChar();
        while (charClass == DIGIT)
        {
            addChar(nextChar);
            getChar();
        }
        nextToken = INT_LIT;
        break;

    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;

    case EOF:
        nextToken = EOF;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = 0;
        break;
    }

    if (nextToken != EOF)
    {
        printf("%s %s\n", lexeme, tokenName(nextToken));
    }
    return nextToken;
}
