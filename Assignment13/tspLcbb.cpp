#include<iostream>
#include<vector>
#include<limits.h>
#include<algorithm>
#include<bits/stdc++.h>
#include<iomanip>
#include <queue> 
using namespace std;

int upper = INT_MAX;
vector<int> finalPath;

class node
{
	public :
	 	int level;
	 	int* visited;
		int cost;
		int** mat;
		int vertex;
		int n;
		vector<int> path;	
			
		node(int n)
		{
			visited = new int[n];						
			mat = new int* [n];
			for(int i=0;i<n;i++)
			{
				mat[i] = new int[n];
				visited[i] = 0; 
			}
			this->n = n;
			cost = 0;
		}
		
		node(node* oldObj)
		{
			this->n = oldObj->n;
			
			visited = new int[n];						
			mat = new int* [n];
			for(int i=0;i<n;i++)
			{
				mat[i] = new int[n]; 
			}
			
			for(int i = 0;i < n;i++)
			{
				for(int j=0;j < n;j++)
				{
					this->mat[i][j] = oldObj->mat[i][j];
				}
				this->visited[i] = oldObj->visited[i];
			}
			
			for(int i=0;i<oldObj->path.size();i++)
			{
				path.push_back(oldObj->path.at(i));
			}
		} 
};

struct CompareCost { 
    bool operator()(node const& n1, node const& n2) 
    {  
        return n1.cost < n2.cost; 
    } 
}; 


bool myfunction(node i ,node j)
{
	return i.cost<j.cost;
}

//function to reduce row
int reduceRowMin(int** mat,node* Node,int index,int n)
{
	int min = INT_MAX;
	for(int j=0;j<n;j++)
	{
		if(mat[index][j] != INT_MAX)
		{
			if(min>mat[index][j])
			{
				min = mat[index][j];
			}
		}	
	}
	
	if(min != INT_MAX)
	{
		for(int j=0;j<n;j++)
		{
			if(mat[index][j] != INT_MAX)
			{
				Node->mat[index][j] = mat[index][j] - min;
			}
			else
				Node->mat[index][j] = INT_MAX;	 		
		}
		return min;
	}
	return 0;	
}

//function to reduce column
int reduceColumnMin(int** mat,node* Node,int index,int n)
{
	int min = INT_MAX;
	for(int j=0;j<n;j++)
	{
		if(mat[j][index] != INT_MAX)
		{
			if(min>mat[j][index])
			{
				min = mat[j][index];
			}
		}	
	}
	
	if(min != INT_MAX)
	{
		for(int j=0;j<n;j++)
		{
			if(mat[j][index] != INT_MAX)
			{
				Node->mat[j][index] = mat[j][index] - min;
			}	 		
		}
		return min;
	}
	return 0;		
}

//function to find reduction matrix
void reduceMatrix(int** mat,node* Node,int n)
{
	int reductionValue = 0,min;
	for(int i = 0;i<n;i++)
	{
		min = reduceRowMin(mat,Node,i,n);
		reductionValue += min;
	}
	
	for(int i = 0;i<n;i++)
	{
		min = reduceColumnMin(Node->mat,Node,i,n);
		reductionValue += min;
	}
	Node->cost += reductionValue;
}

//function to calculate min cost trip 
int tsp(node* liveNode,int n)
{
	if(liveNode->cost > upper)
	{
		return INT_MAX;
	}
	else
		upper = INT_MAX;
	
	if(liveNode->level == n)
	{
		finalPath.clear();
		for(int i = 0;i<liveNode->path.size();i++)
		{
			finalPath.push_back(liveNode->path.at(i));
		}
		upper = liveNode->cost;
		return liveNode->cost;
	}
		
	//prioirty queue used at each level to assign highest priority to the node with minimum cost	
	priority_queue<node,vector<node>,CompareCost> curNodes;
	
	int src = liveNode->vertex;
	node* newNode = NULL;
	int check;
	int min = INT_MAX;
	for(int i=0;i<n;i++)
	{
		if(liveNode->visited[i] == 0 && liveNode->mat[src][i] != INT_MAX)
		{
			newNode = new node(liveNode);
			newNode->level = liveNode->level+1;
			newNode->vertex = i;
			newNode->visited[i] = 1;
			newNode->cost = liveNode->cost;
			newNode->cost += liveNode->mat[src][i];
			newNode->path.push_back(i);
			for(int j=0;j<n;j++)
			{
				newNode->mat[src][j] = INT_MAX;
				newNode->mat[j][i] = INT_MAX;
			}
			newNode->mat[i][src] = INT_MAX;
			newNode->mat[i][0] = INT_MAX;
			reduceMatrix(newNode->mat,newNode,newNode->n);
			
			//cout<<"\nCost : "<<newNode->cost<<endl;
			curNodes.push(*newNode);		
		}
	}
	//sort(curNodes.begin(),curNodes.end(),myfunction);
	
	while(!curNodes.empty())
	{
		node topNode = curNodes.top();
		curNodes.pop();
		check = tsp(&topNode,n);
		if(check<min)
			min = check;		
	}
	return min;
}

int main()
{
	int n;
	int** adjMat;
	cout<<"\nENTER NO OF NODES : ";
	cin>>n;
	cout<<"\nENTER ADJ. MATRIX(0 for INF) : \n";
	
	vector<int> path;
	
	adjMat = new int* [n];
	for(int i=0;i<n;i++)
	{
		adjMat[i] = new int[n];
	}
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<"\nMAT["<<i<<"]["<<j<<"] : ";
			cin>>adjMat[i][j];
			if(adjMat[i][j] == 0)
			{
				adjMat[i][j] = INT_MAX;
			}
		}
	}
	cout<<"\nADJACENCY MATRIX : \n\n";	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<setw(15)<<left<<adjMat[i][j]<<"\t";
		}
		cout<<"\n\n";
	}
	
	node newNode(n);
	newNode.level = 1;
	newNode.visited[0] = 1;
	newNode.vertex = 0;
	reduceMatrix(adjMat,&newNode,n);
	newNode.path.push_back(0);
	int check = tsp(&newNode,n);
	cout<<"\nFinal Cost : "<<check<<"\n\n";
	cout<<"Final Path : ";
	finalPath.push_back(0);
	for(int i=0;i<finalPath.size();i++)
	{
		cout<<finalPath.at(i);
		if(i<finalPath.size()-1)
			cout<<"->";
	}
	cout<<"\n\n";
	return 0;
}





