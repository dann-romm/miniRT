# include "object.h"
# include "bool.h"

typedef struct s_sphere
{
	t_point3d	center;
	double		radius;
	t_color		color;
	t_material	material;
}	t_sphere;

// initialize sphere with given values
t_object3d	*new_sphere(t_point3d center, double radius, t_color color, t_material material);

// check if the ray intersects the sphere
// return TRUE if the ray intersects the sphere, FALSE otherwise
// the intersection point is stored in the intersection_point parameter
t_bool		intersect_sphere(const void *data, const t_point3d vector_start, const t_vector3d vector, t_point3d *intersection_point);

// get color of sphere at given point
t_color		get_color_sphere(const void *data, const t_point3d intersection_point);

// get the normal vector at the given point
t_vector3d	get_normal_vector_sphere(const void *data, const t_point3d intersection_point);

// get the material of the sphere at given point
t_material	get_material_sphere(const void *data, const t_point3d intersection_point);

// get minimum point of bounding box of sphere
t_point3d	get_min_boundary_point_sphere(const void *data);

// get maximum point of bounding box of sphere
t_point3d	get_max_boundary_point_sphere(const void *data);

// release memory allocated by sphere
void		release_data_sphere(void *data);
