double* linspace10(double x1, double x2)
{
	const int n = 10;
	static double linsp_10[10]; //sizeof(linsp_10)/sizeof(linsp_10[0]) should be the same as n
	int i = 0;
	double d = (x2 - x1) / (n - 1);
	for (i = 0; i < n; i++)
	{
		linsp_10[i] = x1 + i * d;
	}
	return linsp_10;
}


/* 
// test of linspace10
#include <stdio.h>
#include "linspace10.h"
int main()
{
        double x1 = 0;
	double x2 = 1;
	int i = 0;
	double *t1;

	t1 = linspace10(x1, x2);
	for (i = 0; i < 10; i++)
	{
		printf("*(t1 + %d) : %f\n", i, *(t1 + i));
	}
	*/
	return 0;
}
*/
