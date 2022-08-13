#include <fcntl.h>
#include "utils_ft.h"
#include "get_next_line.h"
#include "parser.h"

void	parse_element(char *line, t_parsed_data *data)
{
	int	index;

	index = 0;
	while (line[index] == ' ')
		index++;
	if (ft_strncmp(&line[index], "A", 1) == 0)
		return ;
		//parse_ambient_lightning(line, i);
	else if (ft_strncmp(&line[index], "C", 1) == 0)
		parse_camera(line, index + 1, data);
	else if (ft_strncmp(&line[index], "L", 1) == 0)
		parse_light(line, index + 1, data);
	else if (ft_strncmp(&line[index], "sp", 2) == 0)
		parse_sphere(line, index + 2, data);
	else if (ft_strncmp(&line[index], "pl", 2) == 0)
		parse_plane(line, index + 2, data);
	else if (ft_strncmp(&line[index], "cy", 2) == 0)
		parse_cylinder(line, index + 2, data);
}


t_parsed_data	parse_map(char *filename, t_scene *scene)
{
	int				fd;
	char			*line;
	t_parsed_data	data;

	data.scene = scene;
	fd = open(filename, O_RDONLY);
	if_error_safe_exit(fd, &data);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strcmp(line, "\n") != 0)
			parse_element(line, &data);
		line = get_next_line(fd);
	}
	close(fd);
	return (data);
}
