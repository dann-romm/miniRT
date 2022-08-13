#include <stdlib.h>
#include "objects/plane.h"

t_object3d	*new_plane(t_point3d point, t_vector3d normal, t_color color)
{
	t_plane		*plane;
	t_object3d	*plane_object;

	plane = (t_plane *)malloc(sizeof(t_plane));
	plane->point = point;
	plane->normal = normal;
	plane->color = color;
	plane->material = DEFAULT_MATERIAL;
	plane_object = (t_object3d *)malloc(sizeof(t_object3d));
	plane_object->data = plane;
	plane_object->intersect = intersect_plane;
	plane_object->get_color = get_color_plane;
	plane_object->get_normal_vector = get_normal_vector_plane;
	plane_object->get_material = get_material_plane;
	plane_object->get_min_boundary_point = get_min_boundary_point_plane;
	plane_object->get_max_boundary_point = get_max_boundary_point_plane;
	plane_object->release_data = release_data_plane;
	return (plane_object);
}

void	release_data_plane(void *data)
{
	free((t_plane *)data);
}
