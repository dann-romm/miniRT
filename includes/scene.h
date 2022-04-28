#ifndef SCENE_H
# define SCENE_H

# include "color.h"
# include "object.h"
# include "camera.h"
# include "kdtree.h"

typedef struct s_scene
{
	// Array of pointers to 3d objects of scene
	t_object3d	**objects;
	int			objects_count;
	int			last_object_index;
	
	t_KDTree	*kd_tree;
	
	// Array of pointers to light sources
	t_light_source3d	**light_sources;
	int					light_sources_count;
	int					last_light_source_index;
	
	// background color of the scene;
	t_color	background_color;
	
	// Required to return value from interval [0..1]
	double	(*fog_density)(const double distance, const void *fog_parameters);
	void	*fog_parameters;
}	t_scene;


t_scene	*new_scene(const int objects_count, const int light_sources_count, const t_color background_color);

void	release_scene(t_scene *scene);

void	add_object(t_scene *const scene, t_object3d *const object);

void	prepare_scene(t_scene *const scene);

void	set_exponential_fog(t_scene *const scene, const double k);

void	set_no_fog(t_scene *const scene);

void	add_light_source(t_scene *const scene, t_light_source3d *const light_source);

#endif
