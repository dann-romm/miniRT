#include <stdlib.h>
#include "objects/sphere.h"

t_object3d	*new_sphere(t_point3d center, double radius, t_color color, t_material material)
{
	t_sphere	*sphere;
	t_object3d	*sphere_obj;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->center = center;
	sphere->radius = radius;
	sphere->color = color;
	sphere->material = material;
	sphere_obj = (t_object3d *)malloc(sizeof(t_object3d));
	sphere_obj->data = sphere;
	sphere_obj->intersect = intersect_sphere;
	sphere_obj->get_color = get_color_sphere;
	sphere_obj->get_normal_vector = get_normal_vector_sphere;
	sphere_obj->get_material = get_material_sphere;
	sphere_obj->get_min_boundary_point = get_min_boundary_point_sphere;
	sphere_obj->get_max_boundary_point = get_max_boundary_point_sphere;
	sphere_obj->release_data = release_data_sphere;
	return sphere_obj;
}

void	release_data_sphere(void *data)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)data;
	free(sphere);
}
