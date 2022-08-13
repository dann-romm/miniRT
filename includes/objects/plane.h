#ifndef PLANE_H
# define PLANE_H

# include "object.h"
# include "bool.h"

typedef struct s_plane
{
	t_point3d	point;
	t_vector3d	normal;
	t_color		color;
	t_material	material;
}	t_plane;

// initialize plane with given values
t_object3d	*new_plane(t_point3d point, t_vector3d normal, t_color color);

// check if the ray intersects the object
// return TRUE if the ray intersects the object, FALSE otherwise
// the intersection point is stored in the intersection_point parameter
t_bool		intersect_plane(const void *data, const t_point3d vector_start, const t_vector3d vector, t_point3d *intersection_point);

// get color at given point
t_color		get_color_plane(const void *data, const t_point3d intersection_point);

// get the normal vector at the given point
t_vector3d	get_normal_vector_plane(const void *data, const t_point3d intersection_point);

// get the material at given point
t_material	get_material_plane(const void *data, const t_point3d intersection_point);

// get minimum point of bounding box of object
t_point3d	get_min_boundary_point_plane(const void *data);

// get maximum point of bounding box of object
t_point3d	get_max_boundary_point_plane(const void *data);

// release memory allocated by object
void		release_data_plane(void *data);

#endif // PLANE_H
