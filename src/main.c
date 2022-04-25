#include "color.h"
#include "debug.h"
#include <stdio.h>

int main()
{
	t_color a = rgb(15, 255, 16);
	t_color b = rgb(143, 1, 16);

	t_color c = mul_color(a, 0.4);

	_DEBUG_print_color(c);

	return (0);
}
