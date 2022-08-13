#include <math.h>
#include "canvas.h"
#include "color.h"
#include "utils_ft.h"

t_canvas	*new_canvas(int width, int height)
{
	t_canvas	*c;
	
	c = (t_canvas *) malloc(sizeof(t_canvas));
	c->w = width;
	c->h = height;
	c->data = (t_color *) ft_calloc(width * height + 1, sizeof(t_color)); // +1 to avoid segfault when accessing out of bounds
	return (c);
}

void	release_canvas(t_canvas *c)
{
	if (!c)
		return ;
	free(c->data);
	free(c);
}

void	clear_canvas(t_canvas *canv)
{
	ft_memset(canv->data, 0, canv->w * canv->h * sizeof(t_color));
}

void	set_pixel(int x, int y, t_color c, t_canvas *canv)
{
	canv->data[y * canv->w + x] = c;
}

t_color	get_pixel(int x, int y, t_canvas *canv)
{
	return canv->data[y * canv->w + x];
}

// t_canvas	*grayscale_canvas(t_canvas *base, int num_threads)
// {
// 	t_canvas	*ret;
// 	t_color		gray;
// 	int			x;
// 	int			y;
	
// 	(void) num_threads;
// 	ret = new_canvas(base->w, base->h);
// 	x = -1;
// 	while (++x < ret->w)
// 	{
// 		y = -1;
// 		while (++y < ret->h)
// 		{
// 			gray = grayscale(get_pixel(x, y, base));
// 			set_pixel(x, y, gray, ret);
// 		}
// 	}
// 	return (ret);
// }

// // Edges detection
// // See: http://en.wikipedia.org/wiki/Sobel_operator

// int mattrix_x[3][3] =
// 	{{-1, 0, 1},
// 	{-2, 0, 2},
// 	{-1, 0, 1}};

// int mattrix_y[3][3] =
// 	{{-1, -2, -1},
// 	{ 0,  0,  0},
// 	{ 1,  2,  1}};

// t_canvas	*detect_edges_canvas(t_canvas *base, int num_threads) // TODO: разобраться с gx, gy
// {
// 	t_canvas	*grayscaled_canv = grayscale_canvas(base, num_threads);
// 	t_canvas	*grad_canv = new_canvas(base->w, base->h);
// 	uint8_t		grad;
// 	int			x;
// 	int			y;

// 	x = 0;
// 	while (++x < base->w - 1)
// 	{
// 		y = 0;
// 		while (++y < base->h - 1)
// 		{
// 			int i;
// 			int j;
			
// 			int gx = 0;
// 			for (i = -1; i < 2; ++i) {
// 				for (j = -1; j < 2; ++j) {
// 					gx += mattrix_x[i + 1][j + 1] * get_pixel(x + i, y + j, grayscaled_canv).r;
// 				}
// 			}
			
// 			int gy = 0;
// 			for (i = -1; i < 2; ++i) {
// 				for (j = -1; j < 2; ++j) {
// 					gy += mattrix_y[i + 1][j + 1] * get_pixel(x + i, y + j, grayscaled_canv).r;
// 				}
// 			}
			
// 			grad = (uint8_t) sqrt(gx * gx + gy * gy);
// 			set_pixel(x, y, rgb(grad, grad, grad), grad_canv);
// 		}
// 	}
	
// 	release_canvas(grayscaled_canv);
// 	return (grad_canv);
// }
