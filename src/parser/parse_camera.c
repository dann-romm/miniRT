#include "parser.h"
#include "utils_math.h"

void	parse_camera(char *line, int i, t_parsed_data *data)
{
	t_camera	*camera;
	t_point3d	camera_position;
	t_vector3d	vector;
	double		fov;

	i = parse_next_point(line, i, &camera_position);
	if_error_safe_exit(i, data);
	i = parse_next_point(line, i, (t_point3d *)(&vector));
	if_error_safe_exit(i, data);
	i = parse_next_double(line, i, &fov);
	if_error_safe_exit(i, data);

	camera = new_camera(camera_position, vector, degree_to_radian(fov));
	data->camera = camera;
}
