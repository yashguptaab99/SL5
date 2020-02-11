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

//pool table
int POOLTAB[10];

//global declaration
symbolTable SYMTAB[20];
literalTable LITTAB[20];
int STP, LTP, LC, PTP, pool;
char *word[5];


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

void printPOOLTAB()
{
    int i;
    printf("\n\n3]POOL TAB:\n------------------------------------\nPOOL NO.\tPOOL\n");
	printf("------------------------------------\n");
    for(i=0;i<pool+1;i++)
	    printf("%d\t\t%d\n",i,POOLTAB[i]);
    printf("------------------------------------\n");

}
void preprocess(int index)
{
	char str[25];
	int len,i;
	strcpy(str,word[index]);
	len = strlen(str);
	for(i=0;i<len;i++)
	{
		str[i] = str[i+1];
	}
	printf("\tPreprcoess : %s\n",str);
	strcpy(word[index],str);
}

void substring(int index,int start,int end,char* str1)
{
	char str[25];
	int len,i;
	int j=0;
	strcpy(str,word[index]);
	for(i=start;i<=end;i++)
	{
		str1[j] = str[i];
		j++;
	}
	str1[j] = '\0';
}

void createSourceCode(int noOfTokens)
{
	char str[25];
	int i,size,noOfOperands;
	FILE *fptr = NULL;
	fptr = fopen("objectCode.txt","a");
	substring(0,0,1,str);
	if(!strcmp(word[0],"AD,1"))
	{
		substring(1,2,strlen(word[1])-1,str);
		LC = atoi(str);	
		printf("\tLC : %d\n",LC);		
	}
	else if(!strcmp(word[0],"AD,2"))	
	{
		for(i=POOLTAB[PTP];i<POOLTAB[PTP+1];i++)
		{
			fprintf(fptr,"%d '%s'\n",LC,LITTAB[i].lit_name);
			LC ++;		
		}
		PTP++;
	}
        else if(!strcmp(word[0],"AD,3"))
	{
		for(i=POOLTAB[PTP];i<POOLTAB[PTP+1];i++)
		{
			fprintf(fptr,"%d '%s'\n",LC,LITTAB[i].lit_name);
			LC ++;		
		}
		PTP++;
	}
        else if(!strcmp(word[0],"AD,4"))	
	{
		substring(1,2,strlen(word[1])-1,str);
		fprintf(fptr,"%d / %s\n",LC,str);
		LC = atoi(str);
	}
	else if(!strcmp(word[0],"DL,2"))
	{
		substring(1,2,strlen(word[1])-1,str);
		size = atoi(str);
		for(i=1;i<=size;i++)
		{
			fprintf(fptr,"%d\n",LC);
			LC ++;
		}
	}
	else if(!strcmp(word[0],"DL,1"))
	{
		substring(1,2,strlen(word[1])-1,str);
		fprintf(fptr,"%d '%s'\n",LC,str);
		LC++;
	}
	else if(!strcmp(str,"IS"))
	{
		noOfOperands = noOfTokens - 1;
		fprintf(fptr,"%d ",LC);
		substring(0,3,strlen(word[0])-1,str);
		printf("\tMC : %s\n",str);
		fprintf(fptr,"+%s ",str);
		for(i=1;i<=noOfOperands;i++)
		{
			substring(i,0,0,str);
			if(!strcmp(str,"L"))
			{
				substring(i,2,strlen(word[i])-1,str);
				fprintf(fptr,"%d ",LITTAB[atoi(str)].lit_adr);
			}
			else if(!strcmp(str,"R"))
			{
				substring(i,2,strlen(word[i])-1,str);
				fprintf(fptr,"%s ",str);
			}
			else if(!strcmp(str,"S"))
			{
				substring(i,2,strlen(word[i])-1,str);
				fprintf(fptr,"%d ",SYMTAB[atoi(str)].sym_adr);
			}
		}
		fprintf(fptr,"\n");
		LC++;
	}
	fclose(fptr);
}


int main()
{
    char wc[10],str[10],temp;
    FILE *symFile, *litFile,*poolFile, *input;
    int i=0,addr,iterator,j,p;
    PTP = 0;
    POOLTAB[0] = 0;
	LC = 0;
	
    symFile = fopen("symtab.txt","r");
    litFile = fopen("littab.txt","r");
    poolFile = fopen("pooltab.txt","r");

    fscanf(symFile,"%s",wc);
    STP = atoi(wc);
    fscanf(litFile,"%s",wc);
    LTP = atoi(wc);
    fscanf(poolFile,"%s",wc);
    pool = atoi(wc);

    printf("\nSTP = %d\n",STP);
    printf("LTP = %d\n",LTP);
    printf("POOL = %d\n",pool);

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

    for(i=0;i<pool+1;i++)
    {
        fscanf(poolFile,"%s",wc);
        fscanf(poolFile,"%s",wc);
        p = atoi(wc);
        POOLTAB[i]=p;
    }    

    printSYMTAB();
	printLITTAB();
    printPOOLTAB();
	
    fclose(symFile);
    fclose(litFile);

    input = fopen("ir.txt","r");
    temp = fgetc(input);
	while(!feof(input))
	{	
		iterator = 0;
		while(temp != '\n')
		{
			str[iterator] = temp;
			iterator++;
			temp = fgetc(input);
		}	
		str[iterator] = '\0';
		printf("%s\n",str);
		i=0;
		word[i] = strtok(str,")");
        while(word[i] != NULL)
		{
			printf("\n\tToken : %s\n",word[i]);
			preprocess(i);
			i++;
			word[i] = strtok(NULL,")");
		}
        printf("\n\tWord:");
        for(j=0;j<i;j++)
		{
			printf(" %s  ",word[j]);
		}
        printf("\n\n");
        createSourceCode(i);
        temp = fgetc(input);
    }


    return 0;
}
