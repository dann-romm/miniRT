#include "utils_ft.h"
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "point.h"

void if_error_safe_exit(int error_code, t_parsed_data *data)
{
	if (error_code == -1)
	{
		release_camera(data->camera);
		release_scene(data->scene);
		printf("Error\n");
		exit(1);
	}
}

// return value: index of the first character after the parsed value
// if the value is not found, return -1
int	parse_next_double(char *line, int i, double *result)
{
	while (line[i] == ' ')
		i++;
	if (ft_atof(&line[i], result))
		return (-1);
	while ((line[i] >= '0' && line[i] <= '9') || line[i] == '-' || line[i] == '+')
		i++;
	if (line[i] == '.')
	{
		i++;
		while (line[i] >= '0' && line[i] <= '9')
			i++;
	}
	return (i);
}

// return value: index of the first character after the parsed value
// if the value is not found, return -1
int	parse_next_int(char *line, int i, int *result)
{
	while (line[i] == ' ')
		i++;
	if (ft_atoi(&line[i], result))
		return (-1);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	return (i);
}

// return value: index of the first character after the parsed value
// if the value is not found, return -1
int	parse_next_point(char *line, int i, t_point3d *point)
{
	i = parse_next_double(line, i, &point->x);
	if (i == -1)
		return (-1);
	i++;
	i = parse_next_double(line, i, &point->y);
	if (i == -1)
		return (-1);
	i++;
	i = parse_next_double(line, i, &point->z);
	if (i == -1)
		return (-1);
	return (i);
}
