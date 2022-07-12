#include "vector.h"

t_vector3d	reflect_ray(const t_vector3d incident_ray, const t_vector3d norm_v)
{
	const double	k = 2 * dot_product(incident_ray, norm_v)
		/ sqr_module_vector(norm_v);
	const double	x = incident_ray.x - norm_v.x * k;
	const double	y = incident_ray.y - norm_v.y * k;
	const double	z = incident_ray.z - norm_v.z * k;

	return (vector3df(x, y, z));
}
