#include <stdlib.h>
#include "scene.h"
#include "utils_ft.h"

# define DEFAULT_OBJECTS_SIZE 10
# define DEFAULT_LIGHT_SOURCES_SIZE 10

// Declarations
// --------------------------------------------------------------

void	rebuild_kd_tree(t_scene *scene);

// Code
// --------------------------------------------------------------

t_scene	*new_scene(const t_color background_color)
{
	t_scene	*s;

	s = malloc(sizeof(t_scene));
	
	s->objects_size = DEFAULT_OBJECTS_SIZE;
	s->objects = malloc(s->objects_size * sizeof(t_object3d *));
	
	s->light_sources_size = DEFAULT_LIGHT_SOURCES_SIZE;
	s->light_sources = malloc(s->light_sources_size * sizeof(t_light_source3d *));
	
	s->background_color = background_color;

	s->objects_len = 0;
	s->light_sources_len = 0;
	s->kd_tree = NULL;
	return (s);
}

void	release_scene(t_scene *scene)
{
	int	i;

	if (!scene)
		return ;
	i = -1;
	while (++i < scene->objects_len)
	{
		if (scene->objects[i])
			release_object3d(scene->objects[i]);
	}
	i = -1;
	while (++i < scene->light_sources_len)
	{
		if (scene->light_sources[i])
			free(scene->light_sources[i]);
	}
	free(scene->objects);
	free(scene->light_sources);
	if (scene->kd_tree)
		release_kd_tree(scene->kd_tree);
	free(scene);
}

void	add_object(t_scene *const scene, t_object3d *const object)
{	
	if (scene->objects_len == scene->objects_size)
	{
		scene->objects_size *= 2;
		scene->objects = ft_realloc(scene->objects, scene->objects_size * sizeof(t_object3d *));
	}
	scene->objects[scene->objects_len++] = object;
}

void	prepare_scene(t_scene *const scene)
{
	rebuild_kd_tree(scene);
}

void	add_light_source(t_scene *const scene,
	t_light_source3d *const light_source)
{
	if (scene->light_sources_len == scene->light_sources_size)
	{
		scene->light_sources_size *= 2;
		scene->light_sources = ft_realloc(scene->light_sources, scene->light_sources_size * sizeof(t_light_source3d *));
	}
	scene->light_sources[scene->light_sources_len++] = light_source;
}

void	rebuild_kd_tree(t_scene *scene)
{
	if (scene->kd_tree)
		release_kd_tree(scene->kd_tree);
	scene->kd_tree = build_kd_tree(scene->objects, scene->objects_len);
}

void	release_object3d(t_object3d *obj)
{
	if (!obj)
		return ;
	obj->release_data(obj->data);
	free(obj);
}

t_light_source3d	*new_light_source(const t_point3d location,
	const t_color color)
{
	t_light_source3d	*ls_p;

	ls_p = malloc(sizeof(t_light_source3d));
	ls_p->location_world = location;
	ls_p->location = location;
	ls_p->color = color;
	return (ls_p);
}

t_material	material(const double Ka, const double Kd,
		const double Ks, const double Kr,
		const double Kt, const double p)
{
	const double	sum = Ka + Kd + Ks + Kr + Kt;
	t_material		m = {
		.Ka = Ka / sum, .Kd = Kd / sum, .Ks = Ks / sum,
		.Kr = Kr / sum, .Kt = Kt / sum, .p = p};

	return (m);
}
