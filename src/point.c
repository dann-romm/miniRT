#include "point.h"

t_point2d	point2d(const double x, const double y)
{
	t_point2d	p;

	p.x = x;
	p.y = y;
	return (p);
}

t_point3d	point3d(const double x, const double y, const double z)
{
	t_point3d	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}
