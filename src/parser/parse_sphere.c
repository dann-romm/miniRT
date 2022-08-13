#include "parser.h"

void parse_sphere(char *line, int i, t_parsed_data *data)
{
	t_point3d	center;
	t_point3d	tmp_point3d;
	t_color		color;
	double		diameter;

	i = parse_next_point(line, i, &center);
	if_error_safe_exit(i, data);
	i = parse_next_double(line, i, &diameter);
	if_error_safe_exit(i, data);
	i = parse_next_point(line, i, &tmp_point3d);
	if_error_safe_exit(i, data);

	color.r = tmp_point3d.x;
	color.g = tmp_point3d.y;
	color.b = tmp_point3d.z;

	add_object(data->scene, new_sphere(center, diameter/2, color));
}
