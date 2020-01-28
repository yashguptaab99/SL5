#include<stdio.h>
#include<string.h>
#include <stdlib.h>
char mot[15][6]={"STOP","ADD","SUB","MUL","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT","DS","DC"}; //Mnemonics Code Table
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
int isReg(char[10]);
int main()
{

	char wc[10],temps[20];	
	int POOL[10]={0},poolflag=0,pooltab=0;
	int lc,LTP=0,STP=1,i,j=0,k=0,litflag=0,m=0,tempb,flag=0,oldLC=0,val=0;
	FILE *fip,*fir;
	fip=fopen("input.asm","r"); //assembler input
	fir=fopen("ir.txt","w"); //Intermediate Representation
	sym=fopen("sym.txt","w");//symbol table
	lit=fopen("lit.txt","w");//literal table
	fscanf(fip,"%s",wc); //read input
	while(!feof(fip))
	{	
		up:
		//check start
		if(!strcmp(wc,"START")) //if start copy address(lc)
		{
			fscanf(fip,"%d",&lc);
			fprintf(fir,"(%s,%d) (%s,%d)     \t %d\n","AD",1,"C",lc,lc);
			fscanf(fip,"%s",wc); //read next
			goto up;
		}
		//check origin
		else if(!strcmp(wc,"ORIGIN")) //if ORIGIN copy address(lc)
		{
			fprintf(fir,"(%s,%d) ","AD",4);
			fscanf(fip,"%s",wc); //read next
			for(j=0;j<STP;j++)
			{
				//check if said symbol is present in symbol table
				if(!strcmp(sy[j].name,wc))
				{
					fprintf(fir,"(%s,%d)","S",j);
					fscanf(fip,"%s",wc); //read next
					if(!strcmp(wc,"+"))
					{
					    fprintf(fir,"%s",wc);
						fscanf(fip,"%s",wc); //read next
						fprintf(fir,"%s",wc);
						oldLC=lc;
						val=atoi(wc);
						lc=val+sy[j].add;
					}
					if(!strcmp(wc,"-"))
					{
					    fprintf(fir,"%s",wc);
						fscanf(fip,"%s",wc); //read next
						fprintf(fir,"%s",wc);
						oldLC=lc;
						val=atoi(wc);
						lc=sy[j].add-val;
					}
					fprintf(fir,"             \t %d/%d\n",oldLC,lc);
					fscanf(fip,"%s",wc); //read next
					goto up;
				}
			}
			val=atoi(wc);
			oldLC=lc;
			lc=val;
			fprintf(fir,"             \t %d/%d\n",oldLC,lc);
			fscanf(fip,"%s",wc); //read next
			goto up;
		}
		//check EQU
		else if(!strcmp(wc,"EQU"))
		{
			int value;
		    fprintf(fir,"(%s,%d) ","AD",5);  
			fscanf(fip,"%s",wc); //read next
			for(j=0;j<STP;j++)
			{
				//check if said symbol is present in symbol table
				if(!strcmp(sy[j].name,wc))
				{
					fprintf(fir,"(%s,%d)","S",j);
					fscanf(fip,"%s",wc); //read next
					if(!strcmp(wc,"+"))
					{
						fprintf(fir,"%s",wc);
						fscanf(fip,"%s",wc); //read next
						fprintf(fir,"%s",wc);
						val=atoi(wc);
						value=val+sy[j].add;
					}
					if(!strcmp(wc,"-"))
					{
						fprintf(fir,"%s",wc);
						fscanf(fip,"%s",wc); //read next
						fprintf(fir,"%s",wc);
						val=atoi(wc);
						value=sy[j].add-val;
					}
				}
			}
			for(j=0;j<STP;j++)
			{
				 //check if said symbol is present in symbol table
				if(!strcmp(sy[j].name,temps))
				{
					sy[j].add=value;
				}
			}
			fprintf(fir,"     \t %d\n",lc);
			fscanf(fip,"%s",wc); //read next
			goto up;

		}
		//check first is symbol
		if(!isInMot(wc) && !isInPot(wc) && !isReg(wc))
		{
			for(j=0;j<STP;j++)
			{
				//check if said symbol is present in symbol table
				if(!strcmp(sy[j].name,wc))
				{
					flag=1;
					sy[j].add=lc;
					strcpy(temps,sy[j].name);
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
		flag=0;

		//check if it is present in mnemonics table
		for(i=0;i<11;i++)
		{
			if(!strcmp(wc,mot[i]))
			{
				if(!strcmp(wc,"STOP"))//for STOP
				{
					fprintf(fir,"(%s,%d)          \t %d\n","IS",i,lc);
					fscanf(fip,"%s",wc);
					lc++;
					goto up;
				}	
				fprintf(fir,"(%s,%d) ","IS",i); //found in mot
				fscanf(fip,"%s",wc);
				for(j=0;j<4;j++) //now find register
					if(!strcmp(wc,r[j])){
						fprintf(fir,"(R,%d) ",j+1);
						fscanf(fip,"%s",wc);
					}	
				if(!strcmp(wc,"=")) //if = it is literal
				{
					k=1;
					litflag=0;
					fscanf(fip,"%s",wc);
					//check if said literal already present in literlar table
					for(j=poolflag;j<LTP;j++)
						if(lit[j].name==wc[k]) //if(!strcmp(lit[j].name,wc[k]))
						{
							litflag=1;
							fprintf(fir,"(%s,%d)\t %d\n","L",j,lc);
							lc++;
							fscanf(fip,"%s",wc); //read next
							goto up;
						} //else add new entry in Literal table
					if(litflag==0)
					{
						lit[LTP].name=wc[k];
						fprintf(fir,"(%s,%d)\t %d\n","L",LTP,lc);
						LTP++;
						lc++;
						fscanf(fip,"%s",wc); //read next
						goto up;
					}
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
							fscanf(fip,"%s",wc); //read next
							goto up;
						}
					} //else add new entry in symbol table
					if(flag==0)
					{
						strcpy(sy[STP].name,wc);
						fprintf(fir,"(%s,%d)\t %d\n","S",STP,lc);
						STP++;
						lc++;
						fscanf(fip,"%s",wc); //read next
						goto up;
					}
				}
			}
			//if it’s not there in mot then check for symbol definition [DC/DS]
			if(!strcmp(wc,"DS"))
			{
				fscanf(fip,"%d",&tempb);
				fprintf(fir,"(%s,%d) (C,%d)     \t %d\n","DL",2,tempb,lc);
				lc+=tempb;
				fscanf(fip,"%s",wc); //read next					
				goto up;
			}
			else if(!strcmp(wc,"DC"))
			{
				fscanf(fip,"%d",&tempb);
				fprintf(fir,"(%s,%d) (C,%d)     \t %d\n","DL",1,tempb,lc);
				lc++;
				fscanf(fip,"%s",wc); //read next
				goto up;
			}
		}

		//check for END or LTORG of assembly statements
		if(!strcmp(wc,"END") || !strcmp(wc,"LTORG"))
		{
			if(!strcmp(wc,"END"))
			{
				fprintf(fir,"(%s,%d)          \t %d\n","AD",2,lc);
			}
			if(!strcmp(wc,"LTORG"))
			{
				fprintf(fir,"(%s,%d)          \t %d\n","AD",3,lc);
			}
			for(i=poolflag;i<LTP;i++)
			{
				lit[i].add=lc;
				if(!strcmp(wc,"END"))
					fprintf(fir,"           ='%c' \t %d\n",lit[i].name,lc);
				lc++;
			}
			if(!strcmp(wc,"LTORG"))
			{
				fscanf(fip,"%s",wc); //read next
				pooltab++;
				poolflag=LTP;
				POOL[pooltab]=poolflag;
				goto up;				
			}
			if(!strcmp(wc,"END"))
			{
				fprintf(fir,"                    \t %d\n",lc);
				pooltab++;
				poolflag=LTP;
				POOL[pooltab]=poolflag;
				break;
			}			
		}
	}
	//print databases
	printf("\n DATABASE:-");
	printf("\n\n1] SYMBOL TABLE:\n------------------------------------\nSYMBOL NO.\tSYMBOL\tADDRESS");
	for(i=1;i<STP;i++)
		printf("\n %d          \t %s\t%d",i,sy[i].name,sy[i].add);
	printf("\n\n2] LITERAL TABLE:\n------------------------------------\nLITERAL NO.\tLITERAL\tADDRESS");
	for(i=0;i<LTP;i++)
		printf("\n %d           \t %c\t%d",i,lit[i].name,lit[i].add);
	printf("\n\n3]POOL TAB:\n------------------------------------\nPOOL NO.\tPOOL\n");
	for(i=0;i<poolflag+1;i++)
	        printf("%d\t\t%d\n",i,POOL[i]);
	
	fprintf(sym,"\n\n1] SYMBOL TABLE:\n------------------------------------\nSYMBOL NO.\tSYMBOL\tADDRESS");
	for(i=1;i<STP;i++)
		fprintf(sym,"\n %d          \t %s\t%d",i,sy[i].name,sy[i].add);
	fprintf(lit,"\n\n2] LITERAL TABLE:\n------------------------------------\nLITERAL NO.\tLITERAL\tADDRESS");
	for(i=0;i<LTP;i++)
		fprintf(lit,"\n %d           \t %c\t%d",i,lit[i].name,lit[i].add);
	
	 //close files opened
	fclose(sym);
	fclose(lit);       
	fclose(fir);
	fclose(fip);
	return 0;
}


int isInMot(char temp[10])
{
	int i,flag=0;
	for(i=0;i<13;i++)
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
int isReg(char temp[10])
{
	int i,flag=0;
	for(i=0;i<6;i++)
	{
		if(!strcmp(temp,r[i]))
			flag=1;
	}
	return flag;
}
