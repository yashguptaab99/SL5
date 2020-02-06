// CPP Program to find the order 
// of programs for which MRT is 
// minimized 
#include <bits/stdc++.h> 

using namespace std; 

// This functions outputs the required 
// order and Minimum Retrieval Time 
void findOrderMRT(int L[], int n) 
{ 
	// Here length of i'th program is L[i] 
	sort(L, L + n); 

	// Lengths of programs sorted according to increasing 
	// lengths. This is the order in which the programs 
	// have to be stored on tape for minimum MRT 
	cout << "Optimal order in which programs are to be stored is: "; 
	for (int i = 0; i < n; i++) 
		cout << L[i] << " "; 
	cout << endl; 

	// MRT - Minimum Retrieval Time 
	double MRT = 0; 

	// for (int i = 0; i < n; i++) 
	// { 
	// 	int sum = 0; 
	// 	for (int j = 0; j <= i; j++) 
	// 		sum += L[j]; 
	// 	MRT += sum; 
	// } 

	//better way to use avoid two loops
	for (int i = 0; i < n; i++)
    	MRT += (n - i) * L[i];

	MRT /= n; 
	cout << "Minimum Retrieval Time of this order is " << MRT<< endl; 
} 

// Driver Code to test above function 
int main() 
{ 
	int L[] = { 2, 5, 4 }; 
	int n = sizeof(L) / sizeof(L[0]); 
	findOrderMRT(L, n); 
	return 0; 
} 

