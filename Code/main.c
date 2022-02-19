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
	int temp2 = 0;
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


// 3. basisfun
double** basisfun(int s[], double uv[],int num_uv, int p, double U[])
{
	/*
	 basicfun:  Basis function for B-Spline

	 Meaning of the input:
	 s - knot span (from findspan() )
	 uv - parametric points
	 p - spline degree
	 U - knot sequence

	 Meaning of the output:
	 b - Basis functions vector
	*/

	int i;
	double **basisf1;
	basisf1 = (double **)malloc(sizeof(double *)*num_uv);
	for (int i = 0; i < num_uv; i++)
	{
		basisf1[i] = (double *)malloc(sizeof(double)*(p+1));
	}
	double u;
	double** left;
	left = (double**)malloc((p+1) * sizeof(double*));
	for (int i = 0; i < (p + 1); i++)
	{
		left[i] = (double*)malloc(sizeof(double)*1);
	}
	double** right;
	right = (double**)malloc((p + 1) * sizeof(double*));
	for (int i = 0; i < (p + 1); i++)
	{
		right[i] = (double*)malloc(sizeof(double)*1);
	}
	double* n;
	n = (double*)malloc(sizeof(double) * (p+1));
	double saved;
	int r;
	double temp = 0;

	for (int jj = 1; jj < (num_uv + 1); jj++)
	{
		i = s[jj - 1] + 1;
		u = uv[jj - 1];
		n[0] = 1;
		for (int j = 1; j < (p + 1); j++)
		{
			left[j][0] = u - U[i - j];
			right[j][0] = U[i + j - 1] - u;
			saved = 0;
			for (r = 0; r < j; r++)
			{
				temp = n[r] / (right[r + 1][0] + left[j - r][0]);
				n[r] = saved + right[r + 1][0] * temp;
				saved = left[j - r][0] * temp;
			}
		n[j] = saved;
		}
	    basisf1[jj - 1][0] = n[0];
	    basisf1[jj - 1][1] = n[1];
	    basisf1[jj - 1][2] = n[2];
	}
	return basisf1;
}




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


	/*
	// 3. test of basisfun
	int n = 3;
	double U[7] = {0, 0, 0, 0.5, 1, 1, 1};
	int p = 2;
	int i;
	int num = 10;
	double* u;
	double* temp1;
	u = (double*)malloc(sizeof(double) * num);
	temp1 = linspace(0, 1, num);
	for (i = 0; i < num; i++)
	{
		u[i] = *(temp1 + i);
		printf("u[%d] is %f\n", i, u[i]);
	}
	int num_u = num;
	int num_U = 7;
	int* temp2;
	int* s;
	s = (double*)malloc(sizeof(double) * num);
    temp2 = findspan(n, p, u, num_u, U, num_U);
	for (i = 0; i < num_u; i++)
	{
		s[i] = *(temp2 + i);
		printf("s[%d] is %d\n", i, s[i]);
	}
	double** temp3;
	double** b;
	b = (double**)malloc(num_u * sizeof(double*));
	for (int i = 0; i < num_u; i++)
	{
		b[i] = (double*)malloc((p+1)*sizeof(double));
	}
	int num_uv = num;
	int j = 0;
	temp3 = basisfun(s, u, num_uv, p, U);
	for (i = 0; i < num_uv; i++)
	{
		for (j = 0; j < (p + 1); j++)
		{
			b[i][j] = *(*(temp3 + i) + j);
			printf("b[%d][%d] is %f\n", i, j, b[i][j]);
		}
	}
	//  should be [[1.           0.           0. ]
    //             [0.60493827   0.37037037   0.02469136]
    //             [0.30864198   0.59259259   0.09876543]
    //             [0.11111111   0.66666667   0.22222222]
    //             [0.01234568   0.59259259   0.39506173]
    //             [0.39506173   0.59259259   0.01234568]
    //             [0.22222222   0.66666667   0.11111111]
    //             [0.09876543   0.59259259   0.30864198]
    //             [0.02469136   0.37037037   0.60493827]
    //             [0.           0.           1.        ]]
    */





	return 0;
}

