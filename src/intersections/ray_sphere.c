#include "../../inc/intersections.h"
#include <math.h>

#include "../../inc/intersections.h"
#include <math.h>

bool	intersect_sphere(t_ray ray, t_sphere *sphere, double *t)
{
    t_sphere_intersect	sp;

    if (!sphere || !t)
        return (false);
    sp.epsilon = 1e-6;

    sp.oc = vec3_subtract(ray.origin, sphere->center);
    sp.a = vec3_dot(ray.direction, ray.direction);
    sp.b = 2.0 * vec3_dot(sp.oc, ray.direction);
    sp.c = vec3_dot(sp.oc, sp.oc) - (sphere->radius * sphere->radius);
    sp.discriminant = (sp.b * sp.b) - (4.0 * sp.a * sp.c);
    if (sp.discriminant < 0.0)
        return (false);
    sp.sqrt_d = sqrt(sp.discriminant);
    sp.t0 = (-sp.b - sp.sqrt_d) / (2.0 * sp.a);
    sp.t1 = (-sp.b + sp.sqrt_d) / (2.0 * sp.a);
    if (sp.t0 > sp.epsilon && sp.t1 > sp.epsilon)
    {
        if (sp.t0 < sp.t1)
            *t = sp.t0;
        else
            *t = sp.t1;
    }
    else if (sp.t0 > sp.epsilon)
        *t = sp.t0;
    else if (sp.t1 > sp.epsilon)
        *t = sp.t1;
    else
        return (false);

    return (true);
}