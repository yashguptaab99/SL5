%{ 
  /* Definition section */
  #include<stdio.h> 
  #include "y.tab.h" 
  extern union yylval;
   
%} 
  
/*Rule Section*/
%% 

[-+]?[0-9]+ { 
          yylval.intValue=atoi(yytext); 
          return NUMBER; 
       } 
	 
[-+]?[0-9]+[.][0-9]+ { 
          yylval.floatValue=atof(yytext); 
          return FLOAT; 
       } 	 
	        
[\t] ;

[ ] ; 

"PLUS" {return PLUS;}

"SUB" {return SUB;}

"MUL" {return MUL;}

"DIV" {return DIV;}

"MOD" {return MOD;}

[\n] return 0; 
  
. return yytext[0];
%% 
  
int yywrap() 
{ 
 return 1; 
} 


