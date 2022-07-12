# include "object.h"

typedef struct s_sphere
{
	t_point3d	center;
	double		radius;
	t_color		color;
	t_material	material;
}	t_sphere;

t_object3d	*new_sphere(t_point3d center, double radius, t_color color, t_material material);

t_bool		intersect_sphere(const void *data, const t_point3d vector_start, const t_vector3d vector, t_point3d *intersection_point);

t_color		get_color_sphere(const void *data, const t_point3d intersection_point);

t_vector3d	get_normal_vector_sphere(const void *data, const t_point3d intersection_point);

t_material	get_material_sphere(const void *data, const t_point3d intersection_point);

t_point3d	get_min_boundary_point_sphere(const void *data);

t_point3d	get_max_boundary_point_sphere(const void *data);

void		release_data_sphere(void *data);
