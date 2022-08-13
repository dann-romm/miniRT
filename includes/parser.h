#ifndef PARSER_H
# define PARSER_H

# include "scene.h"
# include "camera.h"
# include "objects/sphere.h"
# include "objects/plane.h"
# include "objects/cylinder.h"
# include "canvas.h"

int		parse_map(char *filename);

int		parse_next_double(char *line, int i, double *result);
int		parse_next_int(char *line, int i, int *result);
int		parse_next_point(char *line, int i, t_point3d *point);

// void	parse_camera(char *line, int i, t_camera **camera);
void	parse_plane(char *line, int i);
void	parse_light(char *line, int i);
void	parse_camera(char *line, int i);
void	parse_sphere(char *line, int i);
void	parse_cylinder(char *line, int i);
void	parse_ambient_lightning(char *line, int i); // not written yet

#endif
