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

t_vector3d	multiply_vector(const t_vector3d vector, const double factor);

t_vector3d	cross_product(const t_vector3d v1, const t_vector3d v2);
double		dot_product(const t_vector3d v1, const t_vector3d v2);
double		sqr_module_vector(const t_vector3d v);
double		module_vector(const t_vector3d v);
double		cos_vectors(const t_vector3d v1, const t_vector3d v2);
void		normalize_vector(t_vector3d *const v);

typedef struct s_matrix {
	double	m[3][3];
}	t_rot_matrix;

t_vector3d	rotate_vector_by_matrix(const t_vector3d p, const t_rot_matrix m);
void		axis_angle_to_matrix(t_vector3d axis, double angle, t_rot_matrix *matrix);
void		direction_vector_to_matrix(t_vector3d direction, t_rot_matrix *matrix);

void	multiply_matrix(t_rot_matrix *const m1, t_rot_matrix *const m2, t_rot_matrix *const res);

#endif
