#ifndef UTILS_MATH_H
# define UTILS_MATH_H

double	min_double(double a, double b);
double	max_double(double a, double b);

// convert FOV to distance to projection plane
// given FOV in degrees and screen size
double	fov_to_proj_plane_dist(const double fov, double canvas_width);

#endif
