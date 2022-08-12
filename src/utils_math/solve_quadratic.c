# include <math.h>
# include "bool.h"
# include <stdio.h>

t_bool	solve_quadratic(double a, double b, double c, double *x1, double *x2)
{
	double	sqrt_delta;
	double	x;
	double	y;

	sqrt_delta = sqrt(b * b - 4 * a * c);
	if (isnan(sqrt_delta))
		return (FALSE);

	if (x1)
		*x1 = (-b + sqrt_delta) / (2 * a);
	if (x2)
		*x2 = (-b - sqrt_delta) / (2 * a);
	return (TRUE);
}
