#ifndef UTILS_H
# define UTILS_H

# include <math.h>
# include "render.h"


t_vector3d	cross_product(const t_vector3d a, const t_vector3d b)
{
	return vector3df(a.z * b.y - a.y * b.z,
		a.x * b.z - a.z * b.x,
		a.y * b.x - a.x * b.y);
}

double	dot_product(const t_vector3d v1, const t_vector3d v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

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
	return (dot_product(v1, v2) / sqrt(sqr_module_vector(v1) * sqr_module_vector(v2)));
}

void	normalize_vector(t_vector3d *const v)
{
	const double	module = module_vector(*v);

	v->x = v->x / module;
	v->y = v->y / module;
	v->z = v->z / module;
}

t_vector3d	reflect_ray(
	const t_vector3d incident_ray,
	const t_vector3d norm_v)
{
	const double	k = 2 * dot_product(incident_ray, norm_v) / sqr_module_vector(norm_v);

	const double	x = incident_ray.x - norm_v.x * k;
	const double	y = incident_ray.y - norm_v.y * k;
	const double	z = incident_ray.z - norm_v.z * k;

	return (vector3df(x, y, z));
}

// TODO: use matrixes
t_point3d	rotate_point_x(
	const t_point3d p,
	const double sin_al,
	const double cos_al)
{
	const double y = p.y * cos_al - p.z * sin_al;
	const double z = p.y * sin_al + p.z * cos_al;

	return (point3d(p.x, y, z));
}

t_point3d	rotate_point_y(
	const t_point3d p,
	const double sin_al,
	const double cos_al)
{
	const double	x = p.x * cos_al - p.z * sin_al;
	const double	z = p.x * sin_al + p.z * cos_al;

	return (point3d(x, p.y, z));
}

t_point3d	rotate_point_z(
	const t_point3d p,
	const double sin_al,
	const double cos_al)
{
	const double	x = p.x * cos_al - p.y * sin_al;
	const double	y = p.x * sin_al + p.y * cos_al;

	return (point3d(x, y, p.z));
}

// TODO: use matrixes
t_vector3d	rotate_vector_x(
	const t_vector3d p,
	const double sin_al,
	const double cos_al)
{
	const double	y = p.y * cos_al - p.z * sin_al;
	const double	z = p.y * sin_al + p.z * cos_al;

	return (vector3df(p.x, y, z));
}

t_vector3d	rotate_vector_y(
	const t_vector3d p,
	const double sin_al,
	const double cos_al)
{
	const double	x = p.x * cos_al - p.z * sin_al;
	const double	z = p.x * sin_al + p.z * cos_al;

	return (vector3df(x, p.y, z));
}

t_vector3d	rotate_vector_z(
	const t_vector3d p,
	const double sin_al,
	const double cos_al)
{
	const double	x = p.x * cos_al - p.y * sin_al;
	const double	y = p.x * sin_al + p.y * cos_al;

	return (vector3df(x, y, p.z));
}

#endif
