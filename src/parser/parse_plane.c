#include "parser.h"

void parse_plane(char *line, int i, t_parsed_data *data)
{
	t_point3d	point;
	t_vector3d	normal;
	t_point3d	tmp_point3d;
	t_color		color;

	i = parse_next_point(line, i, &point);
	if_error_safe_exit(i, data);
	i = parse_next_point(line, i, (t_point3d *)(&normal));
	if_error_safe_exit(i, data);
	i = parse_next_point(line, i, &tmp_point3d);
	if_error_safe_exit(i, data);

	color.r = tmp_point3d.x;
	color.g = tmp_point3d.y;
	color.b = tmp_point3d.z;

	add_object(data->scene, new_plane(point, normal, color));
}
