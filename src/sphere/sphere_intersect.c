#include <math.h>
#include "objects/sphere.h"
#include "utils_math.h"

t_bool	intersect_sphere(const void *data, const t_point3d vector_start, const t_vector3d vector, t_point3d *intersection_point)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)data;

	t_vector3d	oc = vector3dp(sphere->center, vector_start);

	double	a = dot_product(vector, vector);
	double	b = 2 * dot_product(vector, oc);
	double	c = dot_product(oc, oc) - (sphere->radius * sphere->radius);

	double	x1 = nan(0);
	double	x2 = nan(0);

	solve_quadratic(a, b, c, &x1, &x2);

	if isnan(x1)
		return (FALSE);

	double	min_t;
	double	max_t;

	if (x1 < x2)
	{
		min_t = x1;
		max_t = x2;
	}
	else
	{
		min_t = x2;
		max_t = x1;
	}

	double t;
	if (min_t > EPSILON)
		t = min_t;
	else
		t = max_t;

	if (t < EPSILON)
		return (FALSE);
	
	*intersection_point = point3d(vector_start.x + vector.x * t, vector_start.y + vector.y * t, vector_start.z + vector.z * t);
	return (TRUE);
}
