#ifndef SCENE_H
# define SCENE_H

# include "color.h"
# include "object.h"
# include "camera.h"
# include "kdtree.h"

typedef struct s_scene
{
	// Array of pointers to 3d objects of scene
	t_object3d			**objects;
	int					objects_len;
	int					objects_size;
	
	// kdtree that contains all objects of scene
	t_KDTree			*kd_tree;
	
	// Array of pointers to light sources
	t_light_source3d	**light_sources;
	int					light_sources_len;
	int					light_sources_size;
	
	// background color of the scene;
	t_color				background_color;
}	t_scene;


t_scene	*new_scene(const t_color background_color);

void	release_scene(t_scene *scene);

void	add_object(t_scene *const scene, t_object3d *const object);

void	prepare_scene(t_scene *const scene);

void	add_light_source(t_scene *const scene, t_light_source3d *const light_source);

void	release_object3d(t_object3d *obj);

#endif
