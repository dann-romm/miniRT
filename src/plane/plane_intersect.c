#include <math.h>
#include "objects/plane.h"

t_bool	intersect_plane(const void *data, const t_point3d vector_start,
	const t_vector3d vector, t_point3d *intersection_point)
{
	t_plane			*plane;
	const double	n_dot_v = dot_product(vector, ((t_plane *)data)->normal);
	double			t;

	plane = (t_plane *)data;
	if (fabs(n_dot_v) < EPSILON)
		return (FALSE);
	t = dot_product(vector3dp(plane->point, vector_start),
			plane->normal) / n_dot_v;
	*intersection_point = point3d(vector_start.x - vector.x * t,
			vector_start.y - vector.y * t, vector_start.z - vector.z * t);
	return (TRUE);
}
