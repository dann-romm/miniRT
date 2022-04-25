#include "render.h"

t_point2d	point2d(const double x, const double y)
{
	return ((t_point2d) {.x = x, .y = y});
}

t_point3d	point3d(const double x, const double y, const double z)
{
	return ((t_point3d) {.x = x, .y = y, .z = z});
}
