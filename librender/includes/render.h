#ifndef RENDER_H
# define RENDER_H

# ifndef EPSILON
#  define EPSILON 1e-5
# endif

# define DBL_MAX 1.7976931348623157e+308

# include "scene.h"
# include "camera.h"
# include "canvas.h"
# include "color.h"
# include "vector.h"

void	render_scene(const t_scene *const scene, const t_camera *const camera, t_canvas *canvas, const int num_threads);

t_color	trace(const t_scene *const scene, const t_camera *const camera, t_vector3d vector);

#endif
