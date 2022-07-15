#include "parser.h"
#include <stdio.h>

//TODO: replace 1080 with a canvas width (line ~61)

int	init_vector(t_vector3d	*vector, char *line, int i)
{
	parse_next_double(line, i, &vector->x);
	while (line[i] != ',')
		i++;
	i++;
	parse_next_double(line, i, &vector->y);
	while (line[i] != ',')
		i++;
	i++;
	parse_next_double(line, i, &vector->z);
	return (i);
}

int	init_camera_position(t_point3d	*camera_position, char *line, int i)
{
	double		x;
	double		y;
	double		z;

	parse_next_double(line, i, &x);
	camera_position->x = x;
	while (line[i] != ',')
		i++;
	i++;
	parse_next_double(line, i, &y);
	camera_position->y = y;
	while (line[i] != ',')
		i++;
	i++;
	parse_next_double(line, i, &z);
	camera_position->z = z;
	while (line[i] != ' ')
		i++;
	i++;
	return (i);
}

void	parse_camera(char *line, int i)
{
	t_camera	*camera;
	t_point3d	camera_position;
	t_vector3d	vector;
	int			fov;
	double		proj_plane_dist;

	while (line[i] == ' ')
		i++;
	i = init_camera_position(&camera_position, line, i);
	while (line[i] == ' ')
		i++;
	i = init_vector(&vector, line, i) + 1;
	while (line[i] == ' ')
		i++;
	ft_atoi(&line[i], &fov);
	proj_plane_dist = fov_to_proj_plane_dist(fov, 1080); // not written yet
	camera = new_camera(camera_position, vector, proj_plane_dist);
}
