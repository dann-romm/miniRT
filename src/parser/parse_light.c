#include <stdio.h> // delete
#include "utils_ft.h"
#include "parser.h"

void	parse_light(char *line, int i)
{
	t_light_source3d	*light_source;
	t_point3d			location;
	t_color				color;
	t_point3d			tmp_point3d;
	double				brightness;

	i = parse_next_point(line, i, &location);
	i = parse_next_double(line, i, &brightness);
	i = parse_next_point(line, i, &tmp_point3d);

	color.r = tmp_point3d.x * brightness;
	color.g = tmp_point3d.y * brightness;
	color.b = tmp_point3d.z * brightness;

	light_source = new_light_source(location, color);

	//printf("color %hhu %hhu %hhu\n", light_source->color.r, light_source->color.g, light_source->color.b);
	//printf("light %f %f %f\n", light_source->location.x, light_source->location.y, light_source->location.z);
}