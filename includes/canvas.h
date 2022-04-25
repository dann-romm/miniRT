#ifndef CANVAS_H
# define CANVAS_H

# include "color.h"

typedef struct s_canvas
{
	int		w;
	int		h;
	t_color	*data;
}	t_canvas;

// create new empty canvas
t_canvas	*new_canvas(int width, int height);

// convert all canvas to grascape colors
t_canvas	*grayscale_canvas(t_canvas *base, int num_threads);

t_canvas	*detect_edges_canvas(t_canvas *base, int num_threads);

// delete canvas and free all allocated data
void		delete_canvas(t_canvas *canv);

// clears canvas, reset all colors to default
void		clear_canvas(t_canvas *canv);

// set pixel color on given coordinates
void	set_pixel(int x, int y, t_color c, t_canvas *canv);

// get pixel color on given coordinates
t_color get_pixel(int x, int y, t_canvas *canv);

// t_canvas	*read_png(char *file_name);

// void	write_png(char file_name[], t_canvas *canv);


#endif