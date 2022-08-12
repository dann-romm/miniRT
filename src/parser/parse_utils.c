#include "utils_ft.h"
#include <stdio.h>
#include <stdlib.h>
#include "point.h"

void if_error_exit(int i) {
	if (i == -1)
	{
		dprintf(2, "Error: invalid map\n");
		exit(1);
	}
}

// return value: index of the first character after the parsed value
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
int	parse_next_int(char *line, int i, int *result)
{
	while (line[i] == ' ')
		i++;
	if (ft_atoi(&line[i], result))
	{
		perror("parsing map");
		return (-1);
	}
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	return (i);
}

// return value: index of the first character after the parsed value
int	parse_next_point(char *line, int i, t_point3d *point)
{
	i = parse_next_double(line, i, &point->x);
	if_error_exit(i);
	i++;
	i = parse_next_double(line, i, &point->y);
	if_error_exit(i);
	i++;
	i = parse_next_double(line, i, &point->z);
	if_error_exit(i);
	return (i);
}

