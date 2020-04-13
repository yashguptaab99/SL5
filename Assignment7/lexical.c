#include<stdio.h>
#include<string.h>
#include<ctype.h>

int searchTerminalTable(char* key);
void setUniversalSymbolTable(char* data,char* type,int ref);

//structure for terminal table
typedef struct TerminalTable
{
	int id;
	char data[20];

}terminalTable;

//structure for identifier table
typedef struct IdentifierTable
{
	int id;
	char data[20];

}identifierTable;

//structure for literal table
typedef struct LiteralTable
{
	int id;
	char data[20];

}literalTable;

//structure for universal symbol table
typedef struct UniversalSymTable
{
	int id;
	char data[10];
	char type[10];
	int ref;
}universalSymbolTable;

terminalTable TRM[100];
identifierTable IDN[100];
literalTable LIT[100];
universalSymbolTable UST[100];
int LTP,USTP,ITP,multiLineCmt;

//functions to set terminal,identifier,literal and universal symbol table entries
void setTerminalTableEntry(int index,char* data)
{
	TRM[index].id = index+1;
	strcpy(TRM[index].data,data);
}

void setIdentifierTableEntry(char* data)
{
	IDN[ITP].id = ITP+1;
	strcpy(IDN[ITP].data,data);
	ITP++;
}

void setLiteralTableEntry(char* data)
{
	LIT[LTP].id = LTP+1;
	strcpy(LIT[LTP].data,data);
	LTP++;
}

void setUniversalSymbolTable(char* data,char* type,int ref)
{
	UST[USTP].id = USTP+1;
	strcpy(UST[USTP].data,data);
	strcpy(UST[USTP].type,type);
	UST[USTP].ref = ref;
	USTP++;
}

//functions to print different tables
void printUniversalSymbolTable()
{
	int i=0;
	printf("\n*********************************** UST ************************************");
	printf("\nId   Data                          Type    Reference\n");
	printf("****************************************************************************\n");
	for(i=0;i<USTP;i++)
	{
		printf("\n%-5d%-30s%-8s%-9d\n",UST[i].id,UST[i].data,UST[i].type,UST[i].ref);
	}
	printf("----------------------------------------------------------------------------\n");	
}

void printTerminalTable()
{
	int i=0;
	printf("\n***TERMINAL TABLE ***");
	printf("\nId   Data\n");
	printf("*********************\n");
	for(i=0;i<68;i++)
	{
		printf("\n%-5d%s\n",TRM[i].id,TRM[i].data);
	}
	printf("---------------------\n");	
}

void printLiteralTable()
{
	int i=0;
	printf("\n******************************* LITERAL TABLE ******************************");
	printf("\nId   Data\n");
	printf("****************************************************************************\n");
	for(i=0;i<LTP;i++)
	{
		printf("\n%-5d%s\n",LIT[i].id,LIT[i].data);
	}
	printf("----------------------------------------------------------------------------\n");	
}

void printIdentifierTable()
{
	int i=0;
	printf("\n********************** IDENTIFIER TABLE *************************");
	printf("\nId   Data\n");
	printf("*****************************************************************\n");
	for(i=0;i<ITP;i++)
	{
		printf("\n%-5d%s\n",IDN[i].id,IDN[i].data);
	}
	printf("-----------------------------------------------------------------\n");	
}

//function to setup terminal table
void setTerminalTable()
{
	int counter = 0;	
	FILE* fptr = fopen("keywords.txt","r+");
	char buffer[500];
	int counter1 = 0;	
	char* token;
	char temp;
	while(!feof(fptr))
	{
		temp = fgetc(fptr);
		while(temp != '\n')
		{
			buffer[counter1] = temp;
			if(!feof(fptr))
			{
				temp = fgetc(fptr);
				counter1++;
			}
			else 
				break;
		}
		buffer[counter1] = '\0';
		counter1 = 0;
		token = strtok(buffer," ");
		while(token != NULL)
		{	
			setTerminalTableEntry(counter,token);
			counter++;
			token = strtok(NULL," ");
		}
		
	}
	fclose(fptr);
}

//function to search in terminal table
int searchTerminalTable(char* key)
{
	int i;
	for(i=0;i<68;i++)
	{
		if(strcmp(TRM[i].data,key)==0)
		{
			return i;
		}	
	}
	return -1;
}

//function to search identifier table
int searchIDN(char* key)
{
	int i;
	for(i=0;i<ITP;i++)
	{
		if(strcmp(IDN[i].data,key)==0)
		{
			return i;
		}	
	}
	return -1;
}

//function to check if given char is a delimiter or not
int isDelimiter(char temp1,char temp2)
{
	int check = -1;
	char temp[3];
	if(temp2 == '+' || temp2 == '-' || temp2 == '=')
	{		
		if(temp1 == '-' || temp1 == '+' || temp1 == '/' || temp1 == '*' || temp1 == '=' || temp1 == '%' || temp1 == '<' || temp1 == '>')
		{
			temp[0] = temp1;
			temp[1] = temp2;
			temp[2] = '\0';	
			check = searchTerminalTable(temp);
		}
		return check;
	}
	
	temp[0] = temp1;
	temp[1] = '\0';
	check = searchTerminalTable(temp);
	return check;	
}

//function to parse string i.e a single line of a program
void parseString(char buffer[1000])
{
	char temp[100];
	int counter = 0;
	int counter1 = 0;
	int len = strlen(buffer);
	int flag = 0;
	int flag1 = 0;
	int i;
	char temp1[3];
	int check1 = -1;
	int check2 = -1;
	while(counter<len)
	{	
		if(multiLineCmt == 1)
		{
			if(buffer[counter] == '*' && buffer[counter+1] == '/')
			{
				counter++;
				multiLineCmt = 0;
			}
			counter++;
		}
		else
		{
			if(isalnum(buffer[counter]))
			{
				temp[counter1++] = buffer[counter++];			
			}
			else
			{
				int check = isDelimiter(buffer[counter],buffer[counter+1]);
				if(check >= 0)
				{
					if(buffer[counter] == '/' && buffer[counter+1] == '/')
					{
						break;
					}
				
					if(buffer[counter] == '/' && buffer[counter+1] == '*')
					{
						counter+=2;
						multiLineCmt = 1;
						continue;
					}
				
					temp[counter1] = '\0';
					counter1 = 0;
					if(temp[0] != '\0')
					{
						check1 = searchTerminalTable(temp);
						if(check1 >= 0)
						{
							setUniversalSymbolTable(temp,"TRM",TRM[check1].id);
							if(strcmp(temp,"include")==0)
							{
								flag1 = 1;
							}
						}
						else
						{
							check2 = searchIDN(temp);
							if(check2 == -1)
							{
								setIdentifierTableEntry(temp);
								setUniversalSymbolTable(temp,"IDN",ITP);
							}
							else	
								setUniversalSymbolTable(temp,"IDN",IDN[check2].id);
						}
						temp[0] = '\0';
					}
					
					if(check >= 0 && check <= 10)
					{
						temp1[0] = buffer[counter];
						temp1[1] = buffer[counter+1];
						temp1[2] = '\0';
						setUniversalSymbolTable(temp1,"TRM",TRM[check].id);	
						counter++;
					}
					else
					{
						temp1[0] = buffer[counter];
						temp1[1] = '\0';
						setUniversalSymbolTable(temp1,"TRM",TRM[check].id);
					}
					temp1[0] = '\0';
					counter++;
					if(strcmp(TRM[check].data,"\"")==0)
					{
						char stringBuf[100];
						i = 0;
						while((int)buffer[counter]!=34)
						{
							stringBuf[i++] = buffer[counter++];
						}
						stringBuf[i] = '\0';
						setLiteralTableEntry(stringBuf);
						setUniversalSymbolTable(stringBuf,"LIT",LTP);
						setUniversalSymbolTable("\"","TRM",TRM[check].id);
						counter++;
						stringBuf[0] = '\0';
					}
				
					if(flag1 == 1 && strcmp(TRM[check].data,"<")==0)
					{
						flag1 = 0;
						char stringBuf1[100];
						i = 0;
						while(strcmp(&buffer[counter],">")!=0)
						{
							stringBuf1[i++] = buffer[counter++];
						}
						stringBuf1[i] = '\0';
						setIdentifierTableEntry(stringBuf1);
						setUniversalSymbolTable(stringBuf1,"IDN",ITP);
						stringBuf1[0] = '\0';
					}
				}
			
				if(check == -1)
				{
					if(buffer[counter] == ' ' || buffer[counter] == '\t')
					{
						counter++;
						temp[counter1] = '\0';
						counter1 = 0;
						if(temp[0] != '\0')
						{
							check1 = searchTerminalTable(temp);
							if(check1 >= 0)
							{
								setUniversalSymbolTable(temp,"TRM",TRM[check1].id);  
							
								if(strcmp(temp,"include") == 0)
								{
									flag1 = 1;
								}
							}
							else
							{
								check2 = searchIDN(temp);
								if(check2 == -1)
								{
									setIdentifierTableEntry(temp);
									setUniversalSymbolTable(temp,"IDN",ITP);
								}	
								else
									setUniversalSymbolTable(temp,"IDN",IDN[check2].id);
							}
							temp[0] = '\0';
						}
					}	
				
				}
			}
		}
	}
}

int main()
{
	FILE* fptr;
	char buffer[1000];
	int counter = 0;	
	
	USTP = 0;
	LTP = 0;
	ITP = 0;
	multiLineCmt = 0;

	setTerminalTable();

	printTerminalTable();
	
	fptr = fopen("program.txt","r+");
	
	char temp = fgetc(fptr);
	while(!feof(fptr))
	{
		while(temp != '\n')
		{
			buffer[counter++] = temp;
			temp = fgetc(fptr);
		}					
		buffer[counter] = '\0';								
		parseString(buffer);
		counter = 0;
		if(!feof(fptr))
		{
			temp = fgetc(fptr);
		} 		
	}
	
	printUniversalSymbolTable();
	
	printLiteralTable();
	
	printIdentifierTable();
	
	return 0;
}
