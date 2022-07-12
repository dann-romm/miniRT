#include <stdlib.h>
#include "scene.h"
#include "utils_ft.h"

// Declarations
// --------------------------------------------------------------

void	rebuild_kd_tree(t_scene *scene);

// Code
// --------------------------------------------------------------

t_scene	*new_scene(const int objects_count, const int light_sources_count, const t_color background_color)
{
	t_scene	*s;

	s = malloc(sizeof(t_scene));
	s->objects_count = objects_count;
	s->objects = ft_calloc(objects_count, sizeof(t_object3d *));
	if (light_sources_count)
		s->light_sources = ft_calloc(light_sources_count, sizeof(t_light_source3d *));
	s->light_sources_count = light_sources_count;
	s->background_color = background_color;
	s->last_object_index = -1;
	s->last_light_source_index = -1;
	s->fog_parameters = NULL;
	s->fog_density = NULL;
	s->kd_tree = NULL;
	return (s);
}

void	release_scene(t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < scene->objects_count)
	{
		if (scene->objects[i])
			release_object3d(scene->objects[i]);
	}
	i = -1;
	while (++i < scene->light_sources_count)
	{
		if (scene->light_sources[i])
			free(scene->light_sources[i]);
	}
	free(scene->objects);
	free(scene->light_sources);
	if (scene->fog_parameters)
		free(scene->fog_parameters);
	if (scene->kd_tree)
		release_kd_tree(scene->kd_tree);
	free(scene);
}

void	add_object(t_scene *const scene, t_object3d *const object)
{	
	scene->objects[++scene->last_object_index] = object;
}

void	prepare_scene(t_scene *const scene)
{
	rebuild_kd_tree(scene);
}

void	add_light_source(t_scene *const scene,
	t_light_source3d *const light_source)
{
	scene->light_sources[++scene->last_light_source_index] = light_source;
}

void	rebuild_kd_tree(t_scene *scene)
{
	if (scene->kd_tree)
		release_kd_tree(scene->kd_tree);
	scene->kd_tree = build_kd_tree(scene->objects,
			scene->last_object_index + 1);
}

void	release_object3d(t_object3d *obj)
{
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
