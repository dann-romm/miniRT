#include "render.h"
#include "scene.h"

#include "objects/sphere.h"

#include <stdio.h>
#include <math.h>

int	main(int ac, char **av)
{
	t_object3d	*obj = new_sphere(point3d(0, 0, 0), 1, rgb(100, 255, 255), material(1, 1, 1, 1, 1, 3));

	t_scene	*scene = new_scene(1, 1, rgb(0, 0, 0));
	add_object(scene, obj);
	prepare_scene(scene);
	
}
