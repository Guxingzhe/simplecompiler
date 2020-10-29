/* sample1-1: 字数统计 */
/* 类似Unix的wc程序 */

%{
int chars = 0;
int words = 0;
int lines = 0;
int totalc = 0;
int totalw = 0;
int totall = 0;
%}

%%
\r|\n|\r\n { lines++; chars++;}
[^ \t\n\r\f\v]+ { words++; chars += strlen(yytext);}
. {chars++;}
%%

int main(int argc, char **argv)
{
  if(argc >1){
    yyin = fopen(argv[1],"r");
    if(!yyin){
      perror(argv[1]);
      return(1);
      }
  }
  if(argc<2){
    yylex();
    printf("result:%d chars%8d words%8d lines\n",chars, words, lines);
  }

  for(int i =1;i<argc;i++){
    FILE* f=fopen(argv[i],"r");
    if(!f){
      perror(argv[i]);
      return(1);
    }
    yyrestart(f); //词法分析器从f中读入
    yylex();
    fclose(f);
    printf("result:%d chars%8d words%8d lines in file %s\n",chars, words, lines, argv[i]);
    totalc += chars;
    totalw += words;
    totall += lines;
  }
  if(argc > 2){
    printf("result:%d chars%8d words%8d lines\n",totalc, totalw, totall);
  }
}
