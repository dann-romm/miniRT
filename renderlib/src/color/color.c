#include "color.h"

t_color	rgb(uint8_t r, uint8_t g, uint8_t b)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color	add_colors(t_color c1, t_color c2)
{
	if ((int) c1.r + c2.r > MAX_R)
		c1.r = MAX_R;
	else
		c1.r += c2.r;
	if ((int) c1.g + c2.g > MAX_G)
		c1.g = MAX_G;
	else
		c1.g += c2.g;
	if ((int) c1.b + c2.b > MAX_B)
		c1.b = MAX_B;
	else
		c1.b += c2.b;
	return (c1);
}

t_color	mix_colors(t_color c1, t_color c2)
{
	t_color	c;
	/*
	c.r = ((uint16_t) c1.r + c2.r) >> 1;
	c.g = ((uint16_t) c1.g + c2.g) >> 1;
	c.b = ((uint16_t) c1.b + c2.b) >> 1;
	*/
	c.r = ((uint16_t) c1.r * c2.r) >> 8;
	c.g = ((uint16_t) c1.g * c2.g) >> 8;
	c.b = ((uint16_t) c1.b * c2.b) >> 8;
	/*
	c.r = sqrt((uint16_t) c1.r * c2.r);
	c.g = sqrt((uint16_t) c1.g * c2.g);
	c.b = sqrt((uint16_t) c1.b * c2.b);
	*/
	return (c);
}

t_color	mul_color(t_color c, double k)
{
	c.r *= k;
	c.g *= k;
	c.b *= k;
	return (c);
}

// https://en.wikipedia.org/wiki/Grayscale
t_color	grayscale(t_color c)
{
	// const uint8_t gray = (uint8_t)(c.r * 0.299 + c.g * 0.587 + c.b * 0.114);
	const uint8_t gray = (uint8_t)(c.r * 0.2126 + c.g * 0.7152 + c.b * 0.0722);

	c.b = gray;
	c.r = gray;
	c.g = gray;
	return (c);
}
