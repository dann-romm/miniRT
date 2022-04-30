#include <stdlib.h>
#include <math.h>
#include "kdtree.h"
#include "utils.h"
#include "utils_ft.h"

#define MAX_TREE_DEPTH 20
#define OBJECTS_IN_LEAF 1

//#define MAX_SPLITS_OF_VOXEL 100
#define MAX_SPLITS_OF_VOXEL 5
#define SPLIT_COST 5

// Declarations
// --------------------------------------------------------------

t_voxel	make_initial_voxel(t_object3d **objects, int objects_count);

t_KDNode	*rec_build(t_object3d **objects, int objects_count, t_voxel v, int iter);

t_KDNode	*make_leaf(t_object3d **objects, int objects_count);

void	find_plane(t_object3d **objects, const int objects_count, const t_voxel v, const int tree_depth, t_plane *const p, t_coord *const c);

int	objects_in_voxel(t_object3d **objects, const int objects_count, const t_voxel v);

void	split_voxel(const t_voxel v, const t_plane p, const t_coord c, t_voxel *const vl, t_voxel *const vr);

int	filter_overlapped_objects(t_object3d **objects, const int objects_count, const t_voxel v);

bool	vector_plane_intersection(const t_vector3d vector, const t_point3d vector_start, const t_plane plane, const t_coord coord, t_point3d *const result);

bool	voxel_intersection(const t_vector3d vector, const t_point3d vector_start, const t_voxel v);

bool	object_in_voxel(t_object3d *const obj, const t_voxel v);

bool	point_in_voxel(const t_point3d p, const t_voxel v);

bool	find_intersection_node(t_KDNode *const node, const t_voxel v, const t_point3d vector_start, const t_vector3d vector, t_object3d **const nearest_obj_ptr, t_point3d *const nearest_intersection_point_ptr, double *const nearest_intersection_point_dist_ptr);

bool	is_intersect_anything_node(t_KDNode *const node, const t_voxel v, const t_point3d vector_start, const t_vector3d vector);

void	release_kd_node(t_KDNode *node);


// Code
// --------------------------------------------------------------

bool	point_in_voxel(const t_point3d p, const t_voxel v)
{
	return ((p.x > v.x_min) && (p.x < v.x_max) &&
			(p.y > v.y_min) && (p.y < v.y_max) &&
			(p.z > v.z_min) && (p.z < v.z_max));
}


void	release_kd_tree(t_KDTree *tree)
{
	release_kd_node(tree->root);
	free(tree);
}

void	release_kd_node(t_KDNode *node)
{
	if (node->l)
		release_kd_node(node->l);
	if (node->r)
		release_kd_node(node->r);
	if (node->objects)
		free(node->objects);
	free(node);
}

t_KDTree	*build_kd_tree(t_object3d **objects, int objects_count)
{
	t_KDTree	*tree;
	
	tree = malloc(sizeof(t_KDTree));
	tree->bounding_box = make_initial_voxel(objects, objects_count);
	tree->root = rec_build(objects, objects_count, tree->bounding_box, 0);
	return (tree);
}

t_KDNode	*rec_build(t_object3d ** objects, int objects_count, t_voxel v, int iter)
{
	t_plane		p;
	t_coord		c;
	t_voxel		vl;
	t_voxel		vr;
	int			l_objects_count;
	int			r_objects_count;
	t_KDNode	*l;
	t_KDNode	*r;
	t_KDNode	*node;

	find_plane(objects, objects_count, v, iter, &p, &c);
	
	if (p == NONE)
		return (make_leaf(objects, objects_count));
	
	split_voxel(v, p, c, &vl, &vr);
	
	l_objects_count = filter_overlapped_objects(objects, objects_count, vl);
	l = rec_build(objects, l_objects_count, vl, iter + 1);
	
	r_objects_count = filter_overlapped_objects(objects, objects_count, vr);
	r = rec_build(objects, r_objects_count, vr, iter + 1);

	node = malloc(sizeof(t_KDNode));
	node->objects = NULL;
	node->objects_count = 0;
	node->plane = p;
	node->coord = c;
	node->l = l;
	node->r = r;
	return (node);
}

int	filter_overlapped_objects(t_object3d **objects, const int objects_count, const t_voxel v)
{
	int			i;
	int			j;
	t_object3d	*tmp;

	i = 0;
	j = objects_count - 1;
	// Put all objects, which overlap with t_voxel to the left part of array
	while (i <= j)
	{
		while ((i < j) && (object_in_voxel(objects[i], v)))
			i++;
		while ((j > i) && (!object_in_voxel(objects[j], v)))
			j--;
		tmp = objects[i];
		objects[i] = objects[j];
		objects[j] = tmp;
		i++;
		j--;
	}
	// Actually, after the loop, variable 'i' is a count of overlapped objects
	return (i);
}

void	split_voxel(const t_voxel v, const t_plane p, const t_coord c, t_voxel *const vl, t_voxel *const vr)
{
	*vl = v;
	*vr = v;
	if (p == XY)
	{
		vl->z_max = c.z;
		vr->z_min = c.z;
	}
	else if (p == XZ)
	{
		vl->y_max = c.y;
		vr->y_min = c.y;
	}
	else if (p == YZ)
	{
		vl->x_max = c.x;
		vr->x_min = c.x;
	}
	// else
	// {
	// 	// Unreachable case
	// 	printf("[split_voxel] Plane is NONE. Error");
	// 	exit(1);
	// }
}

/*
* Using Surface Area Heuristic (SAH) for finding best split pane
*
* SAH = 0.5 * voxel_surface_area * number_of_objects_in_voxel
*
* splitted_SAH = split_cost
*                + 0.5 * left_voxel_surface_area * number_of_objects_in_left_voxel
*                + 0.5 * right_voxel_surface_area * number_of_objects_in_right_voxel
*
* Finding coordinate of split plane (XY, XZ or YZ) which minimizing SAH
*
* If can't find optimal split plane - returns NONE
*
* see: http://stackoverflow.com/a/4633332/653511
*/
void	find_plane(t_object3d ** objects, const int objects_count, const t_voxel v, const int tree_depth, t_plane *const p, t_coord *const c)
{
	const double	hx = v.x_max - v.x_min;
	const double	hy = v.y_max - v.y_min;
	const double	hz = v.z_max - v.z_min;

	if ((tree_depth >= MAX_TREE_DEPTH) || (objects_count <= OBJECTS_IN_LEAF))
	{
		*p = NONE;
		return;
	}

	// Calculating square of each side of initial t_voxel
	double			Sxy = hx * hy;
	double			Sxz = hx * hz;
	double			Syz = hy * hz;
	const double	Ssum = Sxy + Sxz + Syz;
	// Let's normalize square of each side of initial t_voxel
	// to satisfy the following relationship:
	// Sxy + Sxz + Syz = 1
	Sxy /= Ssum;
	Sxz /= Ssum;
	Syz /= Ssum;
	
	const int		max_splits = MAX_SPLITS_OF_VOXEL;
	const double	split_cost = SPLIT_COST;
	
	// Assume that at the beginning best SAH has initial t_voxel
	// SAH = 0.5 * square * objects_count
	// square of initial t_voxel is Sxy + Sxz + Syz = 1
	double	bestSAH = objects_count;
	// initial t_voxel doesn't have split pane
	*p = NONE;
	
	double	currSAH;
	t_coord	curr_split_coord;
	int		i;
	t_voxel	vl;
	t_voxel	vr;
	double	l;
	double	r;
	
	double	S_split;
	double	S_non_split;
	
	// Let's find split surface, which have the least SAH
	
	// TODO: maybe do some refactoring (because of following 3 loops are very similar)
	
	// trying to minimize SAH by splitting across XY plane
	S_split = Sxy;
	S_non_split = Sxz + Syz;
	for (i = 1; i < max_splits; i++)
	{
		l = ((float) i) / max_splits;
		r = 1 - l;
		
		// Current coordinate of split surface
		curr_split_coord.z = v.z_min + l * hz;
		
		split_voxel(v, XY, curr_split_coord, &vl, &vr);
		
		currSAH = (S_split + l * S_non_split) * objects_in_voxel(objects, objects_count, vl)
				+ (S_split + r * S_non_split) * objects_in_voxel(objects, objects_count, vr)
				+ split_cost;
		
		if (currSAH < bestSAH) {
			bestSAH = currSAH;
			*p = XY;
			*c = curr_split_coord;
		}
	}
	
	// trying to minimize SAH by splitting across XZ plane
	S_split = Sxz;
	S_non_split = Sxy + Syz;
	for (i = 1; i < max_splits; i++)
	{
		l = ((float) i) / max_splits;
		r = 1 - l;

		// Current coordinate of split surface
		curr_split_coord.y = v.y_min + l * hy;
		
		split_voxel(v, XZ, curr_split_coord, &vl, &vr);
		
		currSAH = (S_split + l * S_non_split) * objects_in_voxel(objects, objects_count, vl)
				+ (S_split + r * S_non_split) * objects_in_voxel(objects, objects_count, vr)
				+ split_cost;
		
		if (currSAH < bestSAH)
		{
			bestSAH = currSAH;
			*p = XZ;
			*c = curr_split_coord;
		}
	}
	
	// trying to minimize SAH by splitting across YZ plane
	S_split = Syz;
	S_non_split = Sxy + Sxz;
	for (i = 1; i < max_splits; i++)
	{
		l = ((float) i) / max_splits;
		r = 1 - l;
		
		// Current coordinate of split surface
		curr_split_coord.x = v.x_min + l * hx;
		
		split_voxel(v, YZ, curr_split_coord, &vl, &vr);
		
		currSAH = (S_split + l * S_non_split) * objects_in_voxel(objects, objects_count, vl)
				+ (S_split + r * S_non_split) * objects_in_voxel(objects, objects_count, vr)
				+ split_cost;
		
		if (currSAH < bestSAH)
		{
			bestSAH = currSAH;
			*p = YZ;
			*c = curr_split_coord;
		}
	}
}

int	objects_in_voxel(t_object3d **objects, const int objects_count, const t_voxel v)
{
	int	i;
	int	count;
	
	count = 0;
	i = 0;
	while (i < objects_count)
	{
		if (object_in_voxel(objects[i], v))
			++count;
		i++;
	}
	return (count);
}

t_voxel	make_initial_voxel(t_object3d **objects, int objects_count)
{
	if (!objects_count)
		return ((t_voxel){-1, -1, -1, 1, 1, 1});

	t_point3d	min_p = objects[0]->get_min_boundary_point(objects[0]->data);
	t_point3d	max_p = objects[0]->get_max_boundary_point(objects[0]->data);
	
	double		x_min = min_p.x;
	double		y_min = min_p.y;
	double		z_min = min_p.z;
	
	double		x_max = max_p.x;
	double		y_max = max_p.y;
	double		z_max = max_p.z;
	
	int			i;
	for (i = 0; i < objects_count; i++)
	{
		min_p = objects[i]->get_min_boundary_point(objects[i]->data);
		max_p = objects[i]->get_max_boundary_point(objects[i]->data);
		
		x_min = (x_min < min_p.x) ? x_min : min_p.x;
		y_min = (y_min < min_p.y) ? y_min : min_p.y;
		z_min = (z_min < min_p.z) ? z_min : min_p.z;
		
		x_max = (x_max > max_p.x) ? x_max : max_p.x;
		y_max = (y_max > max_p.y) ? y_max : max_p.y;
		z_max = (z_max > max_p.z) ? z_max : max_p.z;
	}

	return ((t_voxel){x_min - 1, y_min - 1, z_min - 1, x_max + 1, y_max + 1, z_max + 1});
}


bool	object_in_voxel(t_object3d *const obj, const t_voxel v)
{
	t_point3d	min_p = obj->get_min_boundary_point(obj->data);
	t_point3d	max_p = obj->get_max_boundary_point(obj->data);

	return
		!((max_p.x < v.x_min)
		|| (max_p.y < v.y_min)
		|| (max_p.z < v.z_min)
		|| (min_p.x > v.x_max)
		|| (min_p.y > v.y_max)
		|| (min_p.z > v.z_max));
}

t_KDNode	*make_leaf(t_object3d **objects, int objects_count)
{
	t_KDNode	*leaf;
	
	leaf = malloc(sizeof(t_KDNode));
	leaf->plane = NONE;
	leaf->objects_count = objects_count;
	leaf->l = NULL;
	leaf->r = NULL;
	if (objects_count)
		leaf->objects = (t_object3d **) malloc(objects_count * sizeof(t_object3d *));
	else
		leaf->objects = NULL;
	ft_memcpy(leaf->objects, objects, objects_count * sizeof(t_object3d *));
	return (leaf);
}

bool	vector_plane_intersection(const t_vector3d vector, const t_point3d vector_start, const t_plane plane, const t_coord coord, t_point3d *const result)
{
	double	k;

	switch (plane)
	{
		case XY:
			if (((coord.z < vector_start.z) && (vector.z > 0))
				|| ((coord.z > vector_start.z) && (vector.z < 0)))
				return (False);
			
			k = (coord.z - vector_start.z) / vector.z;
			*result = point3d(vector_start.x + vector.x * k,
							vector_start.y + vector.y * k,
							coord.z);
			break ;
		
		case XZ:
			if (((coord.y < vector_start.y) && (vector.y > 0))
			|| ((coord.y > vector_start.y) && (vector.y < 0)))
				return (False);
			
			k = (coord.y - vector_start.y) / vector.y;
			*result = point3d(vector_start.x + vector.x * k,
							coord.y,
							vector_start.z + vector.z * k);
			break ;
			
		case YZ:
			if (((coord.x < vector_start.x) && (vector.x > 0))
			|| ((coord.x > vector_start.x) && (vector.x < 0)))
				return (False);
			
			k = (coord.x - vector_start.x) / vector.x;
			*result = point3d(coord.x,
							vector_start.y + vector.y * k,
							vector_start.z + vector.z * k);
			break ;
		case NONE:
			break ;
	}
	
	return (True);
}

bool	voxel_intersection(const t_vector3d vector, const t_point3d vector_start, const t_voxel v)
{
	if (point_in_voxel(vector_start, v))
		return (True);
	
	t_point3d	p;
	t_coord		c;
	
	c.z = v.z_min;
	if (vector_plane_intersection(vector, vector_start, XY, c, &p)
		&& (p.x > v.x_min) && (p.x < v.x_max)
		&& (p.y > v.y_min) && (p.y < v.y_max))
	{
		return (True);
	}
	
	c.z = v.z_max;
	if (vector_plane_intersection(vector, vector_start, XY, c, &p)
		&& (p.x > v.x_min) && (p.x < v.x_max)
		&& (p.y > v.y_min) && (p.y < v.y_max))
	{
		return (True);
	}
	
	c.y = v.y_min;
	if (vector_plane_intersection(vector, vector_start, XZ, c, &p)
		&& (p.x > v.x_min) && (p.x < v.x_max)
		&& (p.z > v.z_min) && (p.z < v.z_max))
	{
		return (True);
	}
	
	c.y = v.y_max;
	if (vector_plane_intersection(vector, vector_start, XZ, c, &p)
		&& (p.x > v.x_min) && (p.x < v.x_max)
		&& (p.z > v.z_min) && (p.z < v.z_max))
	{
		return (True);
	}
	
	c.x = v.x_min;
	if (vector_plane_intersection(vector, vector_start, YZ, c, &p)
		&& (p.y > v.y_min) && (p.y < v.y_max)
		&& (p.z > v.z_min) && (p.z < v.z_max))
	{
		return (True);
	}
	
	c.x = v.x_max;
	if (vector_plane_intersection(vector, vector_start, YZ, c, &p)
		&& (p.y > v.y_min) && (p.y < v.y_max)
		&& (p.z > v.z_min) && (p.z < v.z_max))
	{
		return (True);
	}
	
	return (False);
}

bool	find_intersection_tree(t_KDTree *const tree, const t_point3d vector_start, const t_vector3d vector, t_object3d **const nearest_obj_ptr, t_point3d *const nearest_intersection_point_ptr, double *const nearest_intersection_point_dist_ptr)
{
	return (voxel_intersection(vector, vector_start, tree->bounding_box)
			&& find_intersection_node(tree->root, tree->bounding_box, vector_start, vector, nearest_obj_ptr, nearest_intersection_point_ptr, nearest_intersection_point_dist_ptr));
}

bool	find_intersection_node(t_KDNode *const node, const t_voxel v, const t_point3d vector_start, const t_vector3d vector, t_object3d **const nearest_obj_ptr, t_point3d *const nearest_intersection_point_ptr, double *const nearest_intersection_point_dist_ptr)
{
	// Is leaf
	if (node->plane == NONE)
	{
		if ((node->objects_count) && (node->objects))
		{
			int i;
			
			t_object3d	*obj = NULL;
			t_point3d	intersection_point;
			double	sqr_curr_dist;
			
			t_object3d	*nearest_obj = NULL;
			t_point3d	nearest_intersection_point;
			double	sqr_nearest_dist;
			
			int intersected = False;
			
			// Finding nearest object
			// and intersection point
			for (i = 0; i < node->objects_count; i++)
			{
				if (node->objects[i])
				{
					obj = node->objects[i];
					
					if ((obj->intersect(obj->data, vector_start, vector, &intersection_point))
						&& (point_in_voxel(intersection_point, v)))
					{
						sqr_curr_dist = sqr_module_vector(vector3dp(vector_start, intersection_point));
						
						if ((sqr_curr_dist < sqr_nearest_dist) || (!intersected))
						{
							nearest_obj = obj;
							nearest_intersection_point = intersection_point;
							sqr_nearest_dist = sqr_curr_dist;
							intersected = True;
						}
					}
				}
			}
			
			if (intersected)
			{
				double	nearest_dist = sqrt(sqr_nearest_dist);
				
				if (nearest_dist < *nearest_intersection_point_dist_ptr) {
					*nearest_intersection_point_dist_ptr = nearest_dist;
					*nearest_obj_ptr = nearest_obj;
					*nearest_intersection_point_ptr = nearest_intersection_point;
				}
			}
			
			return (intersected);
		}
		return (False);
	}

	// Otherwise
	
	t_voxel	front_voxel = {0, 0, 0, 0, 0, 0};
	t_voxel	back_voxel;
		
	t_KDNode	*front_node;
	t_KDNode	*back_node;

	switch (node->plane)
	{
		case XY:
			if (((node->coord.z > v.z_min) && (node->coord.z > vector_start.z))
				|| ((node->coord.z < v.z_min) && (node->coord.z < vector_start.z)))
			{
				front_node = node->l;
				back_node = node->r;
				split_voxel(v, node->plane, node->coord, &front_voxel, &back_voxel);
			}
			else
			{
				front_node = node->r;
				back_node = node->l;
				split_voxel(v, node->plane, node->coord, &back_voxel, &front_voxel);
			}
			break;
				
		case XZ:
			if (((node->coord.y > v.y_min) && (node->coord.y > vector_start.y))
				|| ((node->coord.y < v.y_min) && (node->coord.y < vector_start.y)))
			{
				front_node = node->l;
				back_node = node->r;
				split_voxel(v, node->plane, node->coord, &front_voxel, &back_voxel);
			}
			else
			{
				front_node = node->r;
				back_node = node->l;
				split_voxel(v, node->plane, node->coord, &back_voxel, &front_voxel);
			}
			break;
			
		case YZ:
			if (((node->coord.x > v.x_min) && (node->coord.x > vector_start.x))
				|| ((node->coord.x < v.x_min) && (node->coord.x < vector_start.x)))
			{
				front_node = node->l;
				back_node = node->r;
				split_voxel(v, node->plane, node->coord, &front_voxel, &back_voxel);
			}
			else
			{
				front_node = node->r;
				back_node = node->l;
				split_voxel(v, node->plane, node->coord, &back_voxel, &front_voxel);
			}
			break;
			
		case NONE:
			break;
	}
	
	if (voxel_intersection(vector, vector_start, front_voxel)
		&& find_intersection_node(front_node, front_voxel, vector_start, vector, nearest_obj_ptr, nearest_intersection_point_ptr, nearest_intersection_point_dist_ptr))
		return (True);
			
	return (voxel_intersection(vector, vector_start, back_voxel)
		&& find_intersection_node(back_node, back_voxel, vector_start, vector, nearest_obj_ptr, nearest_intersection_point_ptr, nearest_intersection_point_dist_ptr));
}
