#include "objects/sphere.h"

t_color		get_color_sphere(const void *data, const t_point3d intersection_point)
{
	t_sphere	*sphere;
	
	sphere = (t_sphere *)data;
	return (sphere->color);
	// return (((t_sphere *)data)->color);
}

t_material	get_material_sphere(const void *data, const t_point3d intersection_point)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)data;
	return (sphere->material);
	// return (((t_sphere *)data)->material);
}

t_vector3d	get_normal_vector_sphere(const void *data, const t_point3d intersection_point)
{
	t_sphere	*sphere;
	t_vector3d	normal;

	sphere = (t_sphere *)data;
	normal = vector3dp(sphere->center, intersection_point);
	// normal = vector3dp(((t_sphere *)data)->center, intersection_point);
	normalize_vector(&normal);
	return (normal);
}

t_point3d	get_min_boundary_point_sphere(const void *data)
{
	t_sphere	*sphere;
	t_point3d	c;

	sphere = (t_sphere *)data;
	c = sphere->center;
	return (point3d(c.x - sphere->radius, c.y - sphere->radius, c.z - sphere->radius));
}

t_point3d	get_max_boundary_point_sphere(const void *data)
{
	t_sphere	*sphere;
	t_point3d	c;

	sphere = (t_sphere *)data;
	c = sphere->center;
	return (point3d(c.x + sphere->radius, c.y + sphere->radius, c.z + sphere->radius));
}
