#ifndef POINT_H
# define POINT_H

# include <math.h>

# ifndef EPSILON
#  define EPSILON 1e-5
# endif

// TODO: think about using defines instead of functions
// # define point3d(x, y, z) (t_point3d){x, y, z}
// # define point3dp(p, v) (t_point3d){p.x + v.x, p.y + v.y, p.z + v.z}
// # define point2d(x, y) (t_point2d){x, y}

# define POSITIVE_INFINITY_POINT3D (t_point3d){INFINITY, INFINITY, INFINITY}
# define NEGATIVE_INFINITY_POINT3D (t_point3d){-INFINITY, -INFINITY, -INFINITY}

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
