#include <stdlib.h>
#include <math.h>
#include "camera.h"
#include <stdio.h> // delete

t_camera	*new_camera(const t_point3d camera_position, t_vector3d vector, const double fov)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	camera->camera_position = camera_position;
	normalize_vector(&vector);
	direction_vector_to_matrix(vector, &(camera->rotation_matrix));
	camera->proj_plane_dist = DEFAULT_PROJECTION_PLANE_DISTANCE;
	camera->fov = fov;
	return (camera);
}

void	release_camera(t_camera *const cam)
{
	free(cam);
}

void	rotate_camera(t_camera *const cam, const double al_x,
	const double al_y, const double al_z)
{
	// TODO: implement
}

void	move_camera(t_camera *const camera, const t_vector3d vector)
{
	t_vector3d	r_vector = vector3df(0, 0, 1);
	t_point3d	curr_pos;

	r_vector = rotate_vector_by_matrix(r_vector, camera->rotation_matrix);
	curr_pos = camera->camera_position;
	camera->camera_position = point3d(curr_pos.x + r_vector.x,
			curr_pos.y + r_vector.y, curr_pos.z + r_vector.z);
}
