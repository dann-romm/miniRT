#ifndef UTILS_MATH_H
# define UTILS_MATH_H

#include "bool.h"

// solves the quadratic equation ax^2 + bx + c = 0
// returns if the solution is real or not
// if the solution is real, it stores the two solutions in x1 and x2
t_bool	solve_quadratic(double a, double b, double c, double *x1, double *x2);

// convert FOV to distance to projection plane
// given FOV in degrees and screen size
double	fov_to_proj_plane_dist(const double fov, double canvas_width);

#endif