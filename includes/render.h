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
# define DBL_MAX 1.7976931348623157e+308

typedef int bool;

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

/***************************************************
 *                     Render                      *
 ***************************************************/

void	render_scene(const t_scene *const scene, const t_camera *const camera, t_canvas *canvas, const int num_threads);

t_color	trace(const t_scene *const scene, const t_camera *const camera, t_vector3d vector);

/***************************************************
 *                     t_scene                       *
 ***************************************************/

// /***************************************************
//  *                    3D objects                   *
//  ***************************************************/


// t_object3d	*new_triangle(const t_point3d p1, const t_point3d p2, const t_point3d p3, const t_color color, const t_material material);

// t_object3d	*new_triangle_with_norms(
// 	const t_point3d p1,
// 	const t_point3d p2,
// 	const t_point3d p3,
// 	const t_vector3d n1,
// 	const t_vector3d n2,
// 	const t_vector3d n3,
// 	const t_color color,
// 	const t_material material
// );

// t_object3d	*new_triangle_with_texture(
// 	const t_point3d p1,
// 	const t_point3d p2,
// 	const t_point3d p3,
// 	const t_point2d t1,
// 	const t_point2d t2,
// 	const t_point2d t3,
// 	t_canvas *texture,
// 	const t_color color,
// 	const t_material material
// );

// t_object3d	*new_sphere(
// 	const t_point3d center,
// 	const double radius,
// 	const t_color color,
// 	const t_material material
// );

// void	release_object3d(t_object3d *obj);

t_light_source3d	*new_light_source(const t_point3d location, const t_color color);

t_material	material(
	const double Ka,
	const double Kd,
	const double Ks,
	const double Kr,
	const double Kt,
	const double p
);

#endif
