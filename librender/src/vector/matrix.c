#include "vector.h"
#include <stdio.h>

void axis_angle_to_matrix(t_vector3d axis, double angle, t_rot_matrix *matrix)
{
	double c = cos(angle);
	double s = sin(angle);
	double t = 1.0 - c;
	double tmp1 = axis.x * axis.y * t;
	double tmp2 = axis.z * s;

	normalize_vector(&axis);

	matrix->m[0][0] = c + axis.x * axis.x * t;
	matrix->m[1][1] = c + axis.y * axis.y * t;
	matrix->m[2][2] = c + axis.z * axis.z * t;
	matrix->m[1][0] = tmp1 + tmp2;
	matrix->m[0][1] = tmp1 - tmp2;
	tmp1 = axis.x * axis.z * t;
	tmp2 = axis.y * s;
	matrix->m[2][0] = tmp1 - tmp2;
	matrix->m[0][2] = tmp1 + tmp2;
	tmp1 = axis.y * axis.z * t;
	tmp2 = axis.x * s;
	matrix->m[2][1] = tmp1 + tmp2;
	matrix->m[1][2] = tmp1 - tmp2;
}

void direction_vector_to_matrix(t_vector3d direction, t_rot_matrix *matrix)
{
	const t_vector3d initial_vector = vector3df(0, 0, 1);

	t_vector3d axis = cross_product(initial_vector, direction);
	if (axis.x == 0 && axis.y == 0 && axis.z == 0)
		axis = vector3df(0, 0, 1);
	double angle = acos(cos_vectors(initial_vector, direction));

	axis_angle_to_matrix(axis, angle, matrix);
}

void multiply_matrix(t_rot_matrix *const m1, t_rot_matrix *const m2, t_rot_matrix *const res)
{
	res->m[0][0] = m1->m[0][0] * m2->m[0][0] + m1->m[0][1] * m2->m[1][0] + m1->m[0][2] * m2->m[2][0];
	res->m[0][1] = m1->m[0][0] * m2->m[0][1] + m1->m[0][1] * m2->m[1][1] + m1->m[0][2] * m2->m[2][1];
	res->m[0][2] = m1->m[0][0] * m2->m[0][2] + m1->m[0][1] * m2->m[1][2] + m1->m[0][2] * m2->m[2][2];
	res->m[1][0] = m1->m[1][0] * m2->m[0][0] + m1->m[1][1] * m2->m[1][0] + m1->m[1][2] * m2->m[2][0];
	res->m[1][1] = m1->m[1][0] * m2->m[0][1] + m1->m[1][1] * m2->m[1][1] + m1->m[1][2] * m2->m[2][1];
	res->m[1][2] = m1->m[1][0] * m2->m[0][2] + m1->m[1][1] * m2->m[1][2] + m1->m[1][2] * m2->m[2][2];
	res->m[2][0] = m1->m[2][0] * m2->m[0][0] + m1->m[2][1] * m2->m[1][0] + m1->m[2][2] * m2->m[2][0];
	res->m[2][1] = m1->m[2][0] * m2->m[0][1] + m1->m[2][1] * m2->m[1][1] + m1->m[2][2] * m2->m[2][1];
	res->m[2][2] = m1->m[2][0] * m2->m[0][2] + m1->m[2][1] * m2->m[1][2] + m1->m[2][2] * m2->m[2][2];
}
