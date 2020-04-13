%{ 
   /* Definition section */
  #include<stdio.h> 
  int flag=0; 
%} 
   

%token NUMBER FLOAT   
%union
{
    int intValue;
    float floatValue;
} 
%type <intValue> NUMBER
%type <floatValue> FLOAT E ArithmeticExpression
%left PLUS SUB MUL DIV MOD 
  
  
/* Rule Section */
%% 
  
ArithmeticExpression: E{ 
  
         printf("\nResult=%f\n", $$); 
  
         return 0; 
  
        }; 
 E:E PLUS E {$$=$1+$3;} 
  
 |E SUB E {$$=$1-$3;} 
  
 |E MUL E {$$=$1*$3;} 
  
 |E DIV E {$$=$1/$3;} 
  
 |E MOD E {$$=(int)$1%(int)$3;} 
  
 |'('E')' {$$=$2;}
 	 
 | NUMBER {$$=$1;}
   
 | FLOAT {$$=$1;}  
 ; 
  
%% 
    
void main() 
{ 
   printf("\nEnter any Arithmetic Expression : \n"); 
  
   yyparse(); 
   if(flag==0) 
   printf("\nEntered arithmetic expression is Valid\n\n"); 
} 

void yyerror() 
{ 
   printf("\nEntered arithmetic expression is Invalid\n\n"); 
   flag=1; 
} 
