// CPP Program to find the order 
// of programs for which MRT is 
// minimized 
#include <bits/stdc++.h> 

using namespace std; 


// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 

// This functions outputs the required 
// order and Minimum Retrieval Time 
void findOrderMRT(int L[], int n) 
{ 
	// Here length of i'th program is L[i] 
	mergeSort(L,0,n); 

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

