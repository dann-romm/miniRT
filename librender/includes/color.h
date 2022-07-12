#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

# define MAX_R 255
# define MAX_G 255
# define MAX_B 255

typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_color;

// initialize color with given values
t_color	rgb(uint8_t r, uint8_t g, uint8_t b);

// add two colors
t_color	add_colors(t_color c1, t_color c2);

// mix two colors
t_color	mix_colors(t_color c1, t_color c2);

// multiply color by given factor
t_color	mul_color(t_color c, double k);

// get grayscale color
// https://en.wikipedia.org/wiki/Grayscale
t_color	grayscale(t_color c);

#endif
