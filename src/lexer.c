#include "./lexer.h"

const char *enum_strings[] = 
{ 
"TKN_RANDOM_IDEN", 
"TKN_WRITELN", 
"TKN_INT_LIT", 
"TKN_SEMI", 
"TKN_STRING", 
"TKN_OPERATOR", 
"TKN_LPAREN", 
"TKN_RPAREN", 
"TKN_CURLY_L", 
"TKN_CURLY_R", 
"TKN_RETURN", 
"TKN_AMPERSAND",
"TKN_UNIQUE_NAME",
"TKN_VAR",
"TKNE_COLON",
"TKN_ASSIGN",
"TKN_I32",
"TKN_I64",
"TKN_f32",
"TKN_f64",
"TKN_VAR_STRING",
"TKN_B8",
"TKN_C8",// 16
"TKN_MODULE", //17
"TKN_IO", // 18
"TKN_READLN" 
};


Token *tokens = nullptr;
size_t tkn_count = 0;

char buff[128];
size_t i = 0;

Token *give_tokens(FILE *in){
tokens = malloc(64*sizeof(Token));
int c = fgetc(in);
while(c != EOF)
    {  
       if(c == '@')
       {
         buff[i] = (char)c;
         i++;
         buff[i]='\0';
         i=0;
         tokens[tkn_count].type = TKN_AMPERSAND;
         strcpy(tokens[tkn_count].value,buff);
         tkn_count++;
         c= fgetc(in);
         if(isalpha(c))
         {
            while(isalpha(c))
            {
               buff[i] = (char)c;
               i++;
               c=fgetc(in);
            }
            buff[i] = '\0';
            i=0;
            tokens[tkn_count].type = TKN_UNIQUE_NAME;
            strcpy(tokens[tkn_count].value,buff);
            tkn_count++;
         }
         
       } 
       if(isspace(c)){
            c = fgetc(in);
            continue;
       }

       else if(isalpha(c))
       {
        
       // FOR READING SOMETHING LIKE :
       //i32 , f32
         buff[i++] = (char)c;
         // printf("current_c : %c\n",current_c);
         c = fgetc(in);
         if(isdigit(c))
         {
           // c = fgetc(in);
           while(isdigit(c))
           {
             buff[i] = (char)c;
             i++;
             c = fgetc(in); 
           }
           buff[i] ='\0';
           i = 0;
           if(strcmp("i32",buff) == 0)
           {
             tokens[tkn_count].type = TKN_I32;
             strcpy(tokens[tkn_count].value,buff);
             tkn_count++;
           }
           else if(strcmp("i64",buff) == 0)
           {
             tokens[tkn_count].type = TKN_I64;
             strcpy(tokens[tkn_count].value,buff);
             tkn_count++;
           }
           else if(strcmp("f32",buff) == 0)
           {
             tokens[tkn_count].type = TKN_F32;
             strcpy(tokens[tkn_count].value,buff);
             tkn_count++;
           }
           else if(strcmp("f64",buff) == 0)
           {
             tokens[tkn_count].type = TKN_F64;
             strcpy(tokens[tkn_count].value,buff);
             tkn_count++;
           }
           else if(strcmp("c8",buff) == 0)
           {
             tokens[tkn_count].type = TKN_C8;
             strcpy(tokens[tkn_count].value,buff);
             tkn_count++;
           }
            else if(strcmp("b8",buff) == 0)
           {
             tokens[tkn_count].type = TKN_B8;
             strcpy(tokens[tkn_count].value,buff);
             tkn_count++;
           }
           
           
           ungetc(c,in); //  i32
         }               //      
        // else ungetc(c,in);

        // FOR READING NORMAL ALPHABETS  
         else { 
           while(isalpha(c)){
             buff[i] = (char)c;
               i++;
            c =  fgetc(in);
            }
            buff[i] = '\0';
            i = 0;
            ungetc(c,in);

         if(strcmp("writeLn",buff) == 0)
         {
            tokens[tkn_count].type = TKN_WRITELN;
            strcpy(tokens[tkn_count].value,buff);
            tkn_count++;

         }
         else if(strcmp("return",buff) == 0)
         {
            tokens[tkn_count].type = TKN_RETURN;
            strcpy(tokens[tkn_count].value,buff);
            tkn_count++;
         }
         else if(strcmp("module",buff) == 0)
         {
           tokens[tkn_count].type = TKN_MODULE;
           strcpy(tokens[tkn_count].value,buff);
           tkn_count++;
         }
        else if(strcmp("io",buff) == 0)
         {
           tokens[tkn_count].type = TKN_IO;
           strcpy(tokens[tkn_count].value,buff);
           tkn_count++;
         }
         else if(strcmp("readLn",buff) == 0)
         {
           tokens[tkn_count].type = TKN_READLN;
           strcpy(tokens[tkn_count].value,buff);
           tkn_count++;
         
         }
         else if(strcmp("string",buff) == 0)
         {
           tokens[tkn_count].type = TKN_VAR_STRING;
           strcpy(tokens[tkn_count].value,buff);
           tkn_count++;
         }
         
        
          else{
            tokens[tkn_count].type = TKN_VAR;
            strcpy(tokens[tkn_count].value,buff);
            tkn_count++;
           }
        
       }
       }
       else if(isdigit(c)) 
       {
                
        while(isdigit(c)){
            buff[i] = (char)c;
            i++;
            c= fgetc(in); 
           }
           buff[i] = '\0';
           i = 0;
           ungetc(c,in);
        tokens[tkn_count].type = TKN_INT_LIT;
        strcpy(tokens[tkn_count].value,buff);
        tkn_count++;
       } 
       else if(c == ';')   
       {
        tokens[tkn_count].type = TKN_SEMI; 
        tokens[tkn_count].value[0] = ';';
        tokens[tkn_count].value[1] = '\0';
        tkn_count++;
        
      }  
       else if(c == '"')
       { 
         c = fgetc(in);
         while(c != '"' && c!=EOF)
         {
            buff[i] = (char)c;
            i++;
            c = fgetc(in);
         }
         buff[i] = '\0';
         i=0;
         tokens[tkn_count].type = TKN_STRING;
         strcpy(tokens[tkn_count].value,buff);
         tkn_count++;
       }
       else if(c == '(')
       {
          tokens[tkn_count].type = TKN_LPAREN;
          tokens[tkn_count].value[0] = '(';
          tokens[tkn_count].value[1] = '\0';
          tkn_count++;
           }
        
       else if(c == ')')
       {
          tokens[tkn_count].type = TKN_RPAREN;
          tokens[tkn_count].value[0] = ')';
          tokens[tkn_count].value[1] = '\0';
          tkn_count++;
           }
      else if(c == '{')
      {
        tokens[tkn_count].type = TKN_CURLY_L;
          tokens[tkn_count].value[0] = '{';
          tokens[tkn_count].value[1] = '\0';
          tkn_count++; 
      }
      else if(c == '}')
      {
         tokens[tkn_count].type = TKN_CURLY_R;
          tokens[tkn_count].value[0] = '}';
          tokens[tkn_count].value[1] = '\0';
          tkn_count++;
      }
       else if(c == ':')
       {
           tokens[tkn_count].type = TKN_COLON;
          tokens[tkn_count].value[0] = ':';
          tokens[tkn_count].value[1] = '\0';
          tkn_count++;

       }
       else if(c == '=')
       {
          tokens[tkn_count].type = TKN_ASSIGN;
          tokens[tkn_count].value[0] = '=';
          tokens[tkn_count].value[1] = '\0';
          tkn_count++;
       }
       
       c= fgetc(in);
    }
    //  give_token_count(tkn_count);
    return tokens;
}
size_t token_cnt()
{
   return tkn_count;
}
