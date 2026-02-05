#include "../../../inc/miniRT.h"

bool	intersect_plane(t_ray ray, t_plane *plane, double *t)
{
	double	numerator;
	double	denominator;

	if (!plane || !t)
		return (false);
	denominator = vec3_dot(ray.direction, plane->normal);
	if (fabs(denominator) < EPSILON)
		return (false);
	numerator = vec3_dot(vec3_subtract(plane->point, ray.origin),
			plane->normal);
	*t = numerator / denominator;
	return (*t > EPSILON);
}
