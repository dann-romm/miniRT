#include <math.h>
#include "objects/cylinder.h"

t_color	get_color_cylinder(const void *data, const t_point3d intersection_point)
{
	return (((t_cylinder *)data)->color);
}

t_vector3d	get_normal_vector_cylinder(const void *data, const t_point3d intersection_point)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)data;

	t_vector3d	center_to_cap = multiply_vector(cylinder->vector, cylinder->height / 2);
	t_point3d	top_cap_center = point3d(cylinder->center.x + center_to_cap.x, cylinder->center.y + center_to_cap.y, cylinder->center.z + center_to_cap.z);
	t_point3d	bottom_cap_center = point3d(cylinder->center.x - center_to_cap.x, cylinder->center.y - center_to_cap.y, cylinder->center.z - center_to_cap.z);

	if (module_vector(vector3dp(top_cap_center, intersection_point)) < cylinder->radius)
		return (cylinder->vector);
	else if (module_vector(vector3dp(bottom_cap_center, intersection_point)) < cylinder->radius)
		return (multiply_vector(cylinder->vector, -1));
	else
	{
		double t = dot_product(vector3dp(bottom_cap_center, intersection_point), cylinder->vector);
		t_point3d pt = point3d(bottom_cap_center.x - cylinder->vector.x * t, bottom_cap_center.y - cylinder->vector.y * t, bottom_cap_center.z - cylinder->vector.z * t);
		t_vector3d normal = vector3dp(pt, intersection_point);
		normalize_vector(&normal);
		return (normal);
	}
}

t_material	get_material_cylinder(const void *data,
	const t_point3d intersection_point)
{
	return (((t_cylinder *)data)->material);
}

t_point3d	get_min_boundary_point_cylinder(const void *data)
{
	const double	l = sqrt(((t_cylinder *)data)->height / 2
			+ ((t_cylinder *)data)->radius);

	return (point3d(((t_cylinder *)data)->center.x - l,
			((t_cylinder *)data)->center.y - l,
			((t_cylinder *)data)->center.z - l));
}

t_point3d	get_max_boundary_point_cylinder(const void *data)
{
	const double	l = sqrt(((t_cylinder *)data)->height / 2
			+ ((t_cylinder *)data)->radius);

	return (point3d(((t_cylinder *)data)->center.x + l,
			((t_cylinder *)data)->center.y + l,
			((t_cylinder *)data)->center.z + l));
}
