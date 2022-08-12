#include <stdio.h> // delete
#include "utils_ft.h"
#include "parser.h"

void parse_sphere(char *line, int i)
{
	t_object3d	*sphere_object;
	t_point3d	center;
	t_material	material;
	t_point3d	tmp_point3d;
	t_color		color;
	double		diameter;

	i = parse_next_point(line, i, &center);
	i = parse_next_double(line, i, &diameter);
	i = parse_next_point(line, i, &tmp_point3d);

	color.r = tmp_point3d.x;
	color.g = tmp_point3d.y;
	color.b = tmp_point3d.z;

	//printf("color %hhu %hhu %hhu\n radius = %f\n", color.r, color.g, color.b, diameter/2);
	//printf("center %f %f %f\n", center.x, center.y, center.z);

	sphere_object = new_sphere(center, diameter/2, color, material);
}