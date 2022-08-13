#include <stdio.h> // delete
#include "utils_ft.h"
#include "parser.h"

void parse_cylinder(char *line, int i)
{
	t_object3d	*cylinder_object;
	t_point3d	center;
	t_vector3d	normal;
	t_point3d	tmp_point3d;
	double		diameter;
	double		height;
	t_color		color;

	i = parse_next_point(line, i, &center);
	i = parse_next_point(line, i, (t_point3d *)(&normal));
	i = parse_next_double(line, i, &diameter);
	i = parse_next_double(line, i, &height);
	i = parse_next_point(line, i, &tmp_point3d);

	color.r = tmp_point3d.x;
	color.g = tmp_point3d.y;
	color.b = tmp_point3d.z;

	printf("center %f %f %f\n", center.x, center.y, center.z);
	printf("normal %f %f %f\n", normal.x, normal.y, normal.z);
	printf("radius = %f, height = %f\n", diameter/2, height);
	printf("color %hhu %hhu %hhu\n", color.r, color.g, color.b);

	cylinder_object = new_cylinder(diameter/2, height, center, normal, color);
}