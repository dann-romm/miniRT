#ifndef KDTREE_H
# define KDTREE_H

# include "render.h"

t_KDTree	*build_kd_tree(t_object3d **objects, int objects_count);

void	release_kd_tree(t_KDTree *tree);

bool	find_intersection_tree(
	t_KDTree *const tree,
	const t_point3d vector_start,
	const t_vector3d vector,
	t_object3d **const nearest_obj_ptr,
	t_point3d *const nearest_intersection_point_ptr,
	double *const nearest_intersection_point_dist_ptr
);

#endif
