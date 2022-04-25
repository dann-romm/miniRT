#include "render.h"

t_vector3d	vector3dp(const t_point3d start_point, const t_point3d end_point)
{
	return ((t_vector3d) {.x = (end_point.x - start_point.x),
		.y = (end_point.y - start_point.y),
		.z = (end_point.z - start_point.z)});
}

t_vector3d	vector3df(const double x, const double y, const double z)
{
	return ((t_vector3d) {.x = x, .y = y, .z = z});
}
