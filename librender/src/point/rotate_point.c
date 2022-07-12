#include "point.h"

t_point3d	rotate_point_x(const t_point3d p,
	const double sin_al, const double cos_al)
{
	const double	y = p.y * cos_al - p.z * sin_al;
	const double	z = p.y * sin_al + p.z * cos_al;

	return (point3d(p.x, y, z));
}

t_point3d	rotate_point_y(const t_point3d p,
	const double sin_al, const double cos_al)
{
	const double	x = p.x * cos_al - p.z * sin_al;
	const double	z = p.x * sin_al + p.z * cos_al;

	return (point3d(x, p.y, z));
}

t_point3d	rotate_point_z(const t_point3d p,
	const double sin_al, const double cos_al)
{
	const double	x = p.x * cos_al - p.y * sin_al;
	const double	y = p.x * sin_al + p.y * cos_al;

	return (point3d(x, y, p.z));
}
