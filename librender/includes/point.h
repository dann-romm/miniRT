#ifndef POINT_H
# define POINT_H

# ifndef EPSILON
#  define EPSILON 1e-5
# endif

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

// TODO: use matrixes
t_point3d	rotate_point_x(const t_point3d p, const double sin_al, const double cos_al);
t_point3d	rotate_point_y(const t_point3d p, const double sin_al, const double cos_al);
t_point3d	rotate_point_z(const t_point3d p, const double sin_al, const double cos_al);

#endif
