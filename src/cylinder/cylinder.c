#include <stdlib.h>
#include "objects/cylinder.h"

t_object3d	*new_cylinder(double radius, double height, t_point3d center, t_vector3d vector, t_color color, t_material material)
{
	t_cylinder	*cylinder;
	t_object3d	*cylinder_object;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	cylinder->radius = radius;
	cylinder->height = height;
	cylinder->center = center;
	cylinder->vector = vector;
	cylinder->color = color;
	cylinder->material = material;
	cylinder_object = (t_object3d *)malloc(sizeof(t_object3d));
	cylinder_object->data = cylinder;
	cylinder_object->intersect = intersect_cylinder;
	cylinder_object->get_color = get_color_cylinder;
	cylinder_object->get_normal_vector = get_normal_vector_cylinder;
	cylinder_object->get_material = get_material_cylinder;
	cylinder_object->get_min_boundary_point = get_min_boundary_point_cylinder;
	cylinder_object->get_max_boundary_point = get_max_boundary_point_cylinder;
	cylinder_object->release_data = release_data_cylinder;
	return (cylinder_object);
}

void	release_data_cylinder(void *data)
{
	free((t_cylinder *)data);
}
