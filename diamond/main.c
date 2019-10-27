#include <stdio.h>
#include <math.h>

int diamond(int k)
{	
	int m = (k+1)/2;
	for(int i = 1; i <= k; i++)
	{
		for(int j = 1; j <=k; j++)
		{
			int l = i;
			if (i > m) l = 2*m - i;
			if (fabs(j-m) < l) printf("*");
			else printf(" ");
		}
		printf("\n");
	}	
}

int main(void)
{
	diamond(9);
}
