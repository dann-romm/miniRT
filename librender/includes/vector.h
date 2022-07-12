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

t_vector3d	cross_product(const t_vector3d v1, const t_vector3d v2);
double		dot_product(const t_vector3d v1, const t_vector3d v2);
double		sqr_module_vector(const t_vector3d v);
double		module_vector(const t_vector3d v);
double		cos_vectors(const t_vector3d v1, const t_vector3d v2);
void		normalize_vector(t_vector3d *const v);

// TODO: use matrixes
t_vector3d	rotate_vector_x(const t_vector3d p, const double sin_al, const double cos_al);
t_vector3d	rotate_vector_y(const t_vector3d p, const double sin_al, const double cos_al);
t_vector3d	rotate_vector_z(const t_vector3d p, const double sin_al, const double cos_al);

#endif
