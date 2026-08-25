#include<parser.h>

#include<ctype.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdbool.h>
#include "./lexer.h"

info_table table[64];
int table_pos = 0;
char universal_value[64];
int current = 0;
char* format = "d";
char* string_format = "s"; 
int store_type = 0;
char temp_var_name[10];

bool check_var_syntax = false;

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
void expect_any_write(Tokens any_type)
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

       printf("\n");
       printf("parser.h : expect_any_write outer if %s is current token value\n",tokens[current].value);
       printf("parser.h : expect_any_write outer if %s table identifier value\n",table[i].identifier);
       printf("\n");  

       if(strcmp(tokens[current].value,table[i].identifier) == 0) 
       { 
       // printf("expect any current token value : %s\n",  tokens[current].value);
         printf("\n");
         printf("the expect_any_write inner store_type if have runned !\n"); 
         printf("table[i].type = %d",table[i].type);
         store_type = table[i].type;
         printf("\n");
         printf("expect_any_write , store_type is %d->\n",store_type);
         strcpy(temp_var_name,tokens[current].value);
        // strcpy(universal_value,table[i].value);

         // printf("variable value for that same current : %s\n",table[i].value);
       }
       
     }
 }
 else 
 {
   // this generally for string 
   // it is for simple string like 
   // "hello world" inside writeLn 
   strcpy(universal_value,tokens[current].value);
   store_type = 0;
 }
 
 current++;
}
void expect_any_read(Tokens any_type)
{
  // printf("expect_any_read run");
   if(tokens[current].type == TKN_VAR)
   {
     for(int i=0;i<table_pos;i++)
     {
       if(strcmp(tokens[current].value,table[i].identifier) == 0)
       {
         store_type = table[i].type;
         strcpy(temp_var_name,tokens[current].value);
         // printf("parser.c : inside expect_any %s\n",temp_var_name);
        // universal_value = nullptr;
       }
     }
   }
  else
  {
    printf("!!! invalid variable inside readLn !!! ");
  }
   current++;
}
bool expect_any_var(Tokens any_type)
{
  if(tokens[current].type == TKN_ASSIGN)
  { 
    current++; 
    if(tokens[current].type == TKN_INT_LIT) 
    {
      current++;
    }
    check_var_syntax = true;
    return check_var_syntax;
  }
  return check_var_syntax;
}



void parse_write(FILE *out,Tokens type)
{

expect(TKN_WRITELN);
expect(TKN_LPAREN);
// printf("parser.c  : token is : %d",tokens[current].type);
// store_type = tokens[current].type;
// printf("parser.c : the store_tynpe is ->  %d",store_type);
printf("\n");
printf("which type is passed -> %d\n",tokens[current].type);
printf("\n");
expect_any_write(tokens[current].type);

char *data = tokens[current-1].value;
expect(TKN_RPAREN);
expect(TKN_SEMI);
// printf("my data is : %s",data);
printf("store type is %d",store_type);
if(store_type == TKN_I32) fprintf(out,"printf(\"%%%s\\n\",%s);",format,temp_var_name);

else 
{ 
  fprintf(out,"printf(\"%%s\\n\",\"%s\");",universal_value);
   // printf("parser.c :  else part run in write ");
}

}

void parse_read(FILE* out)
{
   expect(TKN_READLN);
   expect(TKN_LPAREN);
   expect_any_read(tokens[current].type);
   expect(TKN_RPAREN);
   expect(TKN_SEMI);
   printf("parser.c : temp_var_name is -> %s\n",temp_var_name);
   fprintf(out,"scanf(\"%%%s\",&%s);",format,temp_var_name);
   
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
  table[table_pos].type = TKN_I32; 
  expect_any_var(tokens[current].type); 
  char* val = tokens[current-1].value;
  table[table_pos].value = val;
  expect(TKN_SEMI);
  

  if(check_var_syntax)
  { 
  fprintf(out,"int %s =",name);
  fprintf(out,"%s ;",val);
  }
  else
  {
   fprintf(out,"int %s;",name);
  }
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
        else if(tokens[current].type == TKN_READLN) parse_read(out);
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

