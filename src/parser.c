#include<parser.h>

#include<ctype.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include "./lexer.h"

info_table table[64];
int table_pos = 0;
char universal_value[64];
int current = 0;
char* format = "d";
char* string_format = "s"; 
int store_type = 0;

void upper_part(FILE *out)
{
char str[] = "#include<stdio.h>\n int main(){\n";
   fputs(str,out);
}
void lower_part(FILE *out)
{
    char str[] =" }\n";
    fputs(str,out);
}

void expect(Tokens type)
{
    if(tokens[current].type == type)
    {   
        // printf("%s\n",tokens[current].value);
        current++;
    }
    else if(tokens[current].type != type)
    {
        
         printf("!!!!    ERROR    !!!!\n") ;
         printf("ERROR : \
you forget : %s at %d token\n",enum_strings[type],current);
        
        // printf("%d\n",current);
        // printf("%d\n",tokens[current].type);
        return;
    }
}
void expect_any(Tokens type)
{
  // printf("\n");
  // printf("parser.c :  currently in expect_any");
 if(tokens[current].type == TKN_VAR)
 {   
  // printf("\n");
   //printf("parser.c : if part is running ");
   // printf("\n");
   // printf("parser.c : current token value %s\n",tokens[current].value);
   for(int i=0;i<table_pos;i++) 
     {
       if(strcmp(tokens[current].value,table[i].identifier) == 0) 
       { 
       // printf("expect any current token value : %s\n",  tokens[current].value);
         
         store_type = table[i].type; 
         strcpy(universal_value,table[i].value);

         // printf("variable value for that same current : %s\n",table[i].value);
       }
       
     }
 }
 else strcpy(universal_value,tokens[current].value);
 
 current++;
}


void parse_write(FILE *out,Tokens type)
{

expect(TKN_WRITELN);
expect(TKN_LPAREN);
// printf("parser.c  : token is : %d",tokens[current].type);
// store_type = tokens[current].type;
// printf("parser.c : the store_type is ->  %d",store_type);
expect_any(tokens[current].type);
char *data = tokens[current-1].value;
expect(TKN_RPAREN);
expect(TKN_SEMI);
// printf("my data is : %s",data);
if(store_type == TKN_I32) fprintf(out,"printf(\"%%%s\\n\",%s);",format,universal_value);
else 
{ 
  fprintf(out,"printf(\"%%s\\n\",\"%s\");",universal_value);
   printf("parser.c :  else part run in write ");
}
}
void parse_main(FILE *out)
{
    expect(TKN_AMPERSAND); // +1
    expect(TKN_UNIQUE_NAME); // +2 
    expect(TKN_CURLY_L); //+3
    upper_part(out);
}
void parse_int_expression(FILE* out)
{
  expect(TKN_VAR);
  char* name = tokens[current-1].value;
  // printf("in int expression -> %s\n",name);
  table[table_pos].identifier = name;
  // printf("in int expression after table get assign -> %s\n",table[table_pos].identifier);
  expect(TKN_COLON);
  expect(TKN_I32);
  expect(TKN_ASSIGN);
  expect(TKN_INT_LIT);
  table[table_pos].type = TKN_I32;
  char* val = tokens[current-1].value;
  
  table[table_pos].value = val;
  
  expect(TKN_SEMI);
  fprintf(out,"int %s =",name);
  fprintf(out,"%s ;",val);
  table_pos++;
}
void parse_lower_main(FILE *out)
{
    expect(TKN_CURLY_R);
    lower_part(out);
}

void parse(FILE *out)
{
    if(tokens[current].type == TKN_AMPERSAND)
        {
            parse_main(out);
            
        }
    while(current < tkn_count-1) 
    {   
        if(tokens[current].type == TKN_WRITELN) parse_write(out,tokens[current].type);
        else if(tokens[current].type == TKN_VAR) parse_int_expression(out);
        else 
        {
            printf("you messed up: parse function at %d\n",current);
            break;
        }
    }
  /*  printf("\n");
    printf("the variable universal value is %s\n",universal_value);
    printf("\n"); */
 parse_lower_main(out);
}

