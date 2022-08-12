#include "vector.h"

t_vector3d rotate_vector_by_matrix(const t_vector3d p, const t_rot_matrix m)
{
	return (vector3df(
		p.x * m.m[0][0] + p.y * m.m[1][0] + p.z * m.m[2][0],
		p.x * m.m[0][1] + p.y * m.m[1][1] + p.z * m.m[2][1],
		p.x * m.m[0][2] + p.y * m.m[1][2] + p.z * m.m[2][2]));
}
