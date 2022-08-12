#include <stdio.h> // delete
#include "utils_ft.h"
#include "parser.h"

void parse_plane(char *line, int i)
{
	t_object3d	*plane_object;
	t_point3d	point;
	t_vector3d	normal;
	t_point3d	tmp_point3d;
	t_color		color;
	t_material	material;

	i = parse_next_point(line, i, &point);
	i = parse_next_point(line, i, (t_point3d *)(&normal));
	i = parse_next_point(line, i, &tmp_point3d);

	color.r = tmp_point3d.x;
	color.g = tmp_point3d.y;
	color.b = tmp_point3d.z;

	plane_object = new_plane(point, normal, color, material);
	//printf("color %hhu %hhu %hhu\n", color.r, color.g, color.b);
	//printf("location %f %f %f\n", point.x, point.y, point.z);
	//printf("normal %f %f %f\n", normal.x, normal.y, normal.z);
}