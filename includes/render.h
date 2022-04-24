#ifndef RENDER_H
# define RENDER_H

// open
# include <fcntl.h>
// close read write
# include <unistd.h>
// printf perror strerror
# include <stdio.h>
// malloc free exit
# include <stdlib.h>
// all functions
# include <math.h>
# include <stdint.h>

# define EPSILON 1e-5

typedef int bool;

typedef struct s_point3d
{
	double	x;
	double	y;
	double	z;
}	t_point3d;

typedef struct s_vector3d
{
	double	x;
	double	y;
	double	z;
}	t_vector3d;

typedef struct s_point2d
{
	double	x;
	double	z;
}	t_point2d;

typedef struct s_object3d
{
	bool	(*intersect)(const void *data, const t_point3d vector_start, const t_vector3d vector, t_point3d *intersection_point);
}	t_object3d;


#endif