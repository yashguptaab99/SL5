#include<stdio.h>
#include<string.h>
#include <stdlib.h>
char mot[11][6]={"STOP","ADD","SUB","MUL","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"}; //Mnemonics Code Table
char pot[6][6]={"START","END","LTORG","ORIGIN","EQU"}; //Pseudo Opcode Table
char r[4][6]={"AREG","BREG","CREG","DREG"}; //registers

struct l
{ 
	char name; //name of literal
	int add; //address ofliteral
}lit[20];

struct s
{ 
	char name[20]; // name of symbol
	int add; //address of symbol
}sy[20];

int isInMot(char [10]);
int isInPot(char[10]);

int main()
{

	char wc[10],temps[5];	
	int lc,LTP=0,STP=0,i,j=0,k=0,litflag=0,m=0,tempb,flag=0,oldLC=0,val=0;
	FILE *fip,*fir;
	fip=fopen("input.asm","r"); //assembler input
	fir=fopen("ir.txt","w"); //Intermediate Representation
	fscanf(fip,"%s",wc); //read input
	while(!feof(fip))
	{
		//check start
		up:if(!strcmp(wc,"START")) //if start copy address(lc)
		{
			fscanf(fip,"%d",&lc);
			fprintf(fir,"(%s,%d)(%s,%d)     \t LC\n","AD",1,"C",lc);
		}
		//check origin
		else if(!strcmp(wc,"ORIGIN")) //if ORIGIN copy address(lc)
		{
			fprintf(fir,"(%s,%d)","AD",4);
			fscanf(fip,"%s",wc); //read next
			for(j=0;j<STP;j++)
			{
				//check if said symbol is present in symbol table
				if(!strcmp(sy[j].name,wc))
				{
					flag=1;
					fprintf(fir,"(%s,%d)","S",j);
					fscanf(fip,"%s",wc); //read next
					if(!strcmp(wc,"+"))
					{
						fscanf(fip,"%s",wc); //read next
						oldLC=lc;
						val=atoi(wc);
						lc=val+sy[j].add;
					}
					if(!strcmp(wc,"-"))
					{
						fscanf(fip,"%s",wc); //read next
						oldLC=lc;
						val=atoi(wc);
						lc=sy[j].add-val;
					}
					fprintf(fir,"     \t %d/%d",oldLC,lc);
					goto up;
				}
			}
		}
		fscanf(fip,"%s",wc); //read next
		//check first is symbol
		if(!isInMot(wc) && !isInPot(wc))
		{
			for(j=0;j<STP;j++)
			{
				//check if said symbol is present in symbol table
				if(!strcmp(sy[j].name,wc))
				{
					flag=1;
					sy[j].add=lc;
					strcpy(temps,sy[STP].name);
					fscanf(fip,"%s",wc); //read next
					break;
				}	
			} //else add new entry in symbol table
			if(flag==0)
			{
				strcpy(sy[STP].name,wc);
				strcpy(temps,sy[STP].name);
				sy[STP].add=lc;
				STP++;
				fscanf(fip,"%s",wc); //read next
			}
		}		
		//check if it is present in mnemonics table
		for(i=0;i<11;i++)
		{
			if(!strcmp(wc,mot[i]))
			{
				if(!strcmp(wc,"STOP"))//for STOP
				{
					fprintf(fir,"(%s,%d)","IS",i);
					fscanf(fip,"%s",wc);
					break;
				}	
				fprintf(fir,"(%s,%d)","IS",i); //found in mot
				fscanf(fip,"%s",wc);
				for(j=0;j<4;j++) //now find register
					if(!strcmp(wc,r[j])){
						fprintf(fir,"(R,%d)",j+1);
						fscanf(fip,"%s",wc);
					}	
				if(!strcmp(wc,"=")) //if = it is literal
				{
					k=1;
					fscanf(fip,"%s",wc);
					//check if said literal already present in literlar table
					for(j=0;j<LTP;j++)
						if(lit[j].name==wc[k]) //if(!strcmp(lit[j].name,wc[k]))
						{
							litflag=1;
							fprintf(fir,"(%s,%d)\t %d","L",j,lc);
						} //else add new entry in Literal table
					if(litflag==0)
					{
						lit[LTP].name=wc[k];
						fprintf(fir,"(%s,%d)\t %d","L",LTP,lc);
						LTP++;
					}
					break;
				}
				else //if it’s not literal it must be symbol
				{
					for(j=0;j<STP;j++)
					{
						//check if said symbol is present in symbol table
						if(!strcmp(sy[j].name,wc))
						{
							flag=1;
							fprintf(fir,"(%s,%d)\t %d\n","S",j,lc);
							lc++;
							goto up;
						}
					} //else add new entry in symbol table
					if(flag==0)
					{
						strcpy(sy[STP].name,wc);
						fprintf(fir,"(%s,%d)\t %d","S",STP,lc);
						STP++;
						break;
					}
				}
			}
			//if it’s not there in mot then check for symbol definition [DC/DS]
			if(!strcmp(wc,"DS"))
			{
				fscanf(fip,"%d",&tempb);
				fprintf(fir,"(%s,%d)(C,%d)     \t %d\n","DL",2,tempb,lc);
				lc+=tempb;					
				goto up;
			}
			else if(!strcmp(wc,"DC"))
			{
				fscanf(fip,"%d",&tempb);
				fprintf(fir,"(%s,%d)(C,%d)     \t %d\n","DL",1,tempb,lc);
				lc++;
				goto up;
			}
		}

		//check for END or LTORG of assembly statements
		if(!strcmp(wc,"END") || !strcmp(wc,"LTORG"))
		{
			if(!strcmp(wc,"END"))
				fprintf(fir,"(%s,%d)          \t %d\n","AD",2,lc);
			if(!strcmp(wc,"LTORG"))
				fprintf(fir,"(%s,%d)          \t %d\n","AD",3,lc);
			for(i=0;i<LTP;i++)
			{
				lit[i].add=lc;
				fprintf(fir,"          ='%c' \t %d\n",lit[i].name,lc);
				lc++;
			}
			if(!strcmp(wc,"END"))
			{
				fprintf(fir,"                    \t %d\n",lc);
				break;
			}			
		}

		lc++;
		fprintf(fir,"\n");
	}
	//print databases
	printf("\n DATABASE:-");
	printf("\n\n1] SYMBOL TABLE:\n------------------\nSYMBOL NO.\tSYMBOL\tADDRESS");
	for(i=0;i<STP;i++)
		printf("\n %d          \t %s\t%d",i,sy[i].name,sy[i].add);
	printf("\n\n2] LITERAL TABLE:\n------------------\nLITERAL NO.\tLITERAL\tADDRESS");
	for(i=0;i<LTP;i++)
		printf("\n %d           \t %c\t%d",i,lit[i].name,lit[i].add);
	printf("\n");
	fclose(fir); //close files opened
	fclose(fip);
	return 0;
}


int isInMot(char temp[10])
{
	int i,flag=0;
	for(i=0;i<11;i++)
	{
		if(!strcmp(temp,mot[i]))
			flag=1;
	}
	return flag;
}
int isInPot(char temp[10])
{
	int i,flag=0;
	for(i=0;i<6;i++)
	{
		if(!strcmp(temp,pot[i]))
			flag=1;
	}
	return flag;
}
