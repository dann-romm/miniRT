#include <stdio.h>
#include "parser.h"
#include "get_next_line.h"

int	parse_next_double(char *line, int i, double *result)
{
	return (ft_atof(&line[i], result));
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
		parse_camera(line, i);
	else if (ft_strncmp(&line[i], "sp", 2) == 0)
		parse_camera(line, i + 2);
	else if (ft_strncmp(&line[i], "pl", 2) == 0)
		parse_camera(line, i);
	else if (ft_strncmp(&line[i], "cy", 2) == 0)
		parse_camera(line, i);
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

int	main()
{
	int	err;

	err = parse_map("/Users/zaira/Desktop/miniRT/scene_test.rt");
	if (err != 0)
	{
		perror("parsing map");
		return (-1);
	}
	return (0);
}
