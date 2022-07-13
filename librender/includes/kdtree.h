#ifndef KDTREE_H
# define KDTREE_H

# include "object.h"
# include "point.h"
# include "vector.h"
# include "bool.h"

typedef enum e_plane
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
	t_plane			plane;
	t_coord			coord;
	t_object3d		**objects;
	int				objects_count;
	struct s_KDNode	*l;
	struct s_KDNode	*r;
}	t_KDNode;

typedef struct s_KDTree
{
	t_KDNode	*root;
	t_voxel		bounding_box;
}	t_KDTree;

t_KDTree	*build_kd_tree(t_object3d **objects, int objects_count);

void		release_kd_tree(t_KDTree *tree);

t_bool		find_intersection_tree(
	t_KDTree *const tree,
	const t_point3d vector_start,
	const t_vector3d vector,
	t_object3d **const nearest_obj_ptr,
	t_point3d *const nearest_intersection_point_ptr,
	double *const nearest_intersection_point_dist_ptr
);

#endif
