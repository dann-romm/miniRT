#ifndef PARSER_H
# define PARSER_H

# include "scene.h"
# include "camera.h"
# include "objects/sphere.h"
# include "objects/plane.h"
# include "objects/cylinder.h"
# include "canvas.h"


typedef struct s_parsed_data
{
	t_scene		*scene;
	t_camera	*camera;
}	t_parsed_data;

t_parsed_data	parse_map(char *filename, t_scene *scene);

int				parse_next_double(char *line, int i, double *result);
int				parse_next_int(char *line, int i, int *result);
int				parse_next_point(char *line, int i, t_point3d *point);

void			parse_plane(char *line, int i, t_parsed_data *data);
void			parse_light(char *line, int i, t_parsed_data *data);
void			parse_camera(char *line, int i, t_parsed_data *data);
void			parse_sphere(char *line, int i, t_parsed_data *data);
void			parse_cylinder(char *line, int i, t_parsed_data *data);
void			parse_ambient_lightning(char *line, int i, t_parsed_data *data); // not written yet

void			if_error_safe_exit(int error_code, t_parsed_data *data);

#endif
