#ifndef UTILS_H
# define UTILS_H

# include <math.h>
# include "point.h"
# include "vector.h"

t_vector3d	cross_product(const t_vector3d a, const t_vector3d b);

double	dot_product(const t_vector3d v1, const t_vector3d v2);

double	sqr_module_vector(const t_vector3d v);

double	module_vector(const t_vector3d v);

double	cos_vectors(const t_vector3d v1, const t_vector3d v2);

void	normalize_vector(t_vector3d *const v);

t_vector3d	reflect_ray(const t_vector3d incident_ray, const t_vector3d norm_v);

// TODO: use matrixes
t_point3d	rotate_point_x(const t_point3d p, const double sin_al, const double cos_al);

t_point3d	rotate_point_y(const t_point3d p, const double sin_al, const double cos_al);

t_point3d	rotate_point_z(const t_point3d p, const double sin_al, const double cos_al);

// TODO: use matrixes
t_vector3d	rotate_vector_x(const t_vector3d p, const double sin_al, const double cos_al);

t_vector3d	rotate_vector_y(const t_vector3d p, const double sin_al, const double cos_al);

t_vector3d	rotate_vector_z(const t_vector3d p, const double sin_al, const double cos_al);

#endif
