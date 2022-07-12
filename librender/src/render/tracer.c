#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "render.h"
#include "scene.h"
#include "kdtree.h"
#include "color.h"

#define INITIAL_RAY_INTENSITY 100
#define THRESHOLD_RAY_INTENSITY 10
#define MAX_RAY_RECURSION_LEVEL 10

// Declarations
// --------------------------------------------------------------

t_color	trace_recursively(
	const t_scene *const scene,
	const t_point3d vector_start,
	const t_vector3d vector,
	const double intensity,
	const int recursion_level);

t_bool	is_viewable(
	const t_point3d target_point,
	const t_point3d starting_point,
	const t_scene *const scene);

t_color get_lighting_color(
	const t_point3d point,
	const t_vector3d norm_v,
	const t_scene *const scene);

t_color	get_specular_color(
	const t_point3d point,
	const t_vector3d reflected_ray,
	const t_scene *const scene,
	const double p);

t_color	calculate_color(
	const t_scene *const scene,
	const t_point3d vector_start,
	const t_vector3d vector,
	t_object3d *const * obj_ptr,
	const t_point3d *const point_ptr,
	const double *const dist_ptr,
	const double intensity,
	const int recursion_level);

// reflect_ray.c
t_vector3d	reflect_ray(const t_vector3d incident_ray, const t_vector3d norm_v);

// Code
// --------------------------------------------------------------

t_color	trace(const t_scene *const scene,
	const t_camera *const camera, t_vector3d vector)
{
	t_vector3d r_vector;
	
	r_vector = rotate_vector_x(vector, camera->sin_al_x, camera->cos_al_x);
	r_vector = rotate_vector_z(r_vector, camera->sin_al_z, camera->cos_al_z);
	r_vector = rotate_vector_y(r_vector, camera->sin_al_y, camera->cos_al_y);
	
	return (trace_recursively(scene, camera->camera_position,
		r_vector, INITIAL_RAY_INTENSITY, 0));
}

// possibly - redundant code (was added to prevent overflow of double)
// TODO: remove
//normalize_vector(&vector);
t_color	trace_recursively(const t_scene *const scene,
	const t_point3d vector_start, const t_vector3d vector,
	const double intensity, const int recursion_level)
{
	t_object3d	*nearest_obj;
	t_point3d	nearest_intersection_point;
	double		nearest_intersection_point_dist;
	
	nearest_obj = NULL;
	nearest_intersection_point_dist = DBL_MAX;
	if (find_intersection_tree(scene->kd_tree, vector_start, vector,
		&nearest_obj, &nearest_intersection_point,
		&nearest_intersection_point_dist))
	{
		return (calculate_color(scene, vector_start, vector, &nearest_obj,
				&nearest_intersection_point, &nearest_intersection_point_dist,
				intensity, recursion_level));
	}
	return (scene->background_color);
}

t_color	calculate_color(const t_scene *const scene, const t_point3d vector_start, const t_vector3d vector, t_object3d *const *obj_ptr, const t_point3d *const point_ptr, const double *const dist_ptr, const double intensity, const int recursion_level)
{
	const t_object3d	*obj = *obj_ptr;
	const t_point3d		point = *point_ptr;
	const double		dist = *dist_ptr;
	const t_material	material = obj->get_material(obj->data, point);
	const t_vector3d	norm = obj->get_normal_vector(obj->data, point);

	t_color	obj_color;
	t_color	ambient_color;
	t_color	diffuse_color;
	t_color	reflected_color;
	t_color	specular_color;
	obj_color = obj->get_color(obj->data, point);

	double	fog_density;
	fog_density = 0;
	if (scene->fog_density)
		fog_density = scene->fog_density(dist, scene->fog_parameters);
	
	t_vector3d	reflected_ray;
	if ((material.Ks) || (material.Kr))
		reflected_ray = reflect_ray(vector, norm);
	
	// Ambient
	if (material.Ka)
		ambient_color = mix_colors(scene->background_color, obj_color);
	
	// Diffuse
	if (material.Kd)
	{
		diffuse_color = obj_color;
		if (scene->light_sources_count)
		{
			t_color light_color = get_lighting_color(point, norm, scene);
			diffuse_color = mix_colors(diffuse_color, light_color);
		}
	}
	
	// Specular
	if (material.Ks)
	{
		specular_color = scene->background_color;
		if (scene->light_sources_count)
			specular_color = get_specular_color(point, reflected_ray, scene, material.p);
	}
	
	// Reflect
	if (material.Kr)
	{
		// Avoid deep recursion by tracing rays, which have intensity is greather than threshold
		// and avoid infinite recursion by limiting number of recursive calls
		if ((intensity > THRESHOLD_RAY_INTENSITY)
			&& (recursion_level < MAX_RAY_RECURSION_LEVEL))
		{
			reflected_color = trace_recursively(scene, point, reflected_ray, intensity * material.Kr * (1 - fog_density), recursion_level + 1);
		}
		else
		{
			reflected_color = scene->background_color;
		}
	}
	
	// Result
	t_color	result_color = rgb(0, 0, 0);

	if (material.Ka)
		result_color = add_colors(result_color, mul_color(ambient_color, material.Ka));
	if (material.Kd)
		result_color = add_colors(result_color, mul_color(diffuse_color, material.Kd));
	if (material.Ks)
		result_color = add_colors(result_color, mul_color(specular_color, material.Ks));
	if (material.Kr)
		result_color = add_colors(result_color, mul_color(reflected_color, material.Kr));
	if (scene->fog_density)
		result_color = add_colors(mul_color(scene->background_color, fog_density), mul_color(result_color, 1 - fog_density));

	return (result_color);
}

t_color	get_lighting_color(const t_point3d point, const t_vector3d norm_v, const t_scene *const scene)
{
	// possibly - redundant code (was added to prevent overflow of double)
	// TODO: remove
	//normalize_vector(&norm_v);

	t_color				light_color = rgb(0, 0, 0);
	t_light_source3d	*ls;
	t_vector3d			v_ls;
	double				cos_ls;
	t_color				color_ls;
	int					i;

	i = 0;
	while (i < scene->last_light_source_index + 1)
	{
		if (scene->light_sources[i])
		{
			ls = scene->light_sources[i];

			// If not shaded
			if (is_viewable(ls->location, point, scene))
			{
				v_ls = vector3dp(point, ls->location);
				cos_ls = fabs(cos_vectors(norm_v, v_ls));
				color_ls = mul_color(ls->color, cos_ls);
				light_color = add_colors(light_color, color_ls);
			}
		}
		i++;
	}
	return (light_color);
}

t_color	get_specular_color(const t_point3d point, const t_vector3d reflected_ray, const t_scene *const scene, const double p)
{
	t_color				light_color = rgb(0, 0, 0);
	t_light_source3d	*ls;
	t_vector3d			v_ls;
	double				cos_ls;
	t_color				color_ls;
	int					i;
	
	i = 0;
	while (i < scene->last_light_source_index + 1)
	{
		if (scene->light_sources[i]) {
			ls = scene->light_sources[i];
		
			// If not shaded
			if (is_viewable(ls->location, point, scene))
			{
				v_ls = vector3dp(point, ls->location);
				cos_ls = cos_vectors(reflected_ray, v_ls);
				if (cos_ls > EPSILON)
				{
					color_ls = mul_color(ls->color, pow(cos_ls, p));
					light_color = add_colors(light_color, color_ls);
				}
			}
		}
		i++;
	}
	
	return (light_color);
}

t_bool	is_viewable(const t_point3d target_point, const t_point3d starting_point, const t_scene *const scene)
{
	const t_vector3d	ray = vector3dp(starting_point, target_point);
	const double		target_dist = module_vector(ray);
	t_object3d			*nearest_obj = NULL;
	t_point3d			nearest_intersection_point;
	double				nearest_intersection_point_dist = DBL_MAX;
	
	if (find_intersection_tree(scene->kd_tree, starting_point, ray, &nearest_obj, &nearest_intersection_point, &nearest_intersection_point_dist))
	{
		// Check if intersection point is closer than target_point
		return (target_dist < nearest_intersection_point_dist);
	}
	// Ray doesn't intersect any of scene objects
	return (1);
}
