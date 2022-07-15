#include <math.h>

double	fov_to_proj_plane_dist(const double fov, double canvas_width)
{
	return (canvas_width / (2 * tan(fov / 2 * M_PI / 180)));
}
