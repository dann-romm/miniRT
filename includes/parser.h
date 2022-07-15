#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include "utils_ft.h"
# include "camera.h"
# include "point.h"
# include "utils_math.h"

int		parse_next_double(char *line, int i, double *result);
void	parse_camera(char *line, int i);
int		init_camera_position(t_point3d	*camera_position, char *line, int i);
void	parse_camera(char *line, int i);
void 	parse_ambient_lightning(char *line, int i); // not written yet

#endif