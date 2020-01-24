#include<bits/stdc++.h>
using namespace std;
#define pb push_back
int it=1;
/*void directans(int n, int chess[][n]){
	int pre=1;
	for(int i=0;i<n;i++){
		chess[pre][i]=1;
		pre+=2;
		if(pre>=n)
			pre=0;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			if(chess[i][j]==1)
				cout<<"Q|";
			else
				cout<<" |";
		cout<<"\n";
		for(int j=0;j<n;j++)
			cout<<"-+";
		cout<<"\n";
	}
}*/

bool isSafe(int row, int col, vector< vector<int> > chess, int n){
	for(int i=0;i<col;i++)
		if(chess[row][i]==1)
			return false;
	for(int i=row, j=col;i>=0 && j>=0; i--, j--)
		if(chess[i][j]==1)
			return false;
	for(int i=row, j=col;i<n && j>=0;i++, j--)
		if(chess[i][j]==1)
			return false;
}

void printt(vector<vector<int> > chess, int n){
	for(int j=0;j<n;j++)
		cout<<"-+";
	cout<<"\n";
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			if(chess[i][j]==1)
				cout<<"Q|";
			else
				cout<<" |";
		cout<<"\n";
		for(int j=0;j<n;j++)
			cout<<"-+";
		cout<<"\n";
	}
	cout<<"\n";
	for(int j=0;j<n;j++)
		cout<<"-+";
	cout<<"\n";
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			if(chess[j][i]==1)
				cout<<"Q|";
			else
				cout<<" |";
		cout<<"\n";
		for(int j=0;j<n;j++)
			cout<<"-+";
		cout<<"\n";
	}
}

void printtt(vector<vector<int> > chess, int n, int row, int col){
	cout<<"Iteration "<<it<<endl;
	it++;
	for(int j=0;j<n;j++)
		cout<<"-+";
	cout<<"\n";
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			if(chess[i][j]==1)
				cout<<"Q|";
			else if(i==row && j==col)
				cout<<":|";
			else
				cout<<" |";
		cout<<"\n";
		for(int j=0;j<n;j++)
			cout<<"-+";
		cout<<"\n";
	}
}

bool count(vector< vector<int> > chess, int n)
{
	int count;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(chess[i][j]==1)
				count++;
	if(count==n)
		return true;
	else
		return false;
}

bool solve(vector< vector<int> > chess, int col, int n){
	if(col>=n)
		return true;

	for(int i=0;i<n;i++){
		printtt(chess,n,i,col);
		if(isSafe(i,col,chess,n)){
			chess[i][col]=1;
			if(solve(chess,col+1,n)){
				if(count(chess,n))
					printt(chess,n);
				return true;
			}
			chess[i][col]=0;
		}
	}
	return false;
}

int main(){
	int n;
	cin>>n;
	vector< vector<int> > chess(n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			chess[i].pb(0);
	for(int i=0;i<n;i++){
		if(solve(chess, i, n)){
			cout<<"\n";
			break;
		}
	}
}