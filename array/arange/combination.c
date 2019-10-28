#include <stdio.h>

void combinationUtil(int arr[], int data[], int start, int end, int index, int r);

// The main function that prints all combinations of size r 
// // in arr[] of size n. This function mainly uses combinationUtil() 
void printCombination(int arr[],int n, int r)
{
	int data[r];
	combinationUtil(arr,data,0,n-1,0,r);
}

/* arr[] ---> Input Array
 * data[] ---> Temporary array to store current combinatin
 * start & end --> Starting and Endind indexes in arr[]
 * index ---> Current index in data[]
 * r ---> Size of a combination to be printed */
void combinationUtil(int arr[], int data[], int start, int end, int index, int r)
{
	//Current combination is ready to be printed, print it
	if(index == r)
	{
		for(int j = 0; j < r;j++)
			printf("%d ",data[j]);
		printf("\n");
		return;
	}
	for (int i = start; i <= end && end -i+1 >= index; i++)
	{
		data[index] = arr[i];
		combinationUtil(arr,data,i+1,end,index+1,r);
	}
}

//Driver program to test above functions
int main()
{
		int arr[] = {1,2,3,4,5};
		int r = 3;
		int n = sizeof(arr)/sizeof(arr[0]);
		printCombination(arr,n,r);
}
