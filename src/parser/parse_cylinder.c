#include "parser.h"

void parse_cylinder(char *line, int index, t_parsed_data *data)
{
	t_point3d	center;
	t_vector3d	vector;
	t_point3d	tmp_point3d;
	double		diameter;
	double		height;
	t_color		color;

	index = parse_next_point(line, index, &center);
	if_error_safe_exit(index, data);
	index = parse_next_point(line, index, (t_point3d *)(&vector));
	if_error_safe_exit(index, data);
	index = parse_next_double(line, index, &diameter);
	if_error_safe_exit(index, data);
	index = parse_next_double(line, index, &height);
	if_error_safe_exit(index, data);
	index = parse_next_point(line, index, &tmp_point3d);
	if_error_safe_exit(index, data);

	color.r = tmp_point3d.x;
	color.g = tmp_point3d.y;
	color.b = tmp_point3d.z;

	add_object(data->scene, new_cylinder(diameter/2.0, height, center, vector, color));
}
