#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
 typedef enum
{
TKN_RANDOM_IDEN, // 0
TKN_WRITELN, // 1
TKN_INT_LIT, // 2
TKN_SEMI, // 3
TKN_STRING, // 4
TKN_OPERATOR, // 5
TKN_LPAREN, // 6
TKN_RPAREN, // 7
TKN_CURLY_L, // 8
TKN_CURLY_R, // 9
TKN_RETURN, //  10
TKN_AMPERSAND, // 11 
TKN_UNIQUE_NAME // 12
}Tokens;

typedef struct 
{
   Tokens type;
   char value[64];
   
}Token;


extern Token *tokens;
extern size_t tkn_count;

Token *give_tokens(FILE *in);
size_t token_cnt();

extern const char *enum_strings[];
