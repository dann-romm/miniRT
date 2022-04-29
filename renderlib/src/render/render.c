#include "render.h"

#define ANTIALIASING 1

void	render_scene(const t_scene *const scene, const t_camera *const camera, t_canvas *canvas, const int num_threads)
{
	const double	dx = canvas->w / 2.0;
	const double	dy = canvas->h / 2.0;
	const double	focus = camera->proj_plane_dist;
	int				i;
	int				j;
	double			x;
	double			y;
	t_vector3d		ray;
	t_color			col;

	// TODO: consider possibility to define these OpenMP parameters
	// in declarative style (using directives of preprocessor)
	
	i = 0;
	while (i < canvas->w)
	{
		j = 0;
		while (j < canvas->h)
		{
			x = i - dx;
			y = j - dy;
			ray = vector3df(x, y, focus);
			col = trace(scene, camera, ray);
			set_pixel(i, j, col, canvas);
			j++;
		}
		i++;
	}
	
	// // TODO: argument of the function? global variable?
	// const int antialiasing = ANTIALIASING;
	
	// if (antialiasing)
	// {
	// 	t_canvas * edges = detect_edges_canvas(canvas, num_threads);
	// 	for(i = 1; i < w - 1; i++) {
	// 		for(j = 1; j < h - 1; j++) {
	// 			// edges canvas is grayscaled
	// 			// it means that color components (r, g, b) are equal
	// 			Byte gray = get_pixel(i, j, edges).r;
			
	// 			// TODO: improve
	// 			if(gray > 10) {
	// 				const double x = i - dx;
	// 				const double y = j - dy;
				
	// 				t_color c = get_pixel(i, j, canvas);
				
	// 				const double weight = 1.0 / 4;
	// 				c = mul_color(c, weight);
	// 				c = add_colors(c, mul_color(trace(scene, camera, vector3df(x + 0.5, y, focus)), weight));
	// 				c = add_colors(c, mul_color(trace(scene, camera, vector3df(x, y + 0.5, focus)), weight));
	// 				c = add_colors(c, mul_color(trace(scene, camera, vector3df(x + 0.5, y + 0.5, focus)), weight));
				
	// 				set_pixel(i, j, c, canvas);
	// 			}
	// 		}
	// 	}
	// 	release_canvas(edges);
	// }
}