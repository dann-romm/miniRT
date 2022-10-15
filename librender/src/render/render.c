#include <math.h>
#include "render.h"
#include <stdio.h>

#define ANTIALIASING 1

double	calc_divisor(const t_camera *camera, const t_canvas *canvas)
{
	double	div;

	div = canvas->w / (2.0 * camera->proj_plane_dist * tan(camera->fov / 2));
	return (div);
}

void	render_scene(const t_scene *const scene,
	const t_camera *const camera, t_canvas *canvas, const int num_threads)
{
	const double	dx = canvas->w / 2.0;
	const double	dy = canvas->h / 2.0;
	const double	divisor = calc_divisor(camera, canvas);
	int				i;
	int				j;
	double			x;
	double			y;
	t_vector3d		ray;
	t_color			col;

	i = 0;
	while (i < canvas->w)
	{
		j = 0;
		while (j < canvas->h)
		{
			x = (i - dx) / divisor;
			y = (j - dy) / divisor;
			ray = vector3df(x, y, camera->proj_plane_dist);
			col = trace(scene, camera, ray);
			set_pixel(i, j, col, canvas);
			j++;
		}
		i++;
	}
}
