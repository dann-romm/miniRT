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

# include "color.h"
# include "canvas.h"

# define EPSILON 1e-5

typedef int bool;

/***************************************************
 *                   Structures                    *
 ***************************************************/

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
	double	y;
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

/***************************************************
 *                     Render                      *
 ***************************************************/

void	render_scene(const t_scene *const scene, const t_camera *const camera, t_canvas *canvas, const int num_threads);

/***************************************************
 *                     t_scene                       *
 ***************************************************/

t_scene	*new_scene(const int objects_count, const int light_sources_count, const t_color background_color);

void	release_scene(t_scene *scene);

void	add_object(t_scene *const scene, t_object3d *const object);

void	prepare_scene(t_scene *const scene);

void	set_exponential_fog(t_scene *const scene, const double k);

void	set_no_fog(t_scene *const scene);

t_color	trace(const t_scene *const scene, const t_camera *const camera, t_vector3d vector);

void	add_light_source(t_scene *const scene, t_light_source3d *const light_source);

/***************************************************
 *                    3D objects                   *
 ***************************************************/


t_object3d	*new_triangle(const t_point3d p1, const t_point3d p2, const t_point3d p3, const t_color color, const t_material material);

t_object3d	*new_triangle_with_norms(
	const t_point3d p1,
	const t_point3d p2,
	const t_point3d p3,
	const t_vector3d n1,
	const t_vector3d n2,
	const t_vector3d n3,
	const t_color color,
	const t_material material
);

t_object3d	*new_triangle_with_texture(
	const t_point3d p1,
	const t_point3d p2,
	const t_point3d p3,
	const t_point2d t1,
	const t_point2d t2,
	const t_point2d t3,
	t_canvas *texture,
	const t_color color,
	const t_material material
);

t_object3d	*new_sphere(
	const t_point3d center,
	const double radius,
	const t_color color,
	const t_material material
);

void	release_object3d(t_object3d *obj);

t_light_source3d	*new_light_source(const t_point3d location, const t_color color);

t_material	material(
	const double Ka,
	const double Kd,
	const double Ks,
	const double Kr,
	const double Kt,
	const double p
);

/***************************************************
 *                     t_camera                    *
 ***************************************************/

t_camera	*new_camera(
	const t_point3d camera_position,
	const double al_x,
	const double al_y,
	const double al_z,
	const double proj_plane_dist
);

void	release_camera(t_camera *const cam);

void	rotate_camera(
	t_camera *const cam,
	const double al_x,
	const double al_y,
	const double al_z
);

void	move_camera(t_camera *const camera, const t_vector3d vector);

/***************************************************
 *                Point and vectors                *
 ***************************************************/

t_point2d	point2d(const double x, const double y);

t_point3d	point3d(const double x, const double y, const double z);

t_vector3d	vector3dp(const t_point3d start_point, const t_point3d end_point);

t_vector3d	vector3df(const double x, const double y, const double z);


#endif
