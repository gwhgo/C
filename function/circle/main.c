#include <stdio.h>
#include <math.h>
/*
	double distance(double x1, double y1, double x2, double y2)
	{
		double dx = x2 - x1;
		double dy = y2 - y1;
		//printf("dx is %f\ndyis %f\n",dx,dy);
		double dsquared = dx*dx + dy*dy;
		//printf("dsquared is %f\n", dsquared);
		double result = sqrt(dsquared);
		return result;
	}
*/

double distance(double x1, double y1, double x2, double y2)
{
	double dx = x2 - x1;
	double dy = y2 - y1;
	return sqrt(dx*dx + dy*dy);
}



double area(double radius)
{
	return 3.1416 * radius * radius;
}

int main(void)
{
	double radius = distance(1.0,2.0,4.0,6.0);
	printf("distance is %f\n",radius);
	double result = area(radius);
	printf("area is %f\n", result);
	return 0;
}
