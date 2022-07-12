#ifndef OBJECT_H
# define OBJECT_H

# include "color.h"
# include "point.h"
# include "vector.h"

typedef int	t_bool;
# define TRUE 1
# define FALSE 0

typedef struct s_light_source3d
{
	t_point3d	location_world; // Absolute location
	t_point3d	location; // Location on projection plane
	t_color		color;
}	t_light_source3d;

// material properties of object (color, reflectivity, transparency, etc.)
// Required:
// Ka + Kd + Ks + Kr + Kt = 1.0
typedef struct s_material
{
	double	Ka; // Ambient
	double	Kd; // Diffuse
	double	Ks; // Specular
	double	Kr; // Reflection
	double	Kt; // Transparency
	double	p; // Ks * light_source_color * ((cos(..))^p)
}	t_material;

typedef struct s_object3d
{
	void		*data;
	//
	t_bool		(*intersect)(const void *data, const t_point3d vector_start, const t_vector3d vector, t_point3d *intersection_point);
	//
	t_color		(*get_color)(const void *data, const t_point3d intersection_point);
	//
	t_vector3d	(*get_normal_vector)(const void *data, const t_point3d intersection_point);
	//
	t_material	(*get_material)(const void *data, const t_point3d intersection_point);
	//
	t_point3d	(*get_min_boundary_point)(const void *data);
	//
	t_point3d	(*get_max_boundary_point)(const void *data);
	//
	void		(*release_data)(void *data);
}	t_object3d;

#endif
