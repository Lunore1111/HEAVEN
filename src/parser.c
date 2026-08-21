#include<parser.h>

#include<ctype.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include "./lexer.h"

int current = 0;

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
you forget something %s at %d token\n",enum_strings[type],current);
        
        // printf("%d\n",current);
        // printf("%d\n",tokens[current].type);
        exit(EXIT_FAILURE);
    }
}

void parse_write(FILE *out)
{
expect(TKN_WRITELN);
expect(TKN_LPAREN);
expect(TKN_STRING);
char *data = tokens[current-1].value;
expect(TKN_RPAREN);
expect(TKN_SEMI);
// printf("my data is : %s",data);
fprintf(out,"printf(\"%s\\n\");",data);
}
void parse_main(FILE *out)
{
    expect(TKN_AMPERSAND); // +1
    expect(TKN_UNIQUE_NAME); // +2 
    expect(TKN_CURLY_L); //+3
    upper_part(out);
}
void parse_lower_main(FILE *out)
{
    expect(TKN_CURLY_R);
    lower_part(out);
}
int w1 = 0;
int w2 = 0;


void parse(FILE *out)
{
    if(tokens[current].type == TKN_AMPERSAND)
        {
            parse_main(out);
            
        }
    while(current < tkn_count-1) 
    {   
        if(tokens[current].type == TKN_WRITELN) parse_write(out);

        else 
        {
            printf("you messed up: parse function at %d\n",current);
            break;
        }
    }
 parse_lower_main(out);
}

