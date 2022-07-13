#include <math.h>
#include "objects/sphere.h"
#include "utils_math.h"

t_bool	intersect_sphere(const void *data, const t_point3d vector_start,
	const t_vector3d vector, t_point3d *intersection_point)
{
	const t_sphere		*sphere = (t_sphere *)data;
	const t_vector3d	v = vector3dp(sphere->center, vector_start);
	double				x1;
	double				x2;
	t_bool				is_solved;

	is_solved = solve_quadratic(dot_product(vector, vector),
			2 * dot_product(vector, v),
			dot_product(v, v) - (sphere->radius * sphere->radius), &x1, &x2);
	if (!is_solved)
		return (FALSE);
	if (x1 > x2)
	{
		x1 += x2;
		x2 = x1 - x2;
		x1 -= x2;
	}
	if (x1 <= EPSILON)
		x1 = x2;
	if (x1 < EPSILON)
		return (FALSE);
	*intersection_point = point3d(vector_start.x + vector.x * x1,
			vector_start.y + vector.y * x1, vector_start.z + vector.z * x1);
	return (TRUE);
}
