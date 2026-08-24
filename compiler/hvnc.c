#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include "./lexer.h"
#include "./parser.h"

int main(int argc,char **argv)
{
   
  FILE *in = nullptr;
  in = fopen(argv[1],"r");
  if(in == nullptr)
  {
    perror("UNABLE TO OPEN FILE TRY AGAIN  !!");
    exit(EXIT_FAILURE);
  } 
   
  tokens = give_tokens(in);
  



  size_t tkn_cnt = token_cnt();

  /*for(int i=0;i<tkn_cnt;i++)
  {
 
     printf("[ No. : %d, type : %d , value : %s ]\n",i,tokens[i].type,tokens[i].value);
 
} 
*/

 //  printf("total token cnt %d\n",token_cnt());
  // printf("%s\n",enum_strings[1]);
    

  fclose(in);
    
  FILE *out = nullptr;
  out = fopen("codegen/out.c","w");
  if(out == nullptr)
  {
    printf("you messed up file cant be open");
  }
  parse(out);
  
 /* printf("\n");
 for(int i=0;i<1;i++)
 {
   printf("identifier  |    type    |      value \n");
  printf("%s  %s  %s\n",table[0].identifier,table[0].type,table[0].value);
}*/
fclose(out);
    
  /* FILE *out = nullptr;
    out = fopen("out.c","w");
    if(out == nullptr)
    {
      perror("UNABLE TO OPEN FILE TRY AGAIN  !!");
      exit(EXIT_FAILURE);
    }
    fprintf(out,
        "#include<stdio.h>\n"
        "int main()\n" 
        "{\n"
        "printf(\"%%s\",\"%s\");\n"
         "return %s;\n"
        " }",tokens[3].value,tokens[1].value);

 //       for(int i=0;i<tkn_count;i++){
   //   printf("type : %d , value : %s\n",tokens[i].type,tokens[i].value);
   //  }

    fclose(out); */
   free(tokens);
  return 0;
}
