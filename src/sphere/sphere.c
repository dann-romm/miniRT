#include <stdlib.h>
#include "objects/sphere.h"

t_object3d	*new_sphere(t_point3d center, double radius, t_color color)
{
	t_sphere	*sphere;
	t_object3d	*sphere_object;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->center = center;
	sphere->radius = radius;
	sphere->color = color;
	sphere->material = DEFAULT_MATERIAL;
	sphere_object = (t_object3d *)malloc(sizeof(t_object3d));
	sphere_object->data = sphere;
	sphere_object->intersect = intersect_sphere;
	sphere_object->get_color = get_color_sphere;
	sphere_object->get_normal_vector = get_normal_vector_sphere;
	sphere_object->get_material = get_material_sphere;
	sphere_object->get_min_boundary_point = get_min_boundary_point_sphere;
	sphere_object->get_max_boundary_point = get_max_boundary_point_sphere;
	sphere_object->release_data = release_data_sphere;
	return (sphere_object);
}

void	release_data_sphere(void *data)
{
	free((t_sphere *)data);
}
