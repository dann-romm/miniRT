#include <math.h>
#include "vector.h"

double	sqr_module_vector(const t_vector3d v)
{
	return (dot_product(v, v));
}

double	module_vector(const t_vector3d v)
{
	return (sqrt(sqr_module_vector(v)));
}

double	cos_vectors(const t_vector3d v1, const t_vector3d v2)
{
	return (dot_product(v1, v2)
		/ sqrt(sqr_module_vector(v1) * sqr_module_vector(v2)));
}

void	normalize_vector(t_vector3d *const v)
{
	const double	module = module_vector(*v);

	v->x = v->x / module;
	v->y = v->y / module;
	v->z = v->z / module;
}
