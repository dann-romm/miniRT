#ifndef CAMERA_H
# define CAMERA_H

# ifndef EPSILON
#  define EPSILON 1e-5
# endif

# include "point.h"
# include "vector.h"
# include "utils.h"

typedef struct s_camera
{
	t_point3d	camera_position;

	double		al_x;
	double		sin_al_x;
	double		cos_al_x;

	double		al_y;
	double		sin_al_y;
	double		cos_al_y;

	double		al_z;
	double		sin_al_z;
	double		cos_al_z;

	double		proj_plane_dist;
}	t_camera;

t_camera	*new_camera(const t_point3d camera_position, const double al_x, const double al_y, const double al_z, const double proj_plane_dist);

void		release_camera(t_camera *const cam);

void		rotate_camera(t_camera *const cam, const double al_x, const double al_y, const double al_z);

void		move_camera(t_camera *const camera, const t_vector3d vector);

#endif
