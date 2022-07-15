#ifndef PARSER_H
# define PARSER_H

# include "scene.h"
# include "camera.h"
# include "canvas.h"

int		parse_map(char *filename);

int		parse_next_double(char *line, int i, double *result);
int		parse_next_int(char *line, int i, int *result);
int		parse_next_point(char *line, int i, t_point3d *point);

// void	parse_camera(char *line, int i, t_camera **camera);
void	parse_camera(char *line, int i);
void	parse_ambient_lightning(char *line, int i); // not written yet

#endif
