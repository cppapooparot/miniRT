#include "../../inc/intersections.h"
#include <math.h>

bool    intersect_plane(t_ray ray, t_plane *plane, double *t)
{
    double    epsilon;
    double          numerator;
    double          denominator;

    if (!plane || !t)
        return (false);
    epsilon = 1e-6;
    denominator = vec3_dot(ray.direction, plane->normal);
    if (fabs(denominator) < epsilon)
        return (false);
    numerator = vec3_dot(vec3_subtract(plane->point, ray.origin), plane->normal);
    *t = numerator / denominator;
    return (*t > epsilon);
}