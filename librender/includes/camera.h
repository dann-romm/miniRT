#ifndef CAMERA_H
# define CAMERA_H

# include "point.h"
# include "vector.h"

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

// initialize camera with given position, angles and projection plane distance
t_camera	*new_camera(const t_point3d camera_position, const double al_x, const double al_y, const double al_z, const double proj_plane_dist);

// release memory allocated for camera
void		release_camera(t_camera *const cam);

// rotate camera by given angles
void		rotate_camera(t_camera *const cam, const double al_x, const double al_y, const double al_z);

// move camera by given vector
void		move_camera(t_camera *const camera, const t_vector3d vector);

#endif
