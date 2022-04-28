#ifndef OBJECT_H
# define OBJECT_H

# include "color.h"
# include "point.h"
# include "vector.h"

typedef struct s_light_source3d
{
	// Absolute location
	t_point3d	location_world;
	// Location on projection
	t_point3d	location;
	t_color		color;
}	t_light_source3d;

typedef struct s_material
{
	// Required:
	// Ka + Kd + Ks + Kr + Kt = 1.0

	// Ambient
	double	Ka;
	// Diffuse
	double	Kd;
	// Specular
	double	Ks;
	// Reflection
	double	Kr;
	// Transparency
	double	Kt;

	// Ks * light_source_color * ((cos(..))^p)
	double	p;

}	t_material;

typedef struct s_object3d
{
	void		*data;
	//
	bool		(*intersect)(const void *data, const t_point3d vector_start, const t_vector3d vector, t_point3d *intersection_point);
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
