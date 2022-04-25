#include "utils.h"

t_vector3d	cross_product(const t_vector3d a, const t_vector3d b)
{
	return (vector3df(a.z * b.y - a.y * b.z,
			a.x * b.z - a.z * b.x,
			a.y * b.x - a.x * b.y));
}

double	dot_product(const t_vector3d v1, const t_vector3d v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
