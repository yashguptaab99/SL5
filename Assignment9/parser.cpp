

#include <iostream>
#include <stdlib.h>
using namespace std;

/*
GRAMMAR
declare -> type variable;
type -> int | float | char
variable -> id,variable | id
*/

//FUNCTION PROTOTYPES
int incr = 0;
int declare();
int type();
int variable();

string input;

//MAIN FUNCTION
int main() 
{
  cout<<"\n---------------------------------------\nDefined Grammar is::\n\ndeclare -> type variable;\ntype -> int | float | char\nvariable -> id,variable | id\n---------------------------------------";
  cout<<"\n\nEnter input string::";
  getline(cin,input);

  int length_str = input.length();
  input += "$";

  cout<<"\n----------STEPS----------";
  int d=declare();

  cout<<"\n-------------------------";
  if (length_str == incr && d==1)
    cout << "\n\nString is accepted" << endl;
  else
    cout << "\n\nString is rejected" << endl;
}

//FIRST STEP OF GRAMMAR
int declare()
{
	cout<<"\ndeclare -> type variable;";

	//CHECKING DATA TYPE OF VARIABLE
	int t=type();
	incr++;

	//CHECHING IF VARIABLE id
	int v=variable();

	//CHECKING FOR END ;
	if(input[incr]==';')
		incr++;

	//IF DATATYPE AND VARIABLE FOLLOW THE RULES THEN RETURN 1
	if(t==1 && v==1)
		return 1;
	else return 0;
}

//DATATYPE
int type()
{
	//INT
	if(input[incr]=='i')
	{
		incr++;
		if(input[incr]=='n')
		{
			incr++;
			if(input[incr]=='t')
			{
				incr++;
				cout<<"\ntype -> int";
				return 1;
			}
			else
			return -1;
		}
		else
		return -1;
	}

	//FLOAT
	else if(input[incr]=='f')
	{
		incr++;
		if(input[incr]=='l')
		{
			incr++;
			if(input[incr]=='o')
			{
				incr++;
				if(input[incr]=='a')
				{
					incr++;
					if(input[incr]=='t')
					{
						incr++;
						cout<<"\ntype -> float";
						return 1;
					}
					else
					return -1;
				}
				else
				return -1;
			}
			else
			return -1;
		}
		else
		return -1;
	}
	
	//CHAR
	else if(input[incr]=='c')
	{
		incr++;
		if(input[incr]=='h')
		{
			incr++;
			if(input[incr]=='a')
			{
				incr++;
				if(input[incr]=='r')
				{
					incr++;
					cout<<"\ntype -> char";
					return 1;
				}
				else
				return -1;
			}
			else
			return -1;
		}
		else
		return -1;
	}
	else
		return -1;
}

//VARIABLE
int variable()
{
	if(input[incr]=='i')
	{
		incr++;
		if(input[incr]=='d')
		{
			incr++;
			if(input[incr]==',')
			{
				incr++;
				cout<<"\nvariable -> id,variable";
				variable();
			}
			else
			{
				cout<<"\nvariable ->id";
				return 1;
			}
		}
		else
		return -1;
	}
	else
		return -1;
}

