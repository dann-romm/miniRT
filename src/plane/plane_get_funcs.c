#include "objects/plane.h"

t_color	get_color_plane(const void *data, const t_point3d intersection_point)
{
	return (((t_plane *)data)->color);
}

t_vector3d	get_normal_vector_plane(const void *data, const t_point3d intersection_point)
{
	return (((t_plane *)data)->normal);
}

t_material	get_material_plane(const void *data, const t_point3d intersection_point)
{
	return (((t_plane *)data)->material);
}

t_point3d	get_min_boundary_point_plane(const void *data)
{
	return (NEGATIVE_INFINITY_POINT3D);
}

t_point3d	get_max_boundary_point_plane(const void *data)
{
	return (POSITIVE_INFINITY_POINT3D);
}
