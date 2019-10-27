#include <stdio.h> 
#include <string.h> 
#define N 10

int a[N];

void init(int a[])
{
	for(int i = 0; i < N; i++)
		a[i] = i+1;	
}

void print(int a[])
{
	for(int i = 0; i < N-1;i++)
		printf("%d-",a[i]);
	printf("%d\n",a[N-1]);
}
/* Function to swap values at two pointers */
void swap(int* x, int* y) 
{ 
	int temp; 
	temp = *x; 
	*x = *y; 
	*y = temp; 
} 

/* Function to print permutations of string 
 * This function takes three parameters: 
 * 1. String 
 * 2. Starting index of the string 
 * 3. Ending index of the string. */
void permute(int* a, int l, int r) 
{ 
	int i; 
	if (l == r) 
		print(a);
		//return ;
	else { 
		for (i = l; i <= r; i++) { 
			swap((a + l), (a + i)); 
			permute(a, l + 1, r); 
			swap((a + l), (a + i)); // backtrack 
		} 
	} 
} 

/* Driver program to test above functions */
int main() 
{ 
	init(a);
	permute(a, 0, N - 1); 
	return 0; 
} 

