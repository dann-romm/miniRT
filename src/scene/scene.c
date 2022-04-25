#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "render.h"
#include "utils.h"
#include "color.h"
#include "kdtree.h"

// Declarations
// --------------------------------------------------------------

void	rebuild_kd_tree(t_scene *scene);

// Code
// --------------------------------------------------------------

t_scene	*new_scene(const int objects_count,
	const int light_sources_count, const t_color background_color)
{
	t_scene	*s;

	s = malloc(sizeof(t_scene));
	s->objects_count = objects_count;
	s->objects = ft_calloc(objects_count, sizeof(t_object3d *));
	if (light_sources_count)
		s->light_sources = ft_calloc(light_sources_count,
				sizeof(t_light_source3d *));
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
	const double		sum = Ka + Kd + Ks + Kr + Kt;
	const t_material	m = {
		.Ka = Ka / sum, .Kd = Kd / sum, .Ks = Ks / sum,
		.Kr = Kr / sum, .Kt = Kt / sum, .p = p};

	return (m);
}

t_camera	*new_camera(const t_point3d camera_position, const double al_x,
	const double al_y, const double al_z, const double proj_plane_dist)
{
	t_camera	*cam;

	cam = malloc(sizeof(t_camera));
	cam->camera_position = camera_position;
	cam->al_x = al_x;
	cam->sin_al_x = sin(al_x);
	cam->cos_al_x = cos(al_x);
	cam->al_y = al_y;
	cam->sin_al_y = sin(al_y);
	cam->cos_al_y = cos(al_y);
	cam->al_z = al_z;
	cam->sin_al_z = sin(al_z);
	cam->cos_al_z = cos(al_z);
	cam->proj_plane_dist = proj_plane_dist;
	return (cam);
}

void	release_camera(t_camera *const cam)
{
	free(cam);
}

void	rotate_camera(t_camera *const cam, const double al_x,
	const double al_y, const double al_z)
{
	if (fabs(al_x) > EPSILON)
	{
		cam->al_x += al_x;
		cam->sin_al_x = sin(cam->al_x);
		cam->cos_al_x = cos(cam->al_x);
	}
	if (fabs(al_y) > EPSILON)
	{
		cam->al_y += al_y;
		cam->sin_al_y = sin(cam->al_y);
		cam->cos_al_y = cos(cam->al_y);
	}
	if (fabs(al_z) > EPSILON)
	{
		cam->al_z += al_z;
		cam->sin_al_z = sin(cam->al_z);
		cam->cos_al_z = cos(cam->al_z);
	}
}

void	move_camera(t_camera *const camera, const t_vector3d vector)
{
	t_vector3d	r_vector;
	t_point3d	curr_pos;

	r_vector = rotate_vector_x(vector, camera->sin_al_x, camera->cos_al_x);
	r_vector = rotate_vector_z(r_vector, camera->sin_al_z, camera->cos_al_z);
	r_vector = rotate_vector_y(r_vector, camera->sin_al_y, camera->cos_al_y);
	curr_pos = camera->camera_position;
	camera->camera_position = point3d(curr_pos.x + r_vector.x,
			curr_pos.y + r_vector.y, curr_pos.z + r_vector.z);
}
