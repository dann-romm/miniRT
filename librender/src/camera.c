#include <stdlib.h>
#include "camera.h"

t_camera	*new_camera(const t_point3d camera_position, const double al_x, const double al_y, const double al_z, const double proj_plane_dist)
{
	t_camera	*cam;

	cam = malloc(sizeof(t_camera));
	cam->camera_position = camera_position;
	cam->al_x = al_x;
	cam->sin_al_x = sin(al_x);
	cam->cos_al_x = cos(al_x);
	cam->al_y = al_y;
	cam->sin_al_y = sin(al_y);
	cam->cos_al_y = cos(al_y);
	cam->al_z = al_z;
	cam->sin_al_z = sin(al_z);
	cam->cos_al_z = cos(al_z);
	cam->proj_plane_dist = proj_plane_dist;
	return (cam);
}

void	release_camera(t_camera *const cam)
{
	free(cam);
}

void	rotate_camera(t_camera *const cam, const double al_x, const double al_y, const double al_z)
{
	if (fabs(al_x) > EPSILON)
	{
		cam->al_x += al_x;
		cam->sin_al_x = sin(cam->al_x);
		cam->cos_al_x = cos(cam->al_x);
	}
	if (fabs(al_y) > EPSILON)
	{
		cam->al_y += al_y;
		cam->sin_al_y = sin(cam->al_y);
		cam->cos_al_y = cos(cam->al_y);
	}
	if (fabs(al_z) > EPSILON)
	{
		cam->al_z += al_z;
		cam->sin_al_z = sin(cam->al_z);
		cam->cos_al_z = cos(cam->al_z);
	}
}

void	move_camera(t_camera *const camera, const t_vector3d vector)
{
	t_vector3d	r_vector;
	t_point3d	curr_pos;

	r_vector = rotate_vector_x(vector, camera->sin_al_x, camera->cos_al_x);
	r_vector = rotate_vector_z(r_vector, camera->sin_al_z, camera->cos_al_z);
	r_vector = rotate_vector_y(r_vector, camera->sin_al_y, camera->cos_al_y);
	curr_pos = camera->camera_position;
	camera->camera_position = point3d(curr_pos.x + r_vector.x, curr_pos.y + r_vector.y, curr_pos.z + r_vector.z);
}
