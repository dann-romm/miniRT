#include "utils_math.h"

double min_double(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double max_double(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}
