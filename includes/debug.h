#ifndef DEBUG_H
# define DEBUG_H

# include <stdio.h>
# include "color.h"

__attribute__((weak))
void	_DEBUG_print_color(t_color c)
{
	printf("color: (%3d,%3d,%3d)\n", c.r, c.g, c.b);
}

#endif
