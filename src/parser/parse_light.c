#include "parser.h"

void	parse_light(char *line, int i, t_parsed_data *data)
{
	t_point3d			location;
	t_color				color;
	t_point3d			tmp_point3d;
	double				brightness;

	i = parse_next_point(line, i, &location);
	if_error_safe_exit(i, data);
	i = parse_next_double(line, i, &brightness);
	if_error_safe_exit(i, data);
	i = parse_next_point(line, i, &tmp_point3d);
	if_error_safe_exit(i, data);

	color.r = tmp_point3d.x * brightness;
	color.g = tmp_point3d.y * brightness;
	color.b = tmp_point3d.z * brightness;

	add_light_source(data->scene, new_light_source(location, color));
}
