#include <stdio.h>
#include "parser.h"
#include "utils_math.h"

// void	parse_camera(char *line, int i, t_camera **camera)
void	parse_camera(char *line, int i)
{
	t_camera	*camera;
	t_point3d	camera_position;
	t_vector3d	vector;
	int			fov;
	double		proj_plane_dist;

	i = parse_next_point(line, i, &camera_position);
	i = parse_next_point(line, i, (t_point3d *)(&vector));
	i = parse_next_int(line, i, &fov);
	proj_plane_dist = fov_to_proj_plane_dist(fov, 1080); // TODO: replace 1080 with a canvas width
	camera = new_camera(camera_position, vector, proj_plane_dist);
	//printf("camera %f %f %f\nvector %f %f %f\nproj_plane_dist %f\n", camera->camera_position.x, camera->camera_position.y, camera->camera_position.z, vector.x, vector.y, vector.z, proj_plane_dist);
}
