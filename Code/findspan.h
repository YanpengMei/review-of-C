#include <stdio.h>

int * findspan(int n, int p, double u[], double U[])
{
    /*
     Updated on : 16.02.2022

     findspan: find the knot span index

     Meaning of the input:
     n - number of control points - 1
     p - spline degree
     u - parametric point
     U - knot sequence

     Meaning of the output:
     span1 - knot span index
     */

    static int span1[10];
    int temp2;
    int i = 0;
    int j = 0;

    for (j = 0; j < 10; j++)
    {
        if (u[j] == U[n + 1])
        {
            span1[j] = n;
            continue;
        }
        
        for (i = 0; i < 9; i++)
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

    /*
    // test of findspan
    int n = 5;
    int p = 2;
    double U[9] = {0, 0, 0, 0.25, 0.5, 0.75, 1, 1, 1};
    double x1 = 0;
    double x2 = 1;
    int i = 0;
    int* t2;
    double* temp_u;
    double u[10];
    int t3[10];

    temp_u = linspace10(x1, x2);
    for (i = 0; i < (sizeof(u)/sizeof(u[0])); i++)
    {
        u[i] = *(temp_u + i);
        printf("%f\n", u[i]);
    }

    t2 = findspan(n, p, u, U);
    for (i = 0; i < 10; i++)
    {
        t3[i] = *(t2 + i);
        printf("%d\n", t3[i]);
    }
    // t3 should be[2 2 2 3 3 4 4 5 5 5]
    */