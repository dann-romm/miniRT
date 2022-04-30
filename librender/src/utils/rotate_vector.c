#include "utils.h"

t_vector3d	rotate_vector_x(const t_vector3d p,
	const double sin_al, const double cos_al)
{
	const double	y = p.y * cos_al - p.z * sin_al;
	const double	z = p.y * sin_al + p.z * cos_al;

	return (vector3df(p.x, y, z));
}

t_vector3d	rotate_vector_y(const t_vector3d p,
	const double sin_al, const double cos_al)
{
	const double	x = p.x * cos_al - p.z * sin_al;
	const double	z = p.x * sin_al + p.z * cos_al;

	return (vector3df(x, p.y, z));
}

t_vector3d	rotate_vector_z(const t_vector3d p,
	const double sin_al, const double cos_al)
{
	const double	x = p.x * cos_al - p.y * sin_al;
	const double	y = p.x * sin_al + p.y * cos_al;

	return (vector3df(x, y, p.z));
}
