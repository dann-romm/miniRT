#include <fcntl.h>
#include <stdio.h> // delete
#include "utils_ft.h"
#include "get_next_line.h"
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

void	parse_element(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strncmp(&line[i], "A", 1) == 0)
		return ;
		//parse_ambient_lightning(line, i);
	else if (ft_strncmp(&line[i], "C", 1) == 0)
		parse_camera(line, i + 1);
	else if (ft_strncmp(&line[i], "L", 1) == 0)
		parse_light(line, i + 1);
	else if (ft_strncmp(&line[i], "sp", 2) == 0)
		parse_sphere(line, i + 2);
	else if (ft_strncmp(&line[i], "pl", 2) == 0)
		parse_plane(line, i + 2);
	// else if (ft_strncmp(&line[i], "cy", 2) == 0)
	// 	parse_camera(line, i + 2);
}


int	parse_map(char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("opening file");
		return (-1);
	}
	line = get_next_line(fd);
	while (line != 0)
	{
		if (ft_strcmp(line, "\n") != 0)
			parse_element(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
