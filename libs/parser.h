#pragma once

#include<ctype.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include "./lexer.h"
#include<stdbool.h>

typedef struct
{

  char* identifier;
  Tokens type;
  char* value;

}info_table;


extern info_table table[64];
extern int table_pos;
extern char universal_value[64];
extern char* format;
extern bool check_var_syntax;

void include_header(FILE* out);
void upper_part(FILE *out);
void lower_part(FILE *out);
void expect(Tokens type);
void expect_any_write(Tokens any_type);
void expect_any_read(Tokens any_type);
bool expect_any_var(Tokens any_type);
void parse_write(FILE *out,Tokens type);
void parse_read(FILE *out);
void parse_main(FILE *out);
void parse_int_expression(FILE *out);
void parse_lower_main(FILE *out);
void parse(FILE *out);
