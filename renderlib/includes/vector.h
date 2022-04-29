#ifndef VECTOR_H
# define VECTOR_H

# include "point.h"

typedef struct s_vector3d
{
	double	x;
	double	y;
	double	z;
}	t_vector3d;

t_vector3d	vector3dp(const t_point3d start_point, const t_point3d end_point);
t_vector3d	vector3df(const double x, const double y, const double z);

#endif
