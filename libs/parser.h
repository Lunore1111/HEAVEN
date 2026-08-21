#pragma once

#include<ctype.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include "./lexer.h"

void upper_part(FILE *out);
void lower_part(FILE *out);
void expect(Tokens type);
void parse_write(FILE *out);
void parse_main(FILE *out);
void parse_lower_main(FILE *out);
void parse(FILE *out);
