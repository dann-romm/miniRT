#ifndef POINT_H
# define POINT_H

typedef struct s_point3d
{
	double	x;
	double	y;
	double	z;
}	t_point3d;

typedef struct s_point2d
{
	double	x;
	double	y;
}	t_point2d;

t_point2d	point2d(const double x, const double y);
t_point3d	point3d(const double x, const double y, const double z);

#endif
