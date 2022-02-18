#include <stdio.h>
#include <stdlib.h>
// updated on 18.Feb.2022


// 1. linspace
double* linspace(double x1, double x2, int n)
{
	/*linspace - just like the functionin Matlab or Python*/
	double* linsp1;
	int i = 0;
	linsp1 = (double*)malloc(sizeof(double) * n);

	double d = (x2 - x1) / (n - 1);
	for (i = 0; i < n; i++)
	{
		linsp1[i] = x1 + i * d;
	}
	return linsp1;
}
// end of linspace


// 2. findspan
int* findspan(int n, int p, double u[], int num_u, double U[], int num_U)
{
	/*
	 findspan: find the knot span index

	 Meaning of the input:
	 n - number of control points - 1
	 p - spline degree
	 u - parametric point
	 num_u - number of elements in u
	 U - knot sequence
	 num_U - number of elements in U

	 Meaning of the output:
	 span1 - knot span index
	 */

	int* span1;
	span1 = (int*)malloc(sizeof(int) * num_u);
	int temp2;
	int i = 0;
	int j = 0;

	for (j = 0; j < num_u; j++)
	{
		if (u[j] == U[n + 1])
		{
			span1[j] = n;
			continue;
		}

		for (i = 0; i < num_U; i++)
		{
			if (U[i] <= u[j])
			{
				temp2 = i;
			}
		}
		span1[j] = temp2;
	}
	return span1;
}
// end of findspan


int main()
{
	/*
	// 1. test of linspace
	double x1 = 0;
	double x2 = 1;
	const int n = 10;
	int i = 0;
	double* temp1;
	double* u;
	u = (double*)malloc(sizeof(double)*n);
	temp1 = linspace(x1, x2, n);
	for (i = 0; i < n; i++)
	{
		u[i] = *(temp1 + i);
		printf("%f\n", u[i]);
	}
	*/	


	/*
	// 2. test of findspan
	int n = 5;
	int p = 2;
	double U[9] = {0, 0, 0, 0.25, 0.5, 0.75, 1, 1, 1};
    int num = 10;
	int num_u = num;
	int num_U = 9;
	double x1 = 0;
	double x2 = 1;
	int i = 0;
    double* temp1;
	int* temp2;
	double *u;
	u = (double*)malloc(sizeof(double) * num);
	int *temp3;
	temp3 = (int*)malloc(sizeof(int) * num);
	temp1 = linspace(x1, x2, num);
	for (i = 0; i < num; i++)
	{
		u[i] = *(temp1 + i);
	}
	temp2 = findspan(n, p, u, num_u, U, num_U);
	for (i = 0; i < num; i++)
	{
		temp3[i] = *(temp2 + i);
		printf("temp3[%d] is %d\n", i, temp3[i]);
	}
	// t3 should be[2 2 2 3 3 4 4 5 5 5]
	*/



	return 0;
}

