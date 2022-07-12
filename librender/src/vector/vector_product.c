#include "vector.h"

t_vector3d	cross_product(const t_vector3d v1, const t_vector3d v2)
{
	return (vector3df(v1.z * v2.y - v1.y * v2.z,
			v1.x * v2.z - v1.z * v2.x,
			v1.y * v2.x - v1.x * v2.y));
}

double	dot_product(const t_vector3d v1, const t_vector3d v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
