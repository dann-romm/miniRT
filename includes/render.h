#ifndef RENDER_H
# define RENDER_H

// open
# include <fcntl.h>
// close read write
# include <unistd.h>
// printf perror strerror
# include <stdio.h>
// malloc free exit
# include <stdlib.h>
// all functions
# include <math.h>
# include <stdint.h>

#include "color.h"

# define EPSILON 1e-5

typedef int bool;

typedef struct s_point3d
{
	double	x;
	double	y;
	double	z;
}	t_point3d;

typedef struct s_vector3d
{
	double	x;
	double	y;
	double	z;
}	t_vector3d;

typedef struct s_point2d
{
	double	x;
	double	z;
}	t_point2d;

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

// KD Tree
typedef enum s_plane
{
	NONE,
	XY,
	XZ,
	YZ
}	t_plane;

typedef union u_coord
{
	double	x;
	double	y;
	double	z;
}	t_coord;

typedef struct s_voxel
{
	double	x_min;
	double	y_min;
	double	z_min;

	double	x_max;
	double	y_max;
	double	z_max;
}	t_voxel;

typedef struct s_KDNode
{
	t_plane		plane;
	t_coord		coord;

	t_object3d	**objects;
	int			objects_count;
	
	struct s_KDNode	*l;
	struct s_KDNode	*r;
}	t_KDNode;

typedef struct s_KDTree
{
	t_KDNode	*root;
	t_voxel		bounding_box;
}	t_KDTree;

typedef struct s_scene
{
	// Array of pointers to 3d objects of scene
	t_object3d	**objects;
	int			objects_count;
	int			last_object_index;
	
	t_KDTree	*kd_tree;
	
	// Array of pointers to light sources
	t_light_source3d	**light_sources;
	int					light_sources_count;
	int					last_light_source_index;
	
	t_color	background_color;
	
	// Required to return value from interval [0..1]
	double	(*fog_density)(const double distance, const void *fog_parameters);
	void	*fog_parameters;
}	t_scene;

typedef struct s_camera
{
	t_point3d	camera_position;

	double		al_x;
	double		sin_al_x;
	double		cos_al_x;

	double		al_y;
	double		sin_al_y;
	double		cos_al_y;

	double		al_z;
	double		sin_al_z;
	double		cos_al_z;

	double		proj_plane_dist;
}	t_camera;

#endif
