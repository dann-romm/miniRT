#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mlx.h"

#include "render.h"
#include "scene.h"

#include "objects/sphere.h"
#include "objects/plane.h"
#include "utils_math.h"

#include "parser.h"

#define RT_WIDTH 640
#define RT_HEIGHT 480
#define RT_PROJ_PLANE_DIST 1.0

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

void	ft_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	*(unsigned int *)(img->addr + (y * img->line_length
				+ x * (img->bits_per_pixel / 8))) = color;
}

int	color_to_int(t_color c)
{
	return ((c.r << 16) + (c.g << 8) + c.b);
}

void print_matrix(t_rot_matrix matrix)
{
	dprintf(2, "matrix:\n%f %f %f\n%f %f %f\n%f %f %f\n",
		matrix.m[0][0], matrix.m[0][1], matrix.m[0][2],
		matrix.m[1][0], matrix.m[1][1], matrix.m[1][2],
		matrix.m[2][0], matrix.m[2][1], matrix.m[2][2]);

}

void init_scene(t_scene **scene_ptr, t_canvas **canvas_ptr)
{
	*scene_ptr = new_scene(rgb(20, 20, 20));
	*canvas_ptr = new_canvas(RT_WIDTH, RT_HEIGHT);
}

int	main(int ac, char **av)
{
	t_scene		*scene;
	t_canvas	*canvas;
	t_camera	*camera;

	init_scene(&scene, &canvas);

	t_parsed_data parsed_data = parse_map(av[1], scene);
	camera = parsed_data.camera;
	
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, RT_WIDTH, RT_HEIGHT, "miniRT");
	t_data	*data = (t_data *)malloc(sizeof(t_data));
	data->img = mlx_new_image(mlx, RT_WIDTH, RT_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	mlx_put_image_to_window(mlx, win, data->img, 0, 0);

	prepare_scene(scene);
	dprintf(2, "Rendering...\n");
	render_scene(scene, camera, canvas, 1);
	dprintf(2, "Rendering done.\n");

	int	i = 0;
	while (i < canvas->w * canvas->h)
	{
		ft_mlx_pixel_put(data, i % canvas->w, i / canvas->w, color_to_int(canvas->data[i]));
		i++;
	}
	mlx_put_image_to_window(mlx, win, data->img, 0, 0);

	mlx_loop(mlx);
}
