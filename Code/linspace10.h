double* linspace10(double x1, double x2)
{
	const int n = 10;
	static double linsp_10[10]; //sizeof(linsp_10) should be the same as n
	int i = 0;
	double d = (x2 - x1) / (n - 1);
	for (i = 0; i < n; i++)
	{
		linsp_10[i] = x1 + i * d;
	}
	return linsp_10;
}