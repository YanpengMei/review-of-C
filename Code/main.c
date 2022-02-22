#include <stdio.h>
#include <stdlib.h>
// updated on 21.Feb.2022


// 1. linspace
double* linspace(double x1, double x2, int n)
{
	// linspace - just like the functionin Matlab or Python(numpy)
	int i = 0;
	double* linsp1;
	linsp1 = (double*)malloc(sizeof(double) * n);

	double d = (x2 - x1) / (n - 1); // d - step size
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
		left[i] = (double*)malloc(sizeof(double));
	}
	double** right;
	right = (double**)malloc((p + 1) * sizeof(double*));
	for (int i = 0; i < (p + 1); i++)
	{
		right[i] = (double*)malloc(sizeof(double));
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
		for (int k = 0; k < (p + 1); k++)
		{
	    basisf1[jj - 1][k] = n[k];
        }
	}
	return basisf1;
}
// end of basisfun


// 4. bspeval
double** bspeval(int p, double cp[][2], int num_cp, double U[], int num_U, double u[], int num_u)
{
	/*
	bspeval: evaluate B - Spline at parametric points

	Meaning of the input :
	p - Degree of the B - Spline.
	cp - Control Points
	     first column of 'cp' is x-value of each control points
		 second column of 'cp' is y-value of each control points
	num_cp - number of columns of cp
	U - Knot sequence
	u - Parametric evaluation points.
	num_u - number of elements in u
	
	Meaning of the output :
	pnt - Evaluated points in xy-coordinate
	*/

	int i, j;
	double** pnt;
	pnt = (double**)malloc(sizeof(double*) * 2);
	for (int i = 0; i < 2; i++)
	{
		pnt[i] = (double*)malloc(sizeof(double) * num_u);
	}

	int* temp1; // get s
	int* s;
	int n = num_cp - 1;
	s = (double*)malloc(sizeof(double) * num_u);
	temp1 = findspan(n, p, u, num_u, U, num_U);
	for (i = 0; i < num_u; i++)
	{
		s[i] = *(temp1 + i);
		//printf("s[%d] is %d\n", i, s[i]);
	}

	double** temp2; // get b
	double** b;
	b = (double**)malloc(num_u * sizeof(double*));
	for (int i = 0; i < num_u; i++)
	{
		b[i] = (double*)malloc((p + 1) * sizeof(double));
	}
	temp2 = basisfun(s, u, num_u, p, U);
	for (i = 0; i < num_u; i++)
	{
		for (j = 0; j < (p + 1); j++)
		{
			b[i][j] = *(*(temp2 + i) + j);
		}
	}

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < num_u; j++)
		{
			pnt[i][j] = 0;
		}
	}

	int* temp3; 
	temp3 = (double*)malloc(sizeof(double) * num_u);
	for (i = 0; i < num_u; i++)
	{
		temp3[i] = s[i] - p;
	}

	double temp4; // get the evaluated points
	for (i = 0; i < (p+1); i++)
	{
		for (j = 0; j < num_u; j++)
		{
			temp4 = b[j][i];
			printf("temp4[%d] is %f\n", j, temp4);
			pnt[0][j] = pnt[0][j] + temp4 * cp[temp3[j] + i][0];
			pnt[1][j] = pnt[1][j] + temp4 * cp[temp3[j] + i][1];
		}
	}
		return pnt;
}
// end of bspeval


// 5. bspderiv
double** bspderiv(int p, double cp[][2], int num_cp, double U[], int num_U)
{
	/*
	bspderiv - B-Spline derivative

    Meaning of the input:
    p - degree of the B-Spline
    cp - control points
    U - knot sequence

    Meaning of the output:
    d_cp_U - control points and knot sequence of the derivative
	*/

    int i, j;
	double** d_cp_U; 
	// first (num_cp - 1) rows of 'd_cp_U' is control points of the derivative
	// last row of 'd_cp_U' is knot sequence of the derivative
	d_cp_U = (double**)malloc(num_cp * sizeof(double*));
	for (int i = 0; i < num_cp; i++)
	{
		d_cp_U[i] = (double*)malloc((num_U - 2) * sizeof(double));
	}

	double temp1;
	for (i = 0; i < (num_cp - 1); i++)
	{
		temp1 = p / (U[i + p + 1] - U[i + 1]);
		for (j = 0; j < 2; j++)
		{
		d_cp_U[i][j] = temp1 * (cp[i + 1][j] - cp[i][j]);
		}
	}

	for (i = 0; i < (num_U - 2); i++)
	{
		d_cp_U[num_cp - 1][i] = U[i + 1];
	}

	return d_cp_U;
}
    // end of bspderiv



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
	double *u;
	u = (double*)malloc(sizeof(double) * num);
	temp1 = linspace(x1, x2, num);
	for (i = 0; i < num; i++)
	{
		u[i] = *(temp1 + i);
	}

	int* temp2;
	int *temp3;
	temp3 = (int*)malloc(sizeof(int) * num);
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

	// b should be [[1.           0.           0. ]
    //              [0.60493827   0.37037037   0.02469136]
    //              [0.30864198   0.59259259   0.09876543]
    //              [0.11111111   0.66666667   0.22222222]
    //              [0.01234568   0.59259259   0.39506173]
    //              [0.39506173   0.59259259   0.01234568]
    //              [0.22222222   0.66666667   0.11111111]
    //              [0.09876543   0.59259259   0.30864198]
    //              [0.02469136   0.37037037   0.60493827]
    //              [0.           0.           1.        ]]
    */


    /*
    // 4. test of bspeval
    int p = 3;
	double cp[6][2] = {{0,   0}, {10,  5}, {20, -5}, {30,  5}, {40, -5}, {50,  0}};
	int num_cp = 6;
	double U[10] = { 0, 0, 0, 0, 0.333, 0.667, 1, 1, 1, 1 };
	int num_U = 10;
	int num_u = 10;
	int i, j;
	double* u;
	double* temp1;
	u = (double*)malloc(sizeof(double) * num_u);
	temp1 = linspace(0, 1, num_u);
	for (i = 0; i < num_u; i++)
	{
		u[i] = *(temp1 + i);
		printf("u[%d] is %f\n", i, u[i]);
	}

	double** temp2;
	double** pnt;
	pnt = (double**)malloc(2 * sizeof(double*));
	for (int i = 0; i < 2; i++)
	{
		pnt[i] = (double*)malloc(num_u * sizeof(double));
	}

	temp2 = bspeval(p, cp, num_cp, U, num_U, u, num_u);
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < num_u; j++)
		{
			pnt[i][j] = *(*(temp2 + i) + j);
			printf("pnt[%d][%d] is %f\n", i, j, pnt[i][j]);
		}
	}
	// pnt should be
    // [[0.  8.48765432  14.56790123  19.16666667  23.11728395  26.88271605  30.83333333  35.43209877  41.51234568  50.]
    //  [0.  2.19135802  0.86419753   -0.83333333  -0.58641975   0.58641975   0.83333333  -0.86419753  -2.19135802   0.]]
	*/



	// 5. test of bspderiv
    int i, j;
	int p = 3;
    double cp[6][2] = {{0,   0}, {10,  5}, {20, -5}, {30,  5}, {40, -5}, {50,  0}};
    double U[10] = { 0, 0, 0, 0, 0.333, 0.667, 1, 1, 1, 1 };
	int num_cp = 6;
	int num_U = 10;
	// first (num_cp - 1) rows of 'd_cp_U' is control points of the derivative
	// last row of 'd_cp_U' is knot sequence of the derivative

	double** d_cp;
	d_cp = (double**)malloc((num_cp - 1) * sizeof(double*));
	for (int i = 0; i < (num_cp - 1); i++)
	{
		d_cp[i] = (double*)malloc(2 * sizeof(double));
	}
	double* d_U;
	d_U = (double*)malloc((num_U - 2) * sizeof(double));
	
	double** temp1;
	temp1 = bspderiv(p, cp, num_cp, U, num_U);
	for (i = 0; i < (num_cp - 1); i++)
	{
		for (j = 0; j < 2; j++)
		{
			d_cp[i][j] = *(*(temp1 + i) + j);
			printf("d_cp[%d][%d] is %f\n", i, j, d_cp[i][j]);
		}
	}
	for (j = 0; j < (num_U - 2); j++)
	{
		d_U[j] = *(*(temp1 + (num_cp - 1)) + j);
		printf("d_U[%d] is %f\n", j, d_U[j]);
	}
	// d_cp should be {{90,45}, {45,-45}, {30,30}, {45,-45}, {90,45}}
    // d_U should be [0.   0.   0.   0.33333333    0.66666667    1.    1.   1.]
	






	return 0;
}

