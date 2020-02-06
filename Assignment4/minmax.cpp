/* structure is used to return two values from minMax() */
#include<stdio.h> 

struct pair 
{ 
	int min; 
	int max;
	int comparison; 
}; 

struct pair getMinMaxOptimal(int arr[], int low, int high) 
{ 
	struct pair minmax, mml, mmr;	 
	int mid; 
	minmax.comparison = 0;

	/* If there is only on element */
	if (low == high) 
	{ 
		minmax.max = arr[low]; 
		minmax.min = arr[low];	 
		return minmax; 
	}	 
	
	/* If there are two elements */
	if (high == low + 1) 
	{ 
		if (arr[low] > arr[high]) 
		{ 
			minmax.max = arr[low]; 
			minmax.min = arr[high];
			minmax.comparison++; 
		} 
		else
		{ 
			minmax.max = arr[high]; 
			minmax.min = arr[low];
			minmax.comparison++; 
		} 
		return minmax; 
	} 
	
	/* If there are more than 2 elements */
	mid = (low + high)/2; 
	mml = getMinMaxOptimal(arr, low, mid); 
	mmr = getMinMaxOptimal(arr, mid+1, high); 
	
	/* compare minimums of two parts*/
	if (mml.min < mmr.min) 
		minmax.min = mml.min; 
	else
		minmax.min = mmr.min;	 

	/* compare maximums of two parts*/
	if (mml.max > mmr.max) 
		minmax.max = mml.max; 
	else
		minmax.max = mmr.max;	 

	return minmax; 
} 


struct pair getMinMax(int arr[], int n) 
{ 
	struct pair minmax;      
  	int i; 
    minmax.comparison = 0;

  	/*If there is only one element then return it as min and max both*/
  	if (n == 1) 
  	{ 
    	minmax.max = arr[0]; 
    	minmax.min = arr[0];      
    	return minmax; 
  	}     
  
  	/* If there are more than one elements, then initialize min  
      and max*/
  	if (arr[0] > arr[1])   
  	{ 
    	minmax.max = arr[0]; 
    	minmax.min = arr[1];
		minmax.comparison++; 
  	}   
  	else
  	{ 
    	minmax.max = arr[1]; 
    	minmax.min = arr[0];
		minmax.comparison++; 
  	}     
  
  	for (i = 2; i<n; i++) 
  	{ 
    	if (arr[i] >  minmax.max)
		{
			minmax.max = arr[i];
			minmax.comparison++;
		}     			      
    	else if (arr[i] <  minmax.min) 
		{
    		minmax.min = arr[i];
			minmax.comparison++; 
		}	
				
  	} 
    
  	return minmax; 
} 

/* Driver program to test above function */
int main() 
{ 
	int arr[] = {1000, 11, 445, 1, 330, 3000};
	int arr_size = 6; 

	struct pair minmax1 = getMinMaxOptimal(arr, 0, arr_size-1); 
	printf("\n-------------Optimal result-------------");
	printf("\n\tMinimum element is %d", minmax1.min); 
	printf("\n\tMaximum element is %d", minmax1.max);
	printf("\n\tComparisons %d",minmax1.comparison); 

	struct pair minmax2 = getMinMax(arr, arr_size);
	printf("\n\n\n-------------Normal Linear result-------------"); 
	printf("\n\tMinimum element is %d", minmax2.min); 
	printf("\n\tMaximum element is %d", minmax2.max);
	printf("\n\tComparisons %d\n\n",minmax2.comparison);
	return 0; 
} 

