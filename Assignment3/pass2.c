#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Symbol Table Structure
typedef struct symbolTable
{
	char sym_name[25];
	int sym_adr;
}symbolTable;

//Literal Table Structure
typedef struct literalTable
{
	char lit_name[10];
	int lit_adr;
}literalTable;

//global declaration
symbolTable SYMTAB[20];
literalTable LITTAB[20];
int STP, LTP;

//print functions
void printSYMTAB()
{
	int i;
	printf("\n\n1] SYMBOL TABLE:\n------------------------------------\nSYMBOL NO.\tSYMBOL\tADDRESS");
	printf("\n------------------------------------");
    for(i=0;i<STP;i++)
		printf("\n%d          \t %s\t%d",i,SYMTAB[i].sym_name,SYMTAB[i].sym_adr);
	printf("\n------------------------------------\n");
}

void printLITTAB()
{
	int i;
	printf("\n\n2] LITERAL TABLE:\n------------------------------------\nLITERAL NO.\tLITERAL\tADDRESS");
	printf("\n------------------------------------");
    for(i=0;i<LTP;i++)
        printf("\n %d           \t %s\t%d",i,LITTAB[i].lit_name,LITTAB[i].lit_adr);
    printf("\n------------------------------------\n");
}


int main()
{
    char wc[10];
    FILE *symFile, *litFile, *input;
    int i=0,addr;

    symFile = fopen("symtab.txt","r");
    litFile = fopen("littab.txt","r");

    fscanf(symFile,"%s",wc);
    STP = atoi(wc);
    fscanf(litFile,"%s",wc);
    LTP = atoi(wc);

    printf("%d\n",STP);
    printf("%d\n",LTP);
    for(i=0;i<STP;i++)
    {
        fscanf(symFile,"%s",wc);
        fscanf(symFile,"%s",wc);
        strcpy(SYMTAB[i].sym_name,wc);
        fscanf(symFile,"%s",wc);
        addr = atoi(wc);
        SYMTAB[i].sym_adr = addr;
    }

    for(i=0;i<LTP;i++)
    {
        fscanf(litFile,"%s",wc);
        fscanf(litFile,"%s",wc);
        strcpy(LITTAB[i].lit_name,wc);
        fscanf(litFile,"%s",wc);
        addr = atoi(wc);
        LITTAB[i].lit_adr = addr;
    }
    

    printSYMTAB();
	printLITTAB();
	
    fclose(symFile);
    fclose(litFile);

    input = fopen("ir.txt","r");
    


    return 0;
}
