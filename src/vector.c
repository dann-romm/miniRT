#include "vector.h"

t_vector3d	vector3dp(const t_point3d start_point, const t_point3d end_point)
{
	t_vector3d	v;

	v.x = end_point.x - start_point.x;
	v.y = end_point.y - start_point.y;
	v.z = end_point.z - start_point.z;
	return (v);
}

t_vector3d	vector3df(const double x, const double y, const double z)
{
	t_vector3d	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
