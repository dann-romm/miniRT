#include "utils_ft.h"
#include "point.h"

// return value: index of the first character after the parsed value
int	parse_next_double(char *line, int i, double *result)
{
	while (line[i] == ' ')
		i++;
	if (ft_atof(&line[i], result))
	{
		// display error end exit
		// perror();
		// exit(1);
		return (-1);
	}
	while (line[i] >= '0' && line[i] <= '9')
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
		// display error end exit
		// perror();
		// exit(1);
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
	i++;
	i = parse_next_double(line, i, &point->y);
	i++;
	i = parse_next_double(line, i, &point->z);
	return (i);
}