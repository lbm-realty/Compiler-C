#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "parser.h"
#include "front.h"

void variable();
void const_condition();
static void error();
int start();

extern int line;
extern char lexeme[100];

void success() {
    int result = start();
    if (result == 0)
        printf("Syntax Validated\n");

    else {
        error();
    }
}

int start()
{
    switch (nextToken)
    {
    case IDENT:
        lex();
        if (nextToken == ASSIGN_OP)
        {
            expr();
            if (nextToken == SEMICOLON)
            {
                printf("Syntax Validated\n");
                return 1;

            }
            else error();
            // break;
        }
    case KEY_IN:
        lex();
        if (nextToken == OPEN_PAREN)
        {
            variable();
            if (nextToken == SEMICOLON)
            {
                printf("Syntax Validated\n");
                return 1;
            }
            else
                error();
            // break;
        }
    case KEY_OUT:
        lex();
        if (nextToken == CLOSE_PAREN)
        {
            expr();
            if (nextToken == SEMICOLON)
            {
                printf("Syntax Validated\n");
                return 1;
            }
            else
                error();
            // break;
        }
    case KEY_IF:
        lex();
        if (nextToken == OPEN_PAREN)
        {
            const_condition();
            lex();
            if (nextToken == CLOSE_PAREN)
            {
                lex();
                if (nextToken == OPEN_CURL)
                {
                    start();
                    lex();
                    if (nextToken == CLOSE_CURL)
                    {
                        lex();
                        if (nextToken == KEY_ELSE)
                        {
                            lex();
                            if (nextToken == OPEN_CURL)
                            {
                                lex();
                                start();
                                lex();
                                if (nextToken == CLOSE_CURL)
                                {
                                    printf("Syntax Validated\n");
                                    return 1;
                                }
                                else
                                    error();
                                // break;
                            }
                            else
                                error();
                            // break;
                        }
                        else
                        {
                            char *next = tokenName(nextToken);
                            if (isblank(next[0]) || isspace(next[0]))
                            {
                                return 1;
                            }
                            else
                                error();
                            // break;
                        }
                    }
                    else
                        error();
                    // break;
                }
                else
                    error();
                // break;
            }
            else
                error();
            // break;
        }
        else
            error();
        // break;

        while (nextToken != EOF && nextToken != CLOSE_CURL)
        {
            expr();
        }
    }
}

/* expr
 * Parses strings in the language generated by the rule:
 * <expr> -> <term> {(+ | -) <term>}
 */
void expr()
{
    /* Parse the first term */
    lex();
    term();

    /* As long as the next token is + or -, get
    the next token and parse the next term */
    while (nextToken == ADD_OP || nextToken == SUB_OP)
    {
        lex();
        term();
    }

    // printf("Exit <expr>\n");
} /* End of function expr */

void const_condition()
{
    lex();
    switch (nextToken)
    {
    case IDENT:
        expr();
        if (nextToken == LESSER_OP || nextToken == GREATER_OP || nextToken == EQUAL_OP ||
            nextToken == NEQUAL_OP || nextToken == LEQUAL_OP || nextToken == GEQUAL_OP)
        {
            expr();
            if (nextToken == SEMICOLON)
                printf("Parsed Successfully\n");
            else
                error();
            // break;
        }
        else
            error();
        // break;
    case OPEN_PAREN:
        const_condition();
        if (nextToken == CLOSE_PAREN)
        {
            lex();
            if (nextToken == SEMICOLON)
                printf("Parsed Successfully\n");
            else
                error();
            // break;
        }
        else
        {
            error();
            // break;
        }
    }
    while (nextToken == BOOL_AND || nextToken == BOOL_OR)
    {
        lex();
        expr();

        switch (nextToken)
        {
        case LESSER_OP:
        case GREATER_OP:
        case EQUAL_OP:
        case NEQUAL_OP:
        case LEQUAL_OP:
        case GEQUAL_OP:
            lex();
            expr();
            break;
        }
    }
}

void variable()
{
    lex();
    char *str = tokenName(nextToken);
    if (isalpha(str[0]))
    {
        lex();
        if (nextToken == CLOSE_PAREN)
            lex();
        else
        {
            error();
            // return;
        }
    }
    else
        error();
    // return;

    // Now we just have two steps left
    // We are at the alphabet now that's usually inside the parenthesis input (n), in this case n
    // Now we have to look if the syntax ends correctly, i.e., with a closed paren and semicolon
}

/* term
 * Parses strings in the language generated by the rule:
 * <term> -> <factor> {(* | /) <factor>)
 */
void term()
{
    /* Parse the first factor */
    factor();
    /* As long as the next token is * or /, get the
    next token and parse the next factor */
    while (nextToken == MULT_OP || nextToken == DIV_OP || nextToken == MOD_OP)
    {
        lex();
        factor();
    }
    // printf("Exit <term>\n");
} /* End of function term */

/* factor
 * Parses strings in the language generated by the rule:
 * <factor> -> id | int_constant | ( <expr )
 * */
void factor()
{
    if (nextToken == IDENT || nextToken == INT_LIT)
    {
        lex();
    }
    else
    {
        if (nextToken == OPEN_PAREN)
        {
            // lex();
            expr();
            if (nextToken == CLOSE_PAREN)
                lex();
            else
                error();
            // return;
        }
        else
            error();
        // return;
    }
}

static void error()
{
    char *token = tokenName(nextToken);
    printf("Error encounter on line %d. The next lexeme was %s and the next token was %c\n", line + 1, lexeme, token);
    exit(1);
}
