#include <stdlib.h>
#include <math.h>
#include "scene.h"

void	set_no_fog(t_scene *const scene)
{
	if (scene->fog_parameters)
		free(scene->fog_parameters);
	scene->fog_density = NULL;
}

double	exponential_fog_density(const double distance, const void *fog_data)
{
	double	*k;

	k = (double *) fog_data;
	return (1 - exp(-(*k) * distance));
}

void	set_exponential_fog(t_scene *const scene, const double k)
{
	double	*k_p;

	scene->fog_density = exponential_fog_density;
	k_p = malloc(sizeof(double));
	*k_p = k;
	if (scene->fog_parameters)
		free(scene->fog_parameters);
	scene->fog_parameters = k_p;
}
